#ifndef W14CAMERA_H
#define W14CAMERA_H

#include "Azul.h"
#include "CameraManager.h"

class W14Camera
{
friend class CameraManager;

public:
	W14Camera( int in, bool perm )
	{
		pCam = new Camera();
		this->index = in;
		this->isPerm = perm;
	}
	virtual ~W14Camera()
	{
		delete pCam;
	}
	void giveToAzulCamMan()
	{
		//HACK BECAUSE DON'T WANT TO MESS WITH AZUL INTERNALS
		CameraMan::setCurrent( pCam );
		pCam = 0;
	}


	Camera* getCamera()
	{
		return pCam;
	}
	virtual void update() = 0;


	int getIndex(){ return index; };
	bool isPermanent(){ return isPerm; };
protected:
	Camera* pCam;
	int index;
	bool isPerm;

	Vect CamPos;	
	Matrix CamRot;
	static const Vect CamUp;
	static const Vect CamDir;
	float CamTranSpeed;
	float CamRotSpeed;
};

#endif