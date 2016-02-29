#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include "Azul.h"

#include <vector>
#include <list>

class W14Camera;
class GameEntity;
class CameraController;

class CameraManager
{
	friend class SceneManager;
public:
	static void setInitCamera( int id );

	/**
	\param	FoV		Field of view in DEGREES
	\param	pointTo	Position in space for Camera to look towards
	\param	camPos	Position in space where Camera is located
	*/
	static int makeStaticCam( float FoV, const Vect& pointTo, const Vect& camPos, bool isPermanent );
	/**
	\param	FoV		Field of view in DEGREES
	\param	pointTo	Initial position in space for Camera to look towards
	\param	camPos	Initial position in space where Camera is located
	*/
	static int makeMoveCam( float FoV, const Vect& pointTo, const Vect& camPos, bool isPermanent );

	static int makeFollowCam( float FoV, float offset_Forwards, float offset_Behind, float offset_Above, GameEntity* toFollow );

	
	static void cycleCam();
	/**
	IF ID DOES NOT EXIST, GAME WILL CRASH
	*/
	static void useCam( int id );
	
	/**
	IF ID IS CURRENTLY ACTIVE CAMERA, GAME WILL CRASH
	*/
	static void deleteCam( int id );

	
	static Camera* getCurrentCam( );

	static void init(int width, int height);
	static void update();
	static void destroy();

	static int getScreenWidth(){ return instance()->screenWidth; };
	static int getScreenHeight(){ return instance()->screenHeight; };



private:
	std::vector< W14Camera* > camList;
	int activeCamID;

	std::list< W14Camera* > sceneCams;

	CameraController* controller;


	int screenWidth;
	int screenHeight;

	static void sceneStartUp();
	static void sceneCleanUp();

	//===========================================================================//
	//PRIVATE helpers for Static functions
	//===========================================================================//
	void privInit( int width, int height );
	void privUpdate();

	int priv_makeStaticCam( float FoV, const Vect& pointTo, const Vect& camPos, bool isPermanent );
	int priv_makeMoveCam( float FoV, const Vect& pointTo, const Vect& camPos, bool isPermanent );
	int priv_makeFollowCam( float FoV, float offset_Forwards, float offset_Behind, float offset_Above, GameEntity* toFollow );
	
	void priv_cycleCam();
	void priv_useCam( int id );
	void priv_deleteCam( int id );


	//===========================================================================//
	//SINGLETON STUFF
	//===========================================================================//
	CameraManager();
	CameraManager( const CameraManager& ) {};
	CameraManager& operator=( const CameraManager& ) {};
	~CameraManager();

	static CameraManager* camManInst;

	static CameraManager* instance()
	{
		if( camManInst == 0 )
			camManInst = new CameraManager();

		return camManInst;
	}
};


#endif 