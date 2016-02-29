#include "FollowCamera.h"

#include "GameEntity.h"

FollowCam::FollowCam( float FoV, float offset_Forwards, float offset_Behind, float offset_Above, GameEntity* toFollow, int in ) : W14Camera( in, false )
{
	//Default Setup of Camera 
	int width = CameraManager::getScreenWidth();
	int sheight = CameraManager::getScreenHeight();

	pCam->setViewport( 0, 0, width, sheight);
	pCam->setPerspective( FoV, float(width)/float(sheight), 1, 5000);

	//Setting Entity to Follow
	this->toFollow = toFollow;


	// Camera vars 
	this->toLookOffset = offset_Forwards;
	this->camPosOffset_Above = offset_Above;
	this->camPosOffset_Behind = offset_Behind;

	this->toFollowLocation = Vect(0,0,0 ) * this->toFollow->getTransMatrix();
	
	this->LookAt = this->toFollowLocation - (  Vect( 0, 0, -this->toLookOffset ) * this->toFollow->getRotMatrix()  );
	this->CamPos = this->toFollowLocation + ( Vect( 0, this->camPosOffset_Above, -this->camPosOffset_Behind ) * this->toFollow->getRotMatrix());

	this->CamRot = Matrix( Quat( ROT_ORIENT, LookAt - CamPos, CamUp) );

	this->CamTranSpeed = 0;
	this->CamRotSpeed = 0;


	// Position and Orient Camera
	//      First: we create a rotation matrix pointing (Z) towards the target
	CamRot = Matrix( Quat( ROT_ORIENT, LookAt - CamPos, CamUp) );

	//		Second: we set the camera to its position and pointing toward the target
	pCam->setOrientAndPosition( CamUp * CamRot, CamPos + CamDir * CamRot, CamPos);

	// Computes all the internal parameters for the camera
	pCam->updateCamera();
}

FollowCam::~FollowCam()
{
}

void FollowCam::update()
{
	this->toFollowLocation = Vect(0,0,0 ) * this->toFollow->getTransMatrix();

	this->LookAt = this->toFollowLocation - (  Vect( 0, 0, -this->toLookOffset ) * this->toFollow->getRotMatrix()  );
	this->CamPos = this->toFollowLocation + ( Vect( 0, this->camPosOffset_Above, -this->camPosOffset_Behind ) * this->toFollow->getRotMatrix() );

	this->CamRot = Matrix( Quat( ROT_ORIENT, LookAt - CamPos, CamUp) );

	pCam->setOrientAndPosition( CamUp * CamRot, CamPos + CamDir * CamRot, CamPos);


	pCam->updateCamera();
}