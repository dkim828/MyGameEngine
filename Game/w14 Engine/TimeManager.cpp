#include "TimeManager.h"

TimeManager* TimeManager::timeManagerInst = NULL;

TimeManager::TimeManager()
{
	StopWatch::initStopWatch();

	totalTime.tic();
	frameTime.tic();
}

TimeManager::~TimeManager()
{
	timeManagerInst = 0;
}
void TimeManager::destroy()
{
	delete timeManagerInst;
}

float TimeManager::getFrameTime()
{
	return instance().privGetFrameTime();
}
float TimeManager::getTotalTime()
{
	return instance().privGetTotalTime();
}
void TimeManager::update()
{
	instance().privUpdate();
}
float TimeManager::getTimePerLoop()
{
//	return frameTime.timeInSeconds();
	return 0.0f;
}

float TimeManager::privGetFrameTime()
{
	return frameTime.timeInSeconds();
}
float TimeManager::privGetTotalTime()
{
	return totalTime.timeInSeconds();
}

void TimeManager::privUpdate()
{
	totalTime.toc();
	frameTime.toc();
	  
    frameTimeSum += frameTime.timeInSeconds();  
    
    freezeFrameProcessing();

	frameTime.tic();
}

void TimeManager::waitForRelease(AZUL_KEY k)
{
    while( InputMan::GetKeyboard()->GetKeyState(k)  )
        glfwPollEvents();
}

void TimeManager::freezeFrameProcessing()
{
    static bool freeze_mode_active = false;
	 
    if ( InputMan::GetKeyboard()->GetKeyState(FREEZE_KEY) || freeze_mode_active )   
    {
        waitForRelease( FREEZE_KEY );

        freeze_mode_active = true;
        bool single_frame = false;

        while( freeze_mode_active && ! single_frame  )
        {
            //cancel freeze
            if (InputMan::GetKeyboard()->GetKeyState(FREEZE_KEY)) 
            {
                waitForRelease( FREEZE_KEY );
                freeze_mode_active = false;
                single_frame = false;
            }
            //go one frame
            else if (InputMan::GetKeyboard()->GetKeyState(SINGLE_FRAME_KEY)) 
            {
                waitForRelease( SINGLE_FRAME_KEY );
                single_frame = true;
            }

			//rescan keyboard
            glfwPollEvents(); 
        }
    }
}
