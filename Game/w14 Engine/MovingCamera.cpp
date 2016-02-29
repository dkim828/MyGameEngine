#include "MovingCamera.h"

MoveCam::MoveCam(int in, bool perm) : W14Camera( in, perm )
{
	// Camera vars 
	CamPos = Vect(0,100,-110.0);	
	CamRot = Matrix( IDENTITY );	// No rotation initially
	CamTranSpeed = 4;
	CamRotSpeed = .02f;

	int width = CameraManager::getScreenWidth();
	int height = CameraManager::getScreenHeight();

	pCam->setViewport( 0, 0, width, height);
	pCam->setPerspective( 45, float(width)/float(height), 1, 5000);

	// Position and Orient Camera
	//      First: we create a rotation matrix pointing (Z) towards the target
	Vect Target(0,0,60);
	CamRot = Matrix( Quat( ROT_ORIENT, Target - CamPos, CamUp));

	//		Second: we set the camera to its position and pointing toward the target
	pCam->setOrientAndPosition( CamUp * CamRot, CamPos + CamDir * CamRot, CamPos);

	// Computes all the internal parameters for the camera
	pCam->updateCamera();
}
MoveCam::MoveCam( float FoV, const Vect& pointTo, const Vect& camPos, int in, bool perm ) : W14Camera( in,perm )
{
	// Camera vars 
	this->CamPos = camPos;	
	this->CamRot = Matrix( IDENTITY );	// No rotation initially
	this->CamTranSpeed = 2;
	this->CamRotSpeed = .02f;

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

MoveCam::~MoveCam()
{
}

void MoveCam::update()
{
	// Camera translation movement (not using time-based values for simplicity)
	if ( InputMan::GetKeyboard()->GetKeyState(AZUL_KEY::KEY_I ) )
	{
		CamPos += Vect(0,0,1) * CamRot * CamTranSpeed;
	}
	else if ( InputMan::GetKeyboard()->GetKeyState(AZUL_KEY::KEY_K ) )
	{
		CamPos += Vect(0,0,1) * CamRot * - CamTranSpeed;
	}

	if ( InputMan::GetKeyboard()->GetKeyState(AZUL_KEY::KEY_J ) )
	{
		CamPos += Vect(1,0,0) * CamRot * CamTranSpeed;
	}
	else if ( InputMan::GetKeyboard()->GetKeyState(AZUL_KEY::KEY_L ) )
	{
		CamPos += Vect(1,0,0) * CamRot * -CamTranSpeed;
	}

	// Camera Rotation movement (not using time-based values for simplicity)
	if ( InputMan::GetKeyboard()->GetKeyState(AZUL_KEY::KEY_LEFT ) )
	{
		CamRot *= Matrix( ROT_Y, CamRotSpeed );
	}
	else if ( InputMan::GetKeyboard()->GetKeyState(AZUL_KEY::KEY_RIGHT ) )
	{
		CamRot *= Matrix( ROT_Y, -CamRotSpeed );
	}

	if ( InputMan::GetKeyboard()->GetKeyState(AZUL_KEY::KEY_UP ) )
	{
		CamRot *= Matrix( Quat( ROT_AXIS_ANGLE, Vect(1,0,0) * CamRot, -CamRotSpeed) );
	}
	else if ( InputMan::GetKeyboard()->GetKeyState(AZUL_KEY::KEY_DOWN ) )
	{
		CamRot *= Matrix( Quat( ROT_AXIS_ANGLE, Vect(1,0,0) * CamRot, CamRotSpeed) );
	}

	// Update the camera settings
	pCam->setOrientAndPosition( CamUp * CamRot, CamPos + CamDir * CamRot, CamPos);
	pCam->updateCamera();
}