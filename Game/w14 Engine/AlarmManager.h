#ifndef ALARMMANAGER_H
#define ALARMMANAGER_H


#include <map>
#include "AlarmGlobals.h"

class Alarmable;
class AlarmMarker;

class AlarmManager
{
public:
	AlarmManager();
	AlarmManager( const AlarmManager& ){};
	~AlarmManager();

	void registerAlarm( Alarmable* a, Alarm::ID id);
	void deregisterAlarm( Alarmable* a, Alarm::ID id);
	void deregisterAllAlarms( Alarmable* a );
	void moveAlarm( Alarmable* a, Alarm::ID id, float newTime );

	void update();

private:
	std::multimap< float, AlarmMarker* > timeLine;

};

#endif //ALARMMANAGER_H