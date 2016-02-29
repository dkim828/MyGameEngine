#include "TerminateableManager.h"
#include "Terminateable.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameEntity.h"

TerminateableManager::~TerminateableManager()
{
	processTerminationEvents();
}

void TerminateableManager::processTerminationEvents()
{
	for( std::list< Terminateable* >::iterator it = terminationList.begin();
		it != terminationList.end(); it++ )
	{
		(*it)->terminationEvent();
		SceneManager::getCurrentScene()->deregisterXables( static_cast<GameEntity*>( (*it) ) );
		(*it)->sendToOwner();
	}

	terminationList.clear();
}
	
void TerminateableManager::registerForTermination( Terminateable* t )
{
	for( std::list< Terminateable* >::iterator it = terminationList.begin();
		it != terminationList.end(); it++ )
	{
 		//Entity is already Registered
		if( (*it) == t )
		{
			printf("Terminateable Entity already Registered");
			return;
		}
	}
	//pushback entity to register
	terminationList.push_back( t );
}