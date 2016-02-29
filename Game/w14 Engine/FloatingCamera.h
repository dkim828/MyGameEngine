#ifndef FLOATINGCAMERA_H
#define FLOATINGCAMERA_H

#include "W14Camera.h"

class FloatingCam : public W14Camera
{
public:
	/**
	\brief default Construction of Floating Camera

	Field of View is set to 45
	Position is ( 0, 80, -50.0 )
	Points to ( 0, 0, 60 ) //Down to Z-axis
	*/
	FloatingCam( int in, bool perm );
	/**
	\param	FoV		Field of view in DEGREES
	\param	pointTo	Position in space for Camera to look towards
	\param	camPos	Position in space where Camera is located
	*/
	FloatingCam( float FoV, const Vect& pointTo, const Vect& camPos, int in, bool perm );
	virtual ~FloatingCam();


	virtual void update();


private:
};



#endif