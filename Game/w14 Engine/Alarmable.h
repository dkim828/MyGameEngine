#ifndef ALARMABLE_H
#define ALARMABLE_H

#include "AlarmGlobals.h"

class Alarmable
{
friend class AlarmManager;
friend class AlarmMarker;

public:
	Alarmable();
	virtual ~Alarmable() {};

	virtual void alarm0(){};
	virtual void alarm1(){};
	virtual void alarm2(){};

protected:
	/**
	\brief A function that is used within GameEntity to set alarms
	\ingroup ALARM

	This function is protected in Alarmable so any derived classes, which includes GameEntity, can call this.

	As mentioned in GameEntity::alarm0(), GameEntity has the functionality of setting an alarm at some future time
	in order to receive a callback through GameEntity::alarm0(), GameEntity::alarm2(), or GameEntity::alarm1(). In
	order to do so, this function is called with specific arguments matching which callback the user wants as well
	as the number of seconds in the future the user may want the callback to happen.

	\b Important: setAlarm() only sets the alarm if it is INACTIVE, meaning it has not been set yet. If you call 
	setAlarm( AlarmID::ID_0, 10 ) and call setAlarm( AlarmID::ID_0, 10 ). The Alarm system will ignore the second
	setAlarm() call because an Alarm 0 is already active. In order to set another alarm time at for Alarm 0, you must
	either first call Alarmable::cancelAlarm(), or change the value of the alarm timer by calling Alarmable::addTimeToAlarm().

	\b Example: Within the Demo's Ship GameEntity, it uses key presses in order to setAlarms as well as call the other
	user accessible alarm functions.a
		\code
		void Ship::keyPressed( AZUL_KEY k, bool Ctrl, bool Shift, bool  )
		{
			// Lots of other Code

			//Alarm Inputs
			if( k == AZUL_KEY::KEY_Z )
			{
				if( Shift )
					addTimeToAlarm( Alarm::ID_0, 5 );
				else if( Ctrl )
					addTimeToAlarm( Alarm::ID_0, -5 );
				else if( Alt )
					cancelAlarm( Alarm::ID_0 );
				else
					setAlarm( Alarm::ID_0, 10);
			}
			if( k == AZUL_KEY::KEY_X )
			{
				if( Shift )
					addTimeToAlarm( Alarm::ID_1, 5 );
				else if( Ctrl )
					addTimeToAlarm( Alarm::ID_1, -5 );
				else if( Alt )
					cancelAlarm( Alarm::ID_1 );
				else
					setAlarm( Alarm::ID_1, 10);
			}
			if( k == AZUL_KEY::KEY_C )
			{
				if( Shift )
					addTimeToAlarm( Alarm::ID_2, 5 );
				else if( Ctrl )
					addTimeToAlarm( Alarm::ID_2, -5 );
				else if( Alt )
					cancelAlarm( Alarm::ID_2 );
				else
					setAlarm( Alarm::ID_2, 10);
		}
		\endcode

		\param	id	An enum value that reflects which Alarm to trigger at a future time
		\param	s	The number of seconds, in float, in the future that the GameEntity will receive a callback for
	*/
	void setAlarm( Alarm::ID id, float s);

	/**
	\brief A function that is used within GameEntity to cancel a single alarm
	\ingroup ALARM

	This function is protected in Alarmable so any derived classes, which includes GameEntity, can call this.

	This is a simple function the user can call to cancel any alarms that may have been set. If this function
	is called on an Alarm that is not active, nothing happens. Otherwise, the alarm is canceled and the passed in
	alarm (Alarm::ID) is set to inactive.

	\b Example: Look at Alarmable::setAlarm()

		\param	id	An enum value that reflects which Alarm to cancel and set inactive.
	*/
	void cancelAlarm( Alarm::ID id );

	/**
	\brief A function that is used within GameEntity to cancel all possible alarms
	\ingroup ALARM

	This function is protected in Alarmable so any derived classes, which includes GameEntity, can call this.

	This is a simple function the user can call to cancel all alarms that may have been set and is active.

	\b Important: cancelAllAlarms() is a necessary function to be called within a GameEntity before the GameEntity
	is either out of scope of the Scene or is destroyed if it is known to be using alarms. An easy place to put call this
	function out of safety is within GameEntity::terminationEvent() function.

	\b Example: Because the Ship GameEntity in the Demo has the potential to have many alarms active at differing times,
	this function is called in the terminationEvent() out of safety in the case that the ship is destroyed when its
	alarms are active.
		\code
		void Ship::terminationEvent()
		{
			deregisterCollision< Ship >( this );

			deregisterKeyboardKey( AZUL_KEY::KEY_W, InputFlags::KeyPressed_KeyReleased );
			deregisterKeyboardKey( AZUL_KEY::KEY_A, InputFlags::KeyPressed_KeyReleased );
			deregisterKeyboardKey( AZUL_KEY::KEY_S, InputFlags::KeyPressed_KeyReleased );
			deregisterKeyboardKey( AZUL_KEY::KEY_D, InputFlags::KeyPressed_KeyReleased );

			deregisterKeyboardKey( AZUL_KEY::KEY_Z, InputFlags::KeyPressed );
			deregisterKeyboardKey( AZUL_KEY::KEY_X, InputFlags::KeyPressed );
			deregisterKeyboardKey( AZUL_KEY::KEY_C, InputFlags::KeyPressed );
			deregisterKeyboardKey( AZUL_KEY::KEY_V, InputFlags::KeyPressed );

			deregisterKeyboardKey( AZUL_KEY::KEY_SPACE, InputFlags::KeyPressed );

			cancelAllAlarms(); //called HERE
		}
		\endcode
	*/
	void cancelAllAlarms( );

	/**
	\brief A function that is used within GameEntity to retrieve the amount of time left before an alarm callback
	\ingroup ALARM

	This function is protected in Alarmable so any derived classes, which includes GameEntity, can call this.

	This function returns a float that represents the number of seconds before a callback is initiated for the Alarm::ID
	passed in as the argument.

	If this function is called on an Alarm that is inactive, it returns -1.

	\b Example:  Look at Alarmable::setAlarm()

		\param	id	An enum value that reflects which Alarm to get seconds until callback
	*/
	float getTimeLeftOnAlarm( Alarm::ID id );

	/**
	\brief A function that is modify an already set alarm
	\ingroup ALARM

	This function is protected in Alarmable so any derived classes, which includes GameEntity, can call this.

	This function literally adds whatever signed float onto trigger time of the passed in Alarm::ID alarm.
	Meaning in order to make the alarm callback happen earlier, the user should pass in a negative number,
	while passing in a positive number in order to make the callback happen later.

	If this function is called for an alarm that is inactive, nothing happens.

	If time is subtracted away from the current time triggering time and the resulting time for the
	alarm callback to happen is negative, meaning that point in time has already happened, the function stops
	its process and leaves the original alarm alone.

	\b Example: Look at Alarmable::setAlarm()

		\param	id	An enum value that reflects which Alarm to cancel and set inactive.
		\param	s	The number of seconds, in float, to modify the specified alarm
	*/
	void addTimeToAlarm( Alarm::ID id, float s );

private:

	/**
	\brief A function used by AlarmManager in order to get proper times to set Alarms for
	\ingroup NOTFORUSER_AL

	This function is private in Alarmable so any derived classes, which includes GameEntity, Cannot touch this.
	Most of the private functions in Alarmable are used for the background alarm managing tasked use by AlarmMarker
	and AlarmManager.

		\param	id	An enum value that reflects which Alarm to retrieve the time trigger for
	*/
	float getTimeTrigger( Alarm::ID id );

	/**
	\brief A function called upon AlarmMarker's destruction
	\ingroup NOTFORUSER_AL

	AlarmMarker is a holder of Alarmable(GameEntity) instances and the times to which callback should
	happen.

	The Alarm Manager holds a map of those AlarmMarkers and they are created upon every Alarmable::setAlarm()
	call.

	Whenever an AlarmMarker is destroyed by either Alarmable::cancelAlarm() or Alarmable::cancelAllAlarms(),
	an AlarmMarker is deleted and within the destructor calls this function in order to tell the GameEntity that
	the alarm is not active anymore

		\param	id	An enum value that reflects which Alarm destroy and set inactive
	*/
	void destroyAlarm( Alarm::ID id ); //used for alarmMarker Destructor

	/**
	\brief A function called upon the triggering of an Alarm
	\ingroup NOTFORUSER_AL

	Once the AlarmManager goes through its map and knows that enough time has passed and an alarm callback must happen,
	it calls the current time's correlating AlarmMarkers that call this function.

	This function just holds a switch that uses the passed in Alarm::ID to choose whether to call GameEntity::alarm0(), GameEntity::alarm1(),
	or GameEntity::alarm2();

		\param	id	An enum value that reflects which Alarm callback to Call
	*/
	void dispatchAlarm( Alarm::ID id);



	float timeTrigger[ Alarm::MAX_ALARM_EVENTS ];


};


#endif //ALARMABLE_H