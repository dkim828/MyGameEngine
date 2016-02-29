#include "CameraManager.h"

#include "CameraController.h"

#include "MovingCamera.h"
#include "FloatingCamera.h"
#include "FollowCamera.h"

#include <assert.h>

#include "Tools\Visualizer.h"

#define SHOWCAMS

CameraManager* CameraManager::camManInst = 0;

//Initializing static const members of W14Camera objects
//CamUp and CamDir
const Vect W14Camera::CamUp  = Vect(0,1,0);// Using local Y axis as 'Up'
const Vect W14Camera::CamDir = Vect(0,0,1);// Using the local Z axis as 'forward'

CameraManager::CameraManager()
{
}
void CameraManager::init( int width, int height )
{
	instance()->privInit( width, height ) ;
}
void CameraManager::privInit( int width, int height )
{
	this->screenHeight = height;
	this->screenWidth = width;

	//Happens if User has not specified cameras to use
	if( camList.empty() )
	{
		camList.push_back( new MoveCam(90,  Vect(0, 0, 0), Vect( 0, 200, -1), 0, true) );
		activeCamID = 0;
	}

	CameraMan::CameraManagerOverride();
	CameraMan::setCurrent( camList[activeCamID]->getCamera() );

	this->controller = new CameraController();
}
CameraManager::~CameraManager()
{
	camManInst = 0;
	delete this->controller;

	if( !camList.empty() )
	{
		camList.front()->giveToAzulCamMan();//HACK BECAUSE DON'T WANT TO MESS WITH AZUL INTERNALS

		for( auto it = camList.begin(); it != camList.end(); it++ )
		{
			delete ( *it );
		}
	}
}
void CameraManager::destroy()
{
	if( camManInst != 0 )
		delete camManInst;
}
void CameraManager::setInitCamera( int id )
{
	if( id < (int)instance()->camList.size() )
		instance()->activeCamID = id;
	else
		instance()->activeCamID = 0;
}


Camera* CameraManager::getCurrentCam( )
{
	return CameraMan::GetCurrent();
}


int CameraManager::makeStaticCam( float FoV, const Vect& pointTo, const Vect& camPos, bool isPermanent )
{
	return instance()->priv_makeStaticCam( FoV, pointTo, camPos, isPermanent);
}
int CameraManager::priv_makeStaticCam( float FoV, const Vect& pointTo, const Vect& camPos, bool isPermanent )
{
	int index = camList.size();

	W14Camera* cam = new FloatingCam( FoV, pointTo, camPos, index, isPermanent );

	camList.push_back(cam);
	if( !isPermanent )
		sceneCams.push_back( cam );

	return index;
}

int CameraManager::makeMoveCam( float FoV, const Vect& pointTo, const Vect& camPos, bool isPermanent  )
{
	return instance()->priv_makeMoveCam( FoV, pointTo, camPos, isPermanent );
}
int CameraManager::priv_makeMoveCam( float FoV, const Vect& pointTo, const Vect& camPos, bool isPermanent )
{
	int index = camList.size();
	
	W14Camera* cam = new MoveCam( FoV, pointTo, camPos, index, isPermanent  );

	camList.push_back(cam);
	if( !isPermanent )
		sceneCams.push_back( cam );

	return index;
}

int CameraManager::makeFollowCam( float FoV, float offset_Forwards, float offset_Behind, float offset_Above, GameEntity* toFollow )
{
	return instance()->priv_makeFollowCam( FoV, offset_Forwards, offset_Behind, offset_Above, toFollow );
}
int CameraManager::priv_makeFollowCam( float FoV, float offset_Forwards, float offset_Behind, float offset_Above, GameEntity* toFollow )
{
	int index = camList.size();

	W14Camera* cam =  new FollowCam( FoV, offset_Forwards, offset_Behind, offset_Above, toFollow, index );
	camList.push_back( cam );
	sceneCams.push_back( cam );

	return index;
}

void CameraManager::sceneCleanUp()
{
	int index;
	while( !instance()->sceneCams.empty() )
	{
		index = instance()->sceneCams.front()->getIndex();
		delete instance()->camList[ index ];
		instance()->camList[ index ] = 0;
		instance()->sceneCams.pop_front();
	}
}
void CameraManager::sceneStartUp()
{
	instance()->controller->setToScene();

	if( instance()->camList[ instance()->activeCamID] == 0 )
		instance()->priv_cycleCam();
}



void CameraManager::cycleCam()
{
	instance()->priv_cycleCam();
}
void CameraManager::priv_cycleCam()
{
	activeCamID += 1;
	if( activeCamID >= (int)camList.size() )
		activeCamID = 0;
	
	//Find next usable camera from list in case of camera deletions
	while( camList[ activeCamID ] == 0 )
		activeCamID ++;

	CameraMan::setCurrent( camList[activeCamID]->getCamera() );
}
void CameraManager::useCam( int id )
{
	instance()->priv_useCam( id );
}
void CameraManager::priv_useCam( int id )
{
	if( id < (int)camList.size())
	{
		activeCamID = id;

		assert( camList[ activeCamID ] != 0  && "Trying to use invalid camID" );

		CameraMan::setCurrent( camList[activeCamID]->getCamera() );
	}
}

void CameraManager::deleteCam( int id )
{
	instance()->priv_deleteCam( id );
}
void CameraManager::priv_deleteCam( int id )
{
	assert( activeCamID != id && "Trying to delete currently active camera" );

	if( !camList[id]->isPermanent() )
	{
		for( auto it = sceneCams.begin();
			it != sceneCams.end(); ++it )
		{
			if( (*it) == camList[id] )
			{
				sceneCams.erase( it );
				break;
			}
		}
	}

	delete camList[id];
	camList[id] = 0;
}


void CameraManager::update()
{
	instance()->privUpdate();
}
void CameraManager::privUpdate()
{
	camList[ activeCamID ]->update();
	
	//DEBUG to see where Camera is
#ifdef SHOWCAMS
	for( auto it = camList.begin(); it != camList.end(); it++ )
	{
		if( ( *it ) != 0 )
			Visualizer::showPoint( ( *it )->CamPos, Colors::Green );
	}
#endif
}

