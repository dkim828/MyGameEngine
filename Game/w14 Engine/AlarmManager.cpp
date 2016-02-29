#include "AlarmManager.h"

#include "TimeManager.h"
#include "AlarmMarker.h"
#include "Alarmable.h"


AlarmManager::AlarmManager()
{
}
AlarmManager::~AlarmManager()
{	
	std::multimap< float, AlarmMarker* >::iterator it;

	for( it = timeLine.begin(); it != timeLine.end(); it++)
	{
		//deleting AlarmMarker
		delete it->second;
	}

	timeLine.clear();
}


void AlarmManager::registerAlarm( Alarmable* a, Alarm::ID id)
{
	float timeTrigger = a->getTimeTrigger(id);
	timeLine.insert( std::pair< float, AlarmMarker* >( timeTrigger, new AlarmMarker(a, id) ) );
}
void AlarmManager::deregisterAlarm( Alarmable* a, Alarm::ID id)
{ /*
	float timeTrigger = a->getTimeTrigger(id);

	std::multimap< float, AlarmMarker* >::iterator it;
	it = timeLine.find( timeTrigger );
	
	//The key/Time Trigger for the deregistering alarm is found
	if( it != timeLine.end() )
	{
		//iterating through all the pairs that have the wanted timeTriggers
		while( it->first == timeTrigger )
		{
			//If deregistering Alarable is the Alarable of an AlarmMarker
			if( it->second->getAlarmable() == a )
			{
				//if deregistering AlarmID is the AlarmID of the AlarmMarker
				if( it->second->getAlarmID() == id )
				{
					//deregistering and deleting the AlarmMarker
					delete it->second;
					timeLine.erase( it );
					break;
				}
			}

			it++;
		}
	}*/
	
	std::multimap< float, AlarmMarker* >::iterator it;
	std::multimap< float, AlarmMarker* >::iterator temp;
	it = timeLine.begin();
	
	//iterating through all the pairs
	while( it != timeLine.end()  )
	{
		if( it->second->getAlarmable() == a )
		{
			//if deregistering AlarmID is the AlarmID of the AlarmMarker
			if( it->second->getAlarmID() == id )
			{
				//deregistering and deleting the AlarmMarker
				delete it->second;
				timeLine.erase( it );
				break;
			}
		}
		++it;
	}

}
void AlarmManager::deregisterAllAlarms( Alarmable* a )
{
	std::multimap< float, AlarmMarker* >::iterator it;
	std::multimap< float, AlarmMarker* >::iterator temp;
	it = timeLine.begin();
	
	//iterating through all the pairs
	while( it != timeLine.end()  )
	{
		if( it->second->getAlarmable() == a )
		{
			delete it->second;

			temp = it;
			temp++;
			timeLine.erase( it );

			it = temp;
		}
		else
			++it;
	}

}

void AlarmManager::moveAlarm( Alarmable* a, Alarm::ID id, float newTime )
{
	float oldTimeTrigger = a->getTimeTrigger(id);

	std::multimap< float, AlarmMarker* >::iterator it;
	it = timeLine.find( oldTimeTrigger );
	
	AlarmMarker* alarmMarkerToMove;

	//The key/Time Trigger for the deregistering alarm is found
	if( it != timeLine.end() )
	{
		//iterating through all the pairs that have the wanted timeTriggers
		while( it->first == oldTimeTrigger )
		{
			//If deregistering Alarable is the Alarable of an AlarmMarker
			if( it->second->getAlarmable() == a )
			{
				//if deregistering AlarmID is the AlarmID of the AlarmMarker
				if( it->second->getAlarmID() == id )
				{
					//deregistering and deleting the AlarmMarker
					alarmMarkerToMove = it->second;
					timeLine.erase( it );
					break;
				}
			}

			it++;
		}
	}

	timeLine.insert( std::pair< float, AlarmMarker* >( newTime, alarmMarkerToMove ) );
}

void AlarmManager::update()
{
	std::multimap< float, AlarmMarker* >::iterator it;
	it = timeLine.begin();

	//if timeLine is not empty &&
	//if current time is >= to earliest time trigger
	while( it != timeLine.end()	&&
		   TimeManager::getTotalTime() >= it->first  )
	{
		//do callback for alarm
		it->second->dispatchAlarm();

		//deregister and delete AlarmMarker
		delete it->second;
		timeLine.erase( it );

		//check Top again
		it = timeLine.begin();
	}
}
