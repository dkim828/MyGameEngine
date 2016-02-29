#ifndef KEYEVENT_H
#define KEYEVENT_H

#include "Azul.h"
#include "InputGlobals.h"

#include <list>

class Inputable;

class KeyEvent
{
public:
	KeyEvent( AZUL_KEY keyIn );
	KeyEvent( const KeyEvent& ) {};
	~KeyEvent();

	void update();

	void registerInputable( Inputable* toReg, InputFlags::KeyFlag state);
	void deregisterInputable( Inputable* toDereg, InputFlags::KeyFlag state );

private:
	AZUL_KEY key;

	//=====================================================================================//
	//keyState
	//----->If true, key is down;
	//----->If false, key is up;
	//=====================================================================================//
	bool currentState;
	//=====================================================================================//
	//keyState
	//----->If true, key is down;
	//----->If false, key is up;
	//=====================================================================================//
	bool prevState;

	bool mod_ctrl;
	bool mod_alt;
	bool mod_shift;
	
	//=====================================================================================//
	//Inputable Entities to call depending on keyEvent
	//=====================================================================================//
	std::list< Inputable* > callback_KeyReleased;
	std::list< Inputable* > callback_KeyPressed;





	void keyReleased();
	void keyPressed();
};

#endif KEYEVENT_H