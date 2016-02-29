#include "GameEntity.h"

#include "AlarmGlobals.h"
#include "SceneManager.h"
#include "Scene.h"



GameEntity::GameEntity()
{
	registerBasicFunctionality();
	camID = -999;
}
GameEntity::~GameEntity()
{
}


void GameEntity::registerBasicFunctionality()
{
	SceneManager::getCurrentScene()->registerXables( this );
}