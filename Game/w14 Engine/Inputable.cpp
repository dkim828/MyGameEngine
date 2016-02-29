#include "Inputable.h"

#include  "SceneManager.h"
#include "Scene.h"
#include "InputableManager.h"

void Inputable::registerKeyboardKey( AZUL_KEY key, InputFlags::KeyFlag state )
{
	SceneManager::getCurrentScene()->getInputableMan()->registerKey( this, key, state );
}
void Inputable::deregisterKeyboardKey( AZUL_KEY key, InputFlags::KeyFlag state )
{
	SceneManager::getCurrentScene()->getInputableMan()->deregisterKey( this, key, state );
}