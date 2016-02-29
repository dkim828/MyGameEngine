#include "CameraManager.h"
#include "CameraController.h"


CameraController::CameraController()
{
}
CameraController::~CameraController()
{
}

void CameraController::setToScene()
{
	registerKeyboardKey( AZUL_KEY::KEY_HOME, InputFlags::KeyPressed );
}

void CameraController::keyPressed( AZUL_KEY k, bool , bool , bool  )
{
	if( k == AZUL_KEY::KEY_HOME )
	{
		CameraManager::cycleCam();
	}
}
void CameraController::keyReleased( AZUL_KEY, bool , bool , bool  )
{
}