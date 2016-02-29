#ifndef MADETERRAIN_H
#define MADETERRAIN_H

#include "Azul.h"
#include "TerrainObject.h"


class MadeTerrain : public TerrainObject
{
public:
	MadeTerrain( GraphicsObject* pGobj, int numCellRows, float sideLength, float maxHeight, float zeroHeight );
	virtual ~MadeTerrain();

	virtual void drawTerrain() override;

	virtual void getTerrainSegmentIterator( const Vect& min, const Vect& max, CellIterator& begin, CellIterator& end );

private:
	GraphicsObject* pGObjFT;
	Matrix WorldMat;

	Cell** terrainCells;
	Vect* vertList;
	
	int total_CellRows;
	int total_VertRows;
	float cellWidth;

	//default Constructor for terrain object not allowed
	MadeTerrain();
};


#endif