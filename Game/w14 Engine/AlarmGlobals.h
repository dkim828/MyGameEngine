#ifndef ALARMGLOBALS_H
#define ALARMGLOBALS_H
/**
\ingroup ALARM

<summary> Each of these flags are associated with which Alarm the user may want to interact
with through Alarmable::setAlarm(), Alarmable::cancelAlarm(), Alarmable::getTimeLeftOnAlarm(),
or Alarmable::addTimeToAlarm().
</summary>
*/
namespace Alarm
{
	enum ID
	{
		ID_0  = 0,
		ID_1  = 1,
		ID_2  = 2
	};

	
	const int MAX_ALARM_EVENTS = 3;
};
#endif //ALARMGLOBALS_H