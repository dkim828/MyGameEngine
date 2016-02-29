#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include "Inputable.h"
#include "Azul.h"


class CameraController : public Inputable
{
public:
	CameraController();
	~CameraController();

	void setToScene();

	//FROM Inputable
	virtual void keyPressed( AZUL_KEY k, bool Ctrl, bool Shift, bool Alt );
	virtual void keyReleased(  AZUL_KEY k, bool Ctrl, bool Shift, bool Alt );
};


#endif