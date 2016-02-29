#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include "Inputable.h"
#include "Updateable.h"
#include "Drawable.h"
#include "Alarmable.h"
#include "Collideable.h"
#include "Terminateable.h"

#include "GraphicsObjectManager.h"

class GameEntity : public Inputable, public Updateable, public Drawable, public Alarmable, public Collideable, public Terminateable
{
public:
	GameEntity();
	virtual ~GameEntity();

	/**
	\brief Termination event that happens after a GameEntity has been marked for Termination
	\ingroup TERMINATION

	This is an optional function to implement for the user in their derived GameEntity classes.

	\b Note: If your GameEntity is registered for collision through Collideable::registerCollision(), your
	GameEntity must Collideable::deregisterCollision() within the terminationEvent.

	\b Note: If your GameEntity is registered for input through Inputable::registerKeyboardKey(), your
	GameEntity must Inputable::deregisterKeyboardKey() within the terminationEvent.

	\b Note: If your GameEntity has any alarms active at any time through Alarmable::setAlarm(), your
	GameEntity must Alarmable::cancelAllAlarms() within the terminationEvent.

	\b Example: The ship in the Demo utilizes almost everything available to the GameEntity. Therefore
	a lot of things need to happen in the terminationEvent() of the ship for the game to run properly
		\code
		void Ship::terminationEvent()
		{
			deregisterCollision< Ship >( this );

			deregisterKeyboardKey( AZUL_KEY::KEY_W, InputFlags::KeyPressed_KeyReleased );
			deregisterKeyboardKey( AZUL_KEY::KEY_A, InputFlags::KeyPressed_KeyReleased );
			deregisterKeyboardKey( AZUL_KEY::KEY_S, InputFlags::KeyPressed_KeyReleased );
			deregisterKeyboardKey( AZUL_KEY::KEY_D, InputFlags::KeyPressed_KeyReleased );

			deregisterKeyboardKey( AZUL_KEY::KEY_Z, InputFlags::KeyPressed_KeyReleased );
			deregisterKeyboardKey( AZUL_KEY::KEY_X, InputFlags::KeyPressed_KeyReleased );
			deregisterKeyboardKey( AZUL_KEY::KEY_C, InputFlags::KeyPressed_KeyReleased );
			deregisterKeyboardKey( AZUL_KEY::KEY_V, InputFlags::KeyPressed_KeyReleased );

			deregisterKeyboardKey( AZUL_KEY::KEY_SPACE, InputFlags::KeyPressed_KeyReleased );

			cancelAllAlarms();
		}
		\endcode
	*/
	virtual void terminationEvent(){};

	/**
	\brief Collision event that happens after a GameEntity has been pinged as collided with another GameEntity
	\ingroup COLLISION

	This is an optional function to implement for the user in their derived GameEntity classes. However, if your
	GameEntity is registered for Collision, and you do not have a Collideable::collided() function implemented
	into the derived GameEntity, there is no way for the GameEntity to know if it collided.

	This function is a bit unique in that depending on which GameEntities were set to be collided through 
	Scene::initScene(), the GameEntity must also implement overloaded collided functions that reflect that. If not,
	the right callbacks are not initiated.

	\b Example: The ship in the Demo's SceneTwo is set to collide with another Ship and Bullet objects. So in 
	Ship's implementation, it needs overloaded versions of collided. So with the overloaded collided functions,
	the Ship can behave differently depending on what it collided with. In the demo, the ship destroys itself when
	it collides with another ship, and if it collides with a bullet that has not been fired by the ship (thus the if
	conditional about the ownerID), it prints out a messages
		\code
		void Ship::collided( Collideable* other)
		{
		}
		void Ship::collided( Ship* other)
		{
			markForTermination();
		}
		void Ship::collided( Bullet* other)
		{
			if( other->getOwnerID() != id)
				printf("\nShip hit by Bullet\n");
		}
		\endcode
		

	\param	other	The GameEntity that has collided with this one
	*/
	virtual void collided( Collideable* other ){other;};
	
	virtual void collidedTerrain(){};

	/**
	\brief This is a callback that is called upon a key press event 
	\ingroup INPUT

	This is an optional function to implement for the user in their derived GameEntity classes.
	However, it needs to be implemented to receive a proper callback from the engine upon
	a key press event.

	Assuming the keys have been properly registered in either some initialize function or the
	constructor of the derived GameEntity, this function will be called with the arguments being
	whatever keys that were registered  when the keys are presed.

	\b Example: The ship in the Demo has movement depending on the WASD keys, shoots with the SPACE
	key, sets/adds time to the alarms using the ZXC keys with modifiers, and the V key outputs
	the remaining times on the alarms. The registration of these keys is viewable in 
	Inputable::registerKeyboardKey().
		\code
		void Ship::keyPressed( AZUL_KEY k, bool Ctrl, bool Shift, bool  )
		{
			//Ship Movement
			if( k == AZUL_KEY::KEY_W )
				impulse = Vect(0,0,1)  * moveSpeed;
			if( k == AZUL_KEY::KEY_S )
				impulse = Vect(0,0,1)  * -moveSpeed;

			if( k == AZUL_KEY::KEY_A )
				rotationImpulse = Matrix( ROT_Y, rotSpeed );
			if( k == AZUL_KEY::KEY_D )
				rotationImpulse = Matrix( ROT_Y, -rotSpeed );

			if( k == AZUL_KEY::KEY_SPACE)
				shootBullet();

			//Alarm Inputs
			if( k == AZUL_KEY::KEY_Z )
			{
				if( Shift )
					addTimeToAlarm( Alarm::ID_0, 5 );
				else if( Ctrl )
					addTimeToAlarm( Alarm::ID_0, -5 );
				else
					setAlarm( Alarm::ID_0, 10);
			}
			if( k == AZUL_KEY::KEY_X )
			{
				if( Shift )
					addTimeToAlarm( Alarm::ID_1, 5 );
				else if( Ctrl )
					addTimeToAlarm( Alarm::ID_1, -5 );
				else
					setAlarm( Alarm::ID_1, 10);
			}
			if( k == AZUL_KEY::KEY_C )
			{
				if( Shift )
					addTimeToAlarm( Alarm::ID_2, 5 );
				else if( Ctrl )
					addTimeToAlarm( Alarm::ID_2, -5 );
				else
					setAlarm( Alarm::ID_2, 10);
			}
			if( k == AZUL_KEY::KEY_V )
			{
				std::string out = "\nAlarm 0: " + std::to_string( getTimeLeftOnAlarm(Alarm::ID_0) ) + "\n";
				out += "Alarm 1: " + std::to_string( getTimeLeftOnAlarm(Alarm::ID_1) ) + "\n";
				out += "Alarm 2: " + std::to_string( getTimeLeftOnAlarm(Alarm::ID_2) ) + "\n\n";

				printf(out.c_str());
			}
		}
		\endcode
		
	\param	k	An AZUL_KEY argument that holds the currently pressed key
	\param	Ctrl	A modifier key. This is true if either left or right Ctrl is held down upon key press
	\param	Shift	A modifier key. This is true if either left or right Shift is held down upon key press
	\param	Alt		A modifier key. This is true if either left or right Alt is held down upon key press
	*/
	virtual void keyPressed( AZUL_KEY k, bool Ctrl, bool Shift, bool Alt ) { k;Ctrl;Shift;Alt;};
	/**
	\brief This is a callback that is called upon a key release event 
	\ingroup INPUT

	This is an optional function to implement for the user in their derived GameEntity classes.
	However, it needs to be implemented to receive a proper callback from the engine upon
	a key release event.

	Assuming the keys have been properly registered in either some initialize function or the
	constructor of the derived GameEntity, this function will be called with the arguments being
	whatever keys that were registered  when the keys are released.

	\b Example: The ship in the Demo is registered to a lot of keys and will have many callbacks
	to this functions such as when KEY_Z is released because Ship is registered for both keyPress
	and keyRelease call backs. However, upon key release all the Ship wants to do is to be able to
	set the movement/rotation impulses to 0 so that the Ship stops moving when the movement keys,
	WASD, are released. The registration of these keys is viewable in Inputable::registerKeyboardKey().
		\code
		void Ship::keyReleased(  AZUL_KEY k, bool , bool , bool  )
		{	
			if( k == AZUL_KEY::KEY_W || k == AZUL_KEY::KEY_S )
			{
				impulse.set(0,0,0);
			}
			if( k == AZUL_KEY::KEY_A  || k == AZUL_KEY::KEY_D)
			{
				rotationImpulse.set(ROT_Y, 0);
			}
		}
		\endcode
		
	\param	k	An AZUL_KEY argument that holds the currently released key
	\param	Ctrl	A modifier key. This is true if either left or right Ctrl is held down upon key release
	\param	Shift	A modifier key. This is true if either left or right Shift is held down upon key release
	\param	Alt		A modifier key. This is true if either left or right Alt is held down upon key release
	*/
	virtual void keyReleased(  AZUL_KEY k, bool Ctrl, bool Shift, bool Alt ) {k;Ctrl;Shift;Alt;};
	
	/**
	\brief An update function that gets called upon each game loop
	\ingroup UPDATE

	This is an optional function to implement for the user in their derived GameEntity classes. However,
	every GameEntity is registered to be updated upon object creation so without this function implemented,
	the derived GameEntity is still being "updated" every loop, but the user's object has no knowledge of that.

	\b Example: An example of a GameEntity without an update() function is the Cottage class in the Demo. It
	is definitely in the scene, but because it is an object that just stays still with no moving parts or internal
	variables to update, Cottage does not implement the update() function solely because it is not being used
	\code
	class Cottage : public GameEntity
	{
	public:
		Cottage();
		Cottage( const Cottage&  ){};
		~Cottage();

		//FROM Terminateable
		virtual void terminationEvent();
	
		//FROM Collideable
		virtual void collided( Collideable* other );
		virtual void collided( Ship* other );
		virtual void collided( Bullet* other );

		//FROM Drawable
		virtual void draw();
	private:
		GraphicsObjectFlatTexture* cottageGObj;

		Matrix Scale;
		Matrix Rotation;
		Matrix Translation;

	};
	\endcode


	\b Example: However, the Ship is a moving part in the demo. It has impulses for the movement and rotation that changes
	its Rotation and position variables. While the impulses are handled in GameEntity::keyPressed(), the Ship takes those
	impulses and updates its positioning variables in update.
		\code
		void Ship::update()
		{
			Rotation *= rotationImpulse;
			position += ( impulse * Rotation );
		}
		\endcode
	*/
	virtual void update(){};

	/**
	\brief A draw function that gets called at the end of each game loop with the purpose of drawing/rendering onto the screen
	\ingroup DRAW

	This is an optional function to implement for the user in their derived GameEntity classes. However,
	every GameEntity is registered to be drawn upon object creation so without this function implemented,
	the derived GameEntity is still being pinged for it every loop, but nothing is actually being drawn.

	If an GameEntity wants to be drawn, it must hold a GraphicsObject which can be obtained through loading models onto
	the AssetManager and then calling AssetManager::getGObj().

	\b Example: The Ship has a GraphicsObjectFlatTexture pointer as a member variable and it set through AssetManager::getGObj()
	using the "shipModel" key. The GraphicsObjectFlatTexture object has render() function that is to be called in the GameEntity::draw()
	function. Moreover, because the Ship is projected on the screen though a calculated transformation matrix, the matrix is set within 
	draw before call render(). Also, Collideable::showBoundingSphere() is also called which in turns does the same thing as just described,
	but for a wireframe sphere that fits the Ship.
	\code
	void Ship::draw()
	{
		Translation.set(TRANS, position);
		worldTransformMatrix = Scale * Rotation * Translation;
		(shipGObj)->setWorld(worldTransformMatrix);
		shipGObj->Render();

		showBoundingSphere();
	}
	\endcode
	*/
	virtual void draw(){};


	/**
	\brief This is a callback that is called upon a finishing of Alarm::ID_0  
	\ingroup ALARM

	This is an optional function to implement for the user in their derived GameEntity classes. However,
	if the derived class calls Alarmable::setAlarm(), the class will never get the proper callback from
	the alarm system because the callback function was not implemented. Behind the scenes, the GameEntity
	is pinged by the alarm system, but the derived class will not know without the function implementation.

	\b Example: The Ship from the demo has the ability to set alarms through its GameEntity::keyPressed() events.
	So when the alarms are done, the callback is setup so a message is shown on the console.
	\code
	void Ship::alarm0()
	{
		 printf("ALARM_0 from Ship\n"); 
	}
	void Ship::alarm1()
	{
		 printf("ALARM_1 from Ship\n"); 
	}
	void Ship::alarm2()
	{
		 printf("ALARM_2 from Ship\n"); 
	}
	\endcode
	*/
	virtual void alarm0(){};
	/**
	\brief This is a callback that is called upon a finishing of Alarm::ID_1  
	\ingroup ALARM

	This is an optional function to implement for the user in their derived GameEntity classes. However,
	if the derived class calls Alarmable::setAlarm(), the class will never get the proper callback from
	the alarm system because the callback function was not implemented. Behind the scenes, the GameEntity
	is pinged by the alarm system, but the derived class will not know without the function implementation.

	\b Example: See GameEntity::alarm0 
	*/
	virtual void alarm1(){};
	/**
	\brief This is a callback that is called upon a finishing of Alarm::ID_2  
	\ingroup ALARM

	This is an optional function to implement for the user in their derived GameEntity classes. However,
	if the derived class calls Alarmable::setAlarm(), the class will never get the proper callback from
	the alarm system because the callback function was not implemented. Behind the scenes, the GameEntity
	is pinged by the alarm system, but the derived class will not know without the function implementation.
	
	\b Example: See GameEntity::alarm0 
	*/
	virtual void alarm2(){};


	/**
	\brief This is a function used by the system to register basic functionality to a GameEntity 
	\ingroup MANAGEMENT

	This is a function that registers a GameEntity with the Updateable and Drawable Managers. Within
	every base GameEntity constructor, this function is called so whenever a derived GameEntity is
	created, they are automatically registered to be "functional" within the scope of the current
	Scene.

	Basically, this function needs to be called whenever some GameEntity is put onto the scene if it
	never existed or was deregistered at some time or another.

	\b Example: Within the Demo, the Bullet object is solely owned and managed by a recycling BulletFactory.
	Although the Ship calls the BulletFactory's create function, the BulletFactory takes care of creation and 
	deletion of Bullet Objects. Furthermore, once a Bullet is created and destroyed, it is kept in a 
	stack within the factory for later use. However, the Bullet is completely deregistered from the
	system when it is destroyed so the Factory must call this function to restore functionality to 
	the Bullet.
	\code
	void BulletFactory::CreateBullet(const Vect& dir,const Vect& Pos, int shooterID )
	{
		Bullet* b;
		std::string out;
		if( instance().recycledStack.empty() )
		{
			b = new Bullet( );
			b->setObjectOwner( &instance() );
		}
		else
		{
			b = instance().recycledStack.top();
			instance().recycledStack.pop();

			b->registerBasicFunctionality();	//function called after taking it out of the recycled stack
		}

		instance().activeSet.insert( b );
		b->initialize( dir, Pos, shooterID );
	} 
	\endcode
	*/
	void registerBasicFunctionality();


	Matrix getScaleMatrix() { return Scale; };
	Matrix getTransMatrix() { return Translation; };
	Matrix getRotMatrix() { return Rotation; };

protected:
	Matrix Scale;
	Matrix Translation;
	Matrix Rotation;

	//CAMERA
	int camID;



	void setGameEntityWorld( Matrix& inWorldTransform )
	{
		//*FIX_FLAG* NEED TO OPTIMIZE WITH STRATEGY OR SOMETHING
		if( gObject != 0)
		{
			gObject->setWorld( inWorldTransform );
		}
		if( collidingModel != 0 )
		{
			colWorldTransform = inWorldTransform;
			updateCollider(); //The stupid
		}
	}


	void setCollision( Model* colModel, CollisionType type = CollisionType::BoundingSphere )
	{
		collidingModel = colModel;
		setCollisionType( type );
	}
	void setGraphicsObject( GraphicsObject* gObj )
	{
		if( gObject != 0 )//There is a pre-existing GraphicsObject
			GraphicsObjectManager::removeGraphicsObject( gObject );

		gObject = gObj;
	}
	void setGraphicsObjectAndCollision( GraphicsObject* gObj, CollisionType type = CollisionType::BoundingSphere )
	{
		if( gObject != 0 )//There is a pre-existing GraphicsObject
			GraphicsObjectManager::removeGraphicsObject( gObject );

		gObject = gObj;
		
		collidingModel = gObject->getModel();
		setCollisionType( type );
	}

	void renderGameEntity()
	{
		gObject->Render();
	}


};

#endif GAMEENTITY_H