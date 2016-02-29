#include "AlarmMarker.h"

#include "Alarmable.h"


AlarmMarker::AlarmMarker( Alarmable* ptr, Alarm::ID id )
{
	alarmableToCall = ptr;
	alarmID = id;
}
AlarmMarker::~AlarmMarker()
{
	alarmableToCall->destroyAlarm( alarmID );
}

Alarm::ID AlarmMarker::getAlarmID()
{
	return alarmID;
}
Alarmable* AlarmMarker::getAlarmable()
{
	return alarmableToCall;
}

void AlarmMarker::dispatchAlarm()
{
	alarmableToCall->dispatchAlarm( alarmID );
}