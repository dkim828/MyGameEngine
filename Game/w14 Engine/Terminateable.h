#ifndef TERMINATEABLE_H
#define TERMINATEABLE_H

class TerminateableReceiver;

class Terminateable
{
friend class TerminateableManager;

public:
	Terminateable();
	virtual ~Terminateable(){};
	
	/**
	\brief A function that is called within a GameEntity to call to start the process for properly destroying this GameEntity
	\ingroup TERMINATION

	Memory management and handling of all GameEntities, unless explicitly set otherwise through Terminateable::setObjectOwner(),
	is handled in the background by W14 system. So, there is a very specific process the system has to go through in order to
	properly delete an object. So instead of calling the delete operator, the GameEntities themselves have to call this 
	function to start that process.
	

	\b Example: The Bullets in the SceneTwo of the Demo collides with Ships. And within the Bullet's collided function with 
	Ships, it checks to make sure the Ship it collided with is NOT the shooter of the bullet and if it is not a message is 
	shown then this function is called to initiate the destruction process.
		\code
		void Bullet::collided( Ship* other  )
		{
			if( other->getID() != ownerID )
			{
				printf("Bullet Collided with EnemyShip\n");
				markForTermination();
			}
		}
		\endcode
	*/
	void markForTermination();

	/**
	\brief A function that is used to set owner of GameEntity
	\ingroup MANAGEMENT

	TerminateableReceiver is a base class that user made Factories should derive from if they need ownership of the
	GameEntity. Upon GameEntity destruction, the last part of the process is to send the GameEntity to whoever
	owns it. By default the GameEntities are owned by and thus sent to a Dumpster class that derives from
	TerminateableReceiver. 
	
	This Dumpster class is NOT to be touched by the user. All it does is delete objects when it needs to.

	However, if you have a recycling factory, the factory needs ownership of the GameEntity. In order to make a
	GameEntity not be sent to the dumpster upon destruction, this function needs to be called on creation of a
	GameEntity.
	

	\b Example: The mentioned scenario with recycling factory is what happens with the BulletFactory in the demo. When
	it creates a new Bullet by calling the "new" operatior, this function is called so the ownership of the Bullet is 
	moved from the default dumpster to the BulletFactory.
		\code
		void BulletFactory::CreateBullet(const Vect& dir,const Vect& Pos, int shooterID )
		{
			Bullet* b;
			std::string out;
			if( instance().recycledStack.empty() )
			{
				b = new Bullet( );//A derived GameEntity
				b->setObjectOwner( &instance() );//function called after newly being created
			}
			else
			{
				b = instance().recycledStack.top();
				instance().recycledStack.pop();

				b->registerBasicFunctionality();	
			}

			instance().activeSet.insert( b );
			b->initialize( dir, Pos, shooterID );
		} 
		\endcode
	*/
	void setObjectOwner( TerminateableReceiver* r );


	virtual void terminationEvent() {};

private:
	void sendToOwner();

	bool markedForTermination;
	TerminateableReceiver* terminateableOwner;
};



#endif //TERMINATEABLE_H