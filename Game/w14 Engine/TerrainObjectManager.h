#ifndef TERRAINOBJECTMANAGER_H
#define TERRAINOBJECTMANAGER_H

#include "Azul.h"

#include <string>
#include <map>
#include <assert.h>

class MadeTerrain;

class TerrainObjectManager
{
friend class Game;

public:
	static void loadTerrainModel( std::string modelKey, char* heightmapFile, int RepeatU, int RepeatV );
	static void loadTerrainObject(  std::string TerrainKey, std::string ModelKey, std::string TextureKey, float sideLength, float maxHeight, float zeroHeight );

	static MadeTerrain* getTerrainObject( std::string key );

private:
	std::map< std::string, MadeTerrain* > terrainObjectMap;
	std::map< std::string, int > numCellRowsOnModelMap;

	void priv_loadTerrainObject( std::string TerrainKey, std::string ModelKey, std::string TextureKey, float sideLength, float maxHeight, float zeroHeight );

	void CreateTerrainModel( std::string modelKey, char* heightmapFile, int RepeatU, int RepeatV);
	void SaveTerrainModel( std::string modelKey, VertexStride_VUN* pVerts, int num_verts, TriangleIndex* tlist, int num_tri);

	//Singleton Instance
	static TerrainObjectManager* inst;

	//PRIVATE Constructor/Destructor
	TerrainObjectManager();
	TerrainObjectManager( const TerrainObjectManager& ) {};
	~TerrainObjectManager();

	//Singular Instance Access
	static TerrainObjectManager& instance()
	{
		if( !inst )
			inst = new TerrainObjectManager();

		return *inst;
	};

	static void destroy();
	void unloadAll();
};

#endif