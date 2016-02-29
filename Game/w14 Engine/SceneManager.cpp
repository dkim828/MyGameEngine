#include "SceneManager.h"
#include "Scene.h"

#include "CameraManager.h"

SceneManager* SceneManager::SceneManagerInst = NULL;


SceneManager::SceneManager()
{
}
SceneManager::~SceneManager()
{
	SceneManagerInst = 0;
	
	delete currentScene;
}
void SceneManager::destroy()
{
	delete SceneManagerInst;
}


void SceneManager::drawCurrentScene()
{
	instance().currentScene->drawScene();
}


void SceneManager::updateCurrentScene()
{
	instance().internalChangeScene();
	instance().currentScene->updateScene();
}
void SceneManager::internalChangeScene()
{
	if( currentScene != nextScene )
	{
		currentScene->endScene();
		CameraManager::sceneCleanUp();
		delete currentScene;

		//make the next scene current
		//and initialize it
		currentScene = nextScene;
		currentScene->initScene();
		CameraManager::sceneStartUp();
	}
}


void SceneManager::setStartScene( Scene* s )
{
	instance().privSetStartScene( s );
}
void SceneManager::privSetStartScene( Scene* s )
{
	currentScene = s;
	nextScene = s;

	currentScene->initScene();

	CameraManager::sceneStartUp();
}


void SceneManager::setNextScene( Scene* s )
{
	instance().privSetNextScene( s );
}
void SceneManager::privSetNextScene( Scene * s )
{
	nextScene = s;
}