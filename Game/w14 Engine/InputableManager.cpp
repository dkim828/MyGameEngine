#include "InputableManager.h"

#include "KeyEvent.h"


InputableManager::InputableManager()
{
}

InputableManager::~InputableManager()
{
	std::map< AZUL_KEY, KeyEvent* >::iterator it;

	for( it = keyMap.begin();
		it != keyMap.end(); it++)
	{
		delete (*it).second;
	}

	keyMap.clear();
}

void InputableManager::update()
{
	std::map< AZUL_KEY, KeyEvent* >::iterator it;

	for( it = keyMap.begin();
		it != keyMap.end(); it++)
	{
		(*it).second->update();
	}
}
void InputableManager::registerKey( Inputable* toReg, AZUL_KEY key, InputFlags::KeyFlag state )
{
	std::map< AZUL_KEY, KeyEvent* >::iterator it;
	it = keyMap.find( key );

	//If Key does not exist;
	if( it == keyMap.end() )
	{
		keyMap[ key ] = new KeyEvent( key );
	}

	keyMap[ key ]->registerInputable( toReg, state );
}
void InputableManager::deregisterKey( Inputable* toDereg, AZUL_KEY key, InputFlags::KeyFlag state )
{
	std::map< AZUL_KEY, KeyEvent* >::iterator it;
	it = keyMap.find( key );

	//If Key does not exist;
	if( it == keyMap.end() )
	{
		printf("Trying to DeRegister a key that does not exist");
	}
	//if Key DOES exist
	else
		keyMap[ key ]->deregisterInputable( toDereg, state );
}
	