#include "FloatingCamera.h"

FloatingCam::FloatingCam( int in, bool perm ) : W14Camera(in, perm)
{
	// Camera vars 
	CamPos = Vect(0,80,-50.0);	
	this->CamRot = Matrix( IDENTITY );	// No rotation initially
	this->CamTranSpeed = 0;
	this->CamRotSpeed = 0;

	int width = CameraManager::getScreenWidth();
	int height = CameraManager::getScreenHeight();

	pCam->setViewport( 0, 0, width, height);
	pCam->setPerspective( 45, float(width)/float(height), 1, 5000);

	// Position and Orient Camera
	//      First: we create a rotation matrix pointing (Z) towards the target
	Vect Target(0,0,60);
	CamRot = Matrix( Quat( ROT_ORIENT, Target - CamPos, CamUp) );

	//		Second: we set the camera to its position and pointing toward the target
	pCam->setOrientAndPosition( CamUp * CamRot, CamPos + CamDir * CamRot, CamPos);

	// Computes all the internal parameters for the camera
	pCam->updateCamera();
}

FloatingCam::FloatingCam( float FoV, const Vect& pointTo, const Vect& camPos, int in, bool perm ): W14Camera(in, perm)
{
	// Camera vars 
	this->CamPos = camPos;	
	this->CamRot = Matrix( IDENTITY );	// No rotation initially
	this->CamTranSpeed = 0;
	this->CamRotSpeed = 0;

	int width = CameraManager::getScreenWidth();
	int height = CameraManager::getScreenHeight();

	pCam->setViewport( 0, 0, width, height);
	pCam->setPerspective( FoV, float(width)/float(height), 1, 5000);

	// Position and Orient Camera
	//      First: we create a rotation matrix pointing (Z) towards the target
	CamRot = Matrix( Quat( ROT_ORIENT, pointTo - CamPos, CamUp) );

	//		Second: we set the camera to its position and pointing toward the target
	pCam->setOrientAndPosition( CamUp * CamRot, CamPos + CamDir * CamRot, CamPos);

	// Computes all the internal parameters for the camera
	pCam->updateCamera();

}

FloatingCam::~FloatingCam()
{
}

void FloatingCam::update()
{
}