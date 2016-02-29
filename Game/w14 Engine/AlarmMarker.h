#ifndef ALARMMARKER_H
#define ALARMMARKER_H

#include "AlarmGlobals.h"

class Alarmable;

class AlarmMarker
{
public:
	AlarmMarker( Alarmable* ptr, Alarm::ID id );
	AlarmMarker( const AlarmMarker& ) {};
	~AlarmMarker();

	Alarm::ID getAlarmID();
	Alarmable* getAlarmable();

	void dispatchAlarm();

private:
	Alarmable* alarmableToCall;
	Alarm::ID alarmID;
};

#endif //ALARMMARKER_H