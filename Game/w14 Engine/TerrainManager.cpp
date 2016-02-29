#include "TerrainManager.h"

#include "TerrainObject.h"
#include "DefaultNoTerrain.h"
#include "MadeTerrain.h"

#include "TerrainObjectManager.h"

TerrainManager::TerrainManager()
{
	this->noTerrain = new NoTerrain();
	this->currentTerrain = this->noTerrain;
}

TerrainManager::~TerrainManager()
{
	delete this->noTerrain;
}

//No need for deletions of current terrain b/c terrains are owned by TerrainObjectManager
void TerrainManager::setCurrentTerrain( std::string terrainKey )
{
	this->currentTerrain = TerrainObjectManager::getTerrainObject( terrainKey );
}

void TerrainManager::setNoTerrain( )
{
	this->currentTerrain = this->noTerrain;
}


TerrainObject* TerrainManager::getCurrentTerrain()
{
	return this->currentTerrain;
}

void TerrainManager::drawCurrentTerrain()
{
	this->currentTerrain->drawTerrain();
}