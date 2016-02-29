#ifndef INPUTABLE_H
#define INPUTABLE_H

#include "Azul.h"
#include "InputGlobals.h"

class Inputable
{
public:
	Inputable() {};
	virtual ~Inputable() {};

	virtual void keyPressed( AZUL_KEY k, bool Ctrl, bool Shift, bool Alt ) { k;Ctrl;Shift;Alt;};
	virtual void keyReleased(  AZUL_KEY k, bool Ctrl, bool Shift, bool Alt ) {k;Ctrl;Shift;Alt;};

protected:
	/**
	\brief A function that is used to register Keyboard Key and the type of event/s to be called back to
	\ingroup INPUT

	This function is protected in Inputable so any derived classes, which includes GameEntity, can call this.

	Like much of the other functionality of GameEntity, the functionality for getting key events is achieved
	through a process of registering to some manager in the Scene that handles Inputable(a base class of 
	GameEntity) and key events. This action was simplified by having a protected register function inside
	Inputable such that any GameEntity can directly call its register/deregister without hassle.

	The way it is implemented now, is that the user must register exactly what kind of keys to receive callbacks
	for. There is no "registerWholeKeyboard" type of function.

	\b Example: The Ship from the Demo, as mentioned in GameEntity::terminationEvent(), needs the Key Pressed
	and Key Released Events due to how the Ship is being controled. However only the KeyPressed events are 
	registered for ZXCV and SPACE keys because the Ship only needed the press events for setting alarms and
	shooting the Bullets.
		\code
		Ship::Ship(float x, float y, float z, int shipID, float yAngle )
		{	
			//lots of other code here //

			registerKeyboardKey( AZUL_KEY::KEY_W, InputFlags::KeyPressed_KeyReleased );
			registerKeyboardKey( AZUL_KEY::KEY_A, InputFlags::KeyPressed_KeyReleased );
			registerKeyboardKey( AZUL_KEY::KEY_S, InputFlags::KeyPressed_KeyReleased );
			registerKeyboardKey( AZUL_KEY::KEY_D, InputFlags::KeyPressed_KeyReleased );

			registerKeyboardKey( AZUL_KEY::KEY_Z, InputFlags::KeyPressed );
			registerKeyboardKey( AZUL_KEY::KEY_X, InputFlags::KeyPressed );
			registerKeyboardKey( AZUL_KEY::KEY_C, InputFlags::KeyPressed );
			registerKeyboardKey( AZUL_KEY::KEY_V, InputFlags::KeyPressed );

			registerKeyboardKey( AZUL_KEY::KEY_SPACE, InputFlags::KeyPressed );
		}
		\endcode

		\param	key		An AZUL_KEY enum value that correlates to some Key on a keyboard
		\param	state	An enum value that reflects the states to which to registerer wants receive callbacks for
	*/
	void registerKeyboardKey( AZUL_KEY key, InputFlags::KeyFlag state );

	/**
	\brief A function that is used to deregister registered Key+_Key event type
	\ingroup INPUT
	
	This function is protected in Inputable so any derived classes, which includes GameEntity, can call this.

	Once a key on the keyboard along with the type callback is registered onto the input system of W14, there is no
	way for the system to know when an object that was receiving callbacks is suddenly destroyed. 

	For every registered key and key event type, there has to be a deregistering of that key and event type somewhere
	by the time the GameEntity is gone.

	\b Important: The deregistering cannot be done in the destructor because with the way the system process game and 
	GameEntity destruction, a deregistering call in the destructor causes a crash. Like with Collideable::deregisterCollision(),
	it is recommended to deregister within the GameEntity::terminationEvent() function.

	\b Example: Following the description above, the Ship from the Demo deregisters all keyboard functionality within
	GameEntity::terminationEvent() that has been derived to Ship::terminationEvent().
		\code
		void Ship::terminationEvent()
		{
			deregisterCollision< Ship >( this );

			deregisterKeyboardKey( AZUL_KEY::KEY_W, InputFlags::KeyPressed_KeyReleased );
			deregisterKeyboardKey( AZUL_KEY::KEY_A, InputFlags::KeyPressed_KeyReleased );
			deregisterKeyboardKey( AZUL_KEY::KEY_S, InputFlags::KeyPressed_KeyReleased );
			deregisterKeyboardKey( AZUL_KEY::KEY_D, InputFlags::KeyPressed_KeyReleased );

			deregisterKeyboardKey( AZUL_KEY::KEY_Z, InputFlags::KeyPressed );
			deregisterKeyboardKey( AZUL_KEY::KEY_X, InputFlags::KeyPressed );
			deregisterKeyboardKey( AZUL_KEY::KEY_C, InputFlags::KeyPressed );
			deregisterKeyboardKey( AZUL_KEY::KEY_V, InputFlags::KeyPressed );

			deregisterKeyboardKey( AZUL_KEY::KEY_SPACE, InputFlags::KeyPressed );
		}
		\endcode

		\param	key		An AZUL_KEY enum value that correlates to some Key on a keyboard
		\param	state	An enum value that reflects the keyStates to deregister from
	*/
	void deregisterKeyboardKey( AZUL_KEY key, InputFlags::KeyFlag state );


	/*
	void registerMouseClick(
	*/
};

#endif INPUTABLE_H