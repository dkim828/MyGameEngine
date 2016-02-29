#ifndef TERRAINMANAGER_H
#define TERRAINMANAGER_H

#include "Azul.h"

#include <string>

class TerrainObject;
class NoTerrain;
class MadeTerrain;

class TerrainManager
{
public:
	TerrainManager();
	TerrainManager( const TerrainManager& ) {};
	~TerrainManager();

	void setNoTerrain();
	void setCurrentTerrain( std::string terrainKey );
	TerrainObject* getCurrentTerrain();


	void drawCurrentTerrain();

private:
	TerrainObject*		currentTerrain;
	NoTerrain*			noTerrain;
};

#endif