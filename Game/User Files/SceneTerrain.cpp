#include "SceneTerrain.h"

#include "../w14 Engine/TerrainObject.h"
#include "GroundPlane.h"
#include "Ship.h"
#include "Bullet.h"

void SceneTerrain::initScene()
{
	//setTerrain( "smallTerrain" );
	setTerrain( "mainTerrain" );

	new Ship(256, 25, 256, 0,0,0,0);
	new Ship(220, 25, 220, 0,0,0,0);

	setCollisionSelf< Ship >();
	setCollisionWithTerrain< Ship >();
	setCollisionWithTerrain< Bullet >();
}

void SceneTerrain::endScene()
{
}
