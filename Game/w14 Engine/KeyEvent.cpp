#include "KeyEvent.h"

#include "Inputable.h"

KeyEvent::KeyEvent( AZUL_KEY keyIn )
{
	key = keyIn;

	prevState = false;
	currentState = false;
}

KeyEvent::~KeyEvent()
{
	callback_KeyReleased.clear();
	callback_KeyPressed.clear();
}



void KeyEvent::update()
{
	//getting current state of key
	currentState = InputMan::GetKeyboard()->GetKeyState( key );

	//If Change in State
	if( currentState != prevState )
	{
		//Getting Key Modifier States only when Change in wanted state
		mod_ctrl = InputMan::GetKeyboard()->GetKeyState( KEY_LEFT_CONTROL ) || InputMan::GetKeyboard()->GetKeyState( KEY_RIGHT_CONTROL );
		mod_alt = InputMan::GetKeyboard()->GetKeyState( KEY_LEFT_ALT ) || InputMan::GetKeyboard()->GetKeyState( KEY_RIGHT_ALT );
		mod_shift = InputMan::GetKeyboard()->GetKeyState( KEY_LEFT_SHIFT ) || InputMan::GetKeyboard()->GetKeyState( KEY_RIGHT_SHIFT );
		
		//IDLE -> PRESSED
		if( prevState == false )
		{
			keyPressed();
		}
		//PRESSED -> IDLE
		else
		{
			keyReleased();
		}
	}

	//setting prevState
	prevState = currentState;
}

void KeyEvent::registerInputable( Inputable* toReg, InputFlags::KeyFlag state)
{
	std::list< Inputable* >::iterator it;

	switch( state )
	{
	case InputFlags::KeyPressed_KeyReleased:
	case InputFlags::KeyPressed:
		//Make sure Inputable is not already registered
		for( it = callback_KeyPressed.begin();
			 it != callback_KeyPressed.end(); it++)
		{
			if( (*it) == toReg )
				break;
		}
		
		//Adding Inputable to callback list if Not registered
		if( it == callback_KeyPressed.end() )
			callback_KeyPressed.push_back( toReg );

		//Statement to continue on to Key Released in case of "both" registration
		if( state != InputFlags::KeyPressed_KeyReleased )
			break;
	case InputFlags::KeyReleased:
		//Make sure Inputable is not already registered
		for( it = callback_KeyReleased.begin();
			 it != callback_KeyReleased.end(); it++)
		{
			if( (*it) == toReg )
				break;
		}
		
		//Adding Inputable to callback list if Not registered
		if( it == callback_KeyReleased.end() )
			callback_KeyReleased.push_back( toReg );

		break;
	default:
		break;
	}
}

void KeyEvent::deregisterInputable( Inputable* toDereg, InputFlags::KeyFlag state)
{
	std::list< Inputable* >::iterator it;

	switch( state )
	{
	case InputFlags::KeyPressed_KeyReleased:
	case InputFlags::KeyPressed:
		//Finding Inputable to deRegister from list
		for( it = callback_KeyPressed.begin();
			 it != callback_KeyPressed.end(); it++)
		{
			if( (*it) == toDereg )
			{
				(*it) = NULL;
				callback_KeyPressed.erase(it);
				break;
			}
		}

		//Statement to continue on to Key Released in case of "both" deregistration
		if( state != InputFlags::KeyPressed_KeyReleased )
			break;
	case InputFlags::KeyReleased:
		//Finding Inputable to deRegister from list
		for( it = callback_KeyReleased.begin();
			 it != callback_KeyReleased.end(); it++)
		{
			if( (*it) == toDereg )
			{
				(*it) = NULL;
				callback_KeyReleased.erase(it);
				break;
			}
		}

		break;
	default:
		break;
	}
}





void KeyEvent::keyPressed()
{
	for( std::list< Inputable* >::iterator it = callback_KeyPressed.begin();
		 it != callback_KeyPressed.end(); it++)
	{                
		(*it)->keyPressed( key, mod_ctrl, mod_shift, mod_alt );
	}
}
void KeyEvent::keyReleased()
{
	for( std::list< Inputable* >::iterator it = callback_KeyReleased.begin();
		 it != callback_KeyReleased.end(); it++)
	{
		(*it)->keyReleased( key, mod_ctrl, mod_shift, mod_alt );
	}
}