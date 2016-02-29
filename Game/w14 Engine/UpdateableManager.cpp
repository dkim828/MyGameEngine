#include "UpdateableManager.h"
#include "Updateable.h"


#include "Tools/ErrorOut.h"

UpdateableManager::UpdateableManager()
{
}
UpdateableManager::~UpdateableManager()
{
	//clear drawable list
	//actual delete is on Terminable
	updateableList.clear();
}


void UpdateableManager::update()
{
	for( std::list< Updateable* >::iterator it = updateableList.begin();
		it != updateableList.end(); it++ )
	{
		(*it)->update();
	}
}

void UpdateableManager::registerUpdateable( Updateable* toReg )
{
	for( std::list< Updateable* >::iterator it = updateableList.begin();
		it != updateableList.end(); it++ )
	{
		//Entity is already Registered
		if( (*it) == toReg )
		{
			ErrorOut::debugOut("Updateable Entity already Registered");
			return;
		}
	}
	//pushback entity to register
	updateableList.push_back( toReg );
}

void UpdateableManager::deregisterUpdateable( Updateable* toDereg )
{ 
	std::list< Updateable* >::iterator it;
	for( it = updateableList.begin();
		 it != updateableList.end() ; it++ )
	{
		//Entity is found
		if( (*it) == toDereg )
		{
			break;
		}
	}

	//Updateable Entity to Deregister was not found
	if( it == updateableList.end() )
	{
		ErrorOut::debugOut("Updateable Entity to DeRegister is not registered");
	}
	//Updateable Entity to Deregister was Found
	else
	{
		updateableList.erase(it);
	}
}
