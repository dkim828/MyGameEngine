#ifndef INPUTABLEMANAGER_H
#define INPUTABLEMANAGER_H

#include "Azul.h"
#include "InputGlobals.h"

#include <map>


class KeyEvent;
class Inputable;

class InputableManager
{
public:
	InputableManager();
	InputableManager( const InputableManager& ) {};
	~InputableManager();

	void update();

	void registerKey( Inputable* toReg, AZUL_KEY key, InputFlags::KeyFlag state );
	void deregisterKey( Inputable* toDereg, AZUL_KEY key, InputFlags::KeyFlag state );

private:
	std::map< AZUL_KEY, KeyEvent* > keyMap; 
};

#endif INPUTABLEMANAGER_H