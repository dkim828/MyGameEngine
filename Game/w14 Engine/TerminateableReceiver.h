#ifndef TERMINATEABLERECEIVER_H
#define TERMINATEABLERECEIVER_H


class Terminateable;

class TerminateableReceiver
{
public:
	TerminateableReceiver(){};
	virtual ~TerminateableReceiver(){};

	/**
	\brief A function that is used by the internal system as the final callback of GameEntity destruction
	\ingroup MANAGEMENT

	TerminateableReceiver is a base class that user made Factories should derive from if they need ownership of the
	GameEntity. Upon GameEntity destruction, the last part of the process is to send the GameEntity to whoever
	owns it. By default the GameEntities are owned by and thus sent to a Dumpster class that derives from
	TerminateableReceiver. 
	
	This Dumpster class is NOT to be touched by the user. All it does is delete objects when it needs to.

	The Dumpster RECEIVES a GameEntity at the end of its destruction process through the Dumpster's implementation
	of this function where the Dumpster proceeds to delete it.

	\b Example: The mentioned scenario with recycling factory is what happens with the BulletFactory in the demo. On Bullet creation
	in the factory, the ownership of created Bullets is set to the BulletFactory as shown in Terminateable::setObjectOwner(). So
	when a Bullet calls Terminateable::markForTermination(), the BulletFactory receives it through this function and proceeds
	to recycle it.
		\code
		void  BulletFactory::receiveTerminateable( Terminateable* t )
		{
			activeSet.erase( (Bullet*) t );
			recycledStack.push( (Bullet*) t );
		}
		\endcode
	*/
	virtual void receiveTerminateable( Terminateable* t) = 0;
private:
};


#endif