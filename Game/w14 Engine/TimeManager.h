#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include "Azul.h"

class TimeManager
{
public:
	static void init(){};

	//Clean Up
	static void destroy();

	static float getFrameTime();
	static float getTotalTime();
	static float getTotalGameTime();

	static float getTimePerLoop();

	static void update();

private:
	static const AZUL_KEY FREEZE_KEY = AZUL_KEY::KEY_F12;
	static const AZUL_KEY SINGLE_FRAME_KEY = AZUL_KEY::KEY_F11;

	//Instance Variables
	StopWatch frameTime;
	StopWatch totalTime;
	float frameTimeSum;

	float deltaTime;


	//Private Functions
	float privGetFrameTime();
	float privGetTotalTime();
	void privUpdate();

	void freezeFrameProcessing();
	void waitForRelease( AZUL_KEY k );



	//Singleton Instance
	static TimeManager* timeManagerInst;
	
	//PRIVATE Constructor/Destructor
	TimeManager();
	TimeManager( const TimeManager& ) {};
	~TimeManager();

	//Singular Instance Access
	static TimeManager& instance()
	{
		if( !timeManagerInst )
			timeManagerInst = new TimeManager();

		return *timeManagerInst;
	};

};

#endif TIMEMANAGER_H