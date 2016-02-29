#include "Alarmable.h"

#include "SceneManager.h"
#include "Scene.h"
#include "AlarmManager.h"
#include "TimeManager.h"

#include "Tools/ErrorOut.h"

Alarmable::Alarmable()
{
	//defaulting all the TimeTriggers to -1
	//-1 means Alarm is NOT active
	for( int i = 0; i < Alarm::MAX_ALARM_EVENTS; i++)
	{
		timeTrigger[i] = -1.0f;
	}
}
	

float Alarmable::getTimeTrigger( Alarm::ID id )
{
	return timeTrigger[ (int) id ];
}

void Alarmable::setAlarm( Alarm::ID id, float s)
{
	//if alarm id is an inactive alarm
	if( timeTrigger[ (int)id ] == -1.0f )
	{
		//set proper timeTrigger
		timeTrigger[ (int)id ] = TimeManager::getTotalTime() + s;

		 //register alarm
		SceneManager::getCurrentScene()->getAlarmMan()->registerAlarm( this, id);
	}
}

void Alarmable::cancelAlarm( Alarm::ID id )
{
	//if alarm id is an active alarm
//	if( timeTrigger[ (int)id ] != -1.0f )
//	{
		//deregister alarm
		SceneManager::getCurrentScene()->getAlarmMan()->deregisterAlarm( this, id);

		//Set TimeTrigger to -1 to denote alarm inactive
		timeTrigger[ (int)id ] = -1.0f;
//	}
}

void Alarmable::cancelAllAlarms( )
{
	//deregister alarm
	SceneManager::getCurrentScene()->getAlarmMan()->deregisterAllAlarms( this );
}

float Alarmable::getTimeLeftOnAlarm( Alarm::ID id )
{
	//if alarm id is an active alarm
	if ( timeTrigger[ (int)id ] != -1.0f )
	{
		return timeTrigger[ (int)id ] - TimeManager::getTotalTime();
	}
	else
		return -1;
}
void Alarmable::addTimeToAlarm( Alarm::ID id, float s )
{
	//if alarm id is an active alarm
	if ( timeTrigger[ (int)id ] != -1.0f )
	{
		float newTime = timeTrigger[ (int)id ] + s;
		
		//making sure new time is still in future in case of subtraction
		if( newTime > TimeManager::getTotalTime() )
		{
			SceneManager::getCurrentScene()->getAlarmMan()->moveAlarm( this, id, newTime );

			//set proper timeTrigger
			timeTrigger[ (int)id ] = newTime;
		}
	}
}

void Alarmable::destroyAlarm( Alarm::ID id )
{
	//Set TimeTrigger to -1 to denote alarm inactive
	timeTrigger[ (int)id ] = -1.0f;
}

void Alarmable::dispatchAlarm( Alarm::ID id)
{
	//Set TimeTrigger to -1 to denote alarm inactive
	timeTrigger[ (int)id ] = -1.0f;

	switch( id )
	{
	case Alarm::ID_0:
		alarm0();
		break;
	case Alarm::ID_1:
		alarm1();
		break;
	case Alarm::ID_2:
		alarm2();
		break;
	default:
		ErrorOut::debugOut("Trying to dispatch out of bounds alarm ID");
		exit(EXIT_FAILURE);
	}
}