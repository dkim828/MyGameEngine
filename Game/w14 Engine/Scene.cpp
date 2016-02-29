#include "Scene.h"

#include "AlarmManager.h"
#include "InputableManager.h"
#include "UpdateableManager.h"
#include "DrawableManager.h"
#include "CollisionManager.h"
#include "TerminateableManager.h"

#include "TerminateableDumpster.h"

#include "TerrainManager.h"

#include "GameEntity.h"
#include "Tools\ErrorOut.h"
#include "CameraManager.h"

Scene::Scene()
{
	inputableMan = new InputableManager();
	drawableMan = new DrawableManager();
	updateableMan = new UpdateableManager();
	alarmMan = new AlarmManager();
	collisionMan = new CollisionManager();
	terminateableMan = new TerminateableManager();

	this->terrainMan = new TerrainManager();

	dumpster = new TerminateableDumpster();
}
Scene::~Scene()
{
	//deleting managers
	delete terminateableMan;

	delete inputableMan;
	delete drawableMan;
	delete updateableMan;
	delete alarmMan;
	delete collisionMan;

	delete this->terrainMan;

	delete dumpster;
}

void Scene::registerXables( GameEntity* toReg )
{
	ErrorOut::debugOut("++++++++Auto registerXablesCalled++++++++++");

	updateableMan->registerUpdateable( static_cast<Updateable*>(toReg) );
	drawableMan->registerDrawable( static_cast<Drawable*>(toReg) );
}
void Scene::deregisterXables( GameEntity* toDereg )
{
	ErrorOut::debugOut("++++++++Auto deregisterXablesCalled++++++++++");
	
	updateableMan->deregisterUpdateable( static_cast<Updateable*>(toDereg) );
	drawableMan->deregisterDrawable( static_cast<Drawable*>(toDereg) );
}

void Scene::setTerrain( std::string terrainKey )
{
	this->terrainMan->setCurrentTerrain( terrainKey );
}

void Scene::drawScene()
{
	drawableMan->draw();
	this->terrainMan->drawCurrentTerrain();
}
void Scene::updateScene()
{
	terminateableMan->processTerminationEvents();

	inputableMan->update();
	updateableMan->update();

	collisionMan->processCollisions();

	alarmMan->update();
}