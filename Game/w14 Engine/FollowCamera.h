#ifndef FOLLOWCAMERA_H
#define FOLLOWCAMERA_H

#include "W14Camera.h"

class GameEntity;

class FollowCam : public W14Camera
{
public:
	/**
	\param	FoV					Field of view in DEGREES
	\param	offset_Forwards		This value is how far ahead of GameEntity for Camera to look
	\param	offset_Behind		This value is how far behind of GameEntity the Camera is to be
	\param	offset_Above		This value is how far above of GameEntity the Camera is to be
	\param	toFollow			GameEntity to follow
	*/
	FollowCam( float FoV, float offset_Forwards, float offset_Behind, float offset_Above, GameEntity* toFollow, int in );

	virtual ~FollowCam();

	virtual void update();

private:
	//Not Allowing use of default Constructor for FollowCamera
	FollowCam();

	GameEntity* toFollow;
	Vect LookAt;

	Vect toFollowLocation;

	float toLookOffset;
	float camPosOffset_Behind;
	float camPosOffset_Above;
	
};

#endif