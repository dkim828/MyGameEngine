#include "MadeTerrain.h"
#include "Cell.h"

#include "Tools\TerrainTools.h"
#include "Tools\MathTools.h"

MadeTerrain::MadeTerrain( GraphicsObject* pGobj, int numCellRows, float sideLength, float maxHeight, float zeroHeight )
{
	this->pGObjFT = pGobj;
	this->WorldMat = Matrix(SCALE, sideLength, maxHeight, sideLength ) *
					Matrix( ROT_XYZ, 0,0,0 ) *
					Matrix(TRANS, Vect(0, zeroHeight, 0 ) );
	this->pGObjFT->setWorld( this->WorldMat );


	this->total_CellRows = numCellRows;
	this->cellWidth = sideLength / this->total_CellRows;

	this->total_VertRows = numCellRows + 1;

	
	//Initialize Terrain Cell Arrays
	this->terrainCells = new Cell*[ this->total_CellRows ];
	for( int i = 0; i < this->total_CellRows; ++i )
	{
		this->terrainCells[i] = new Cell[ this->total_CellRows ];
	}

	//Set Cell Values + transform
	this->vertList = this->pGObjFT->getModel()->getVectList();
	float maxAltitude;
	float minAltitude;

	for( int z = 0; z < this->total_CellRows ; ++z )
	{
		for( int x = 0; x < this->total_CellRows ; ++x )
		{
			TerrainTools::vert_getIndicesFromCELL( x, z, this->pGObjFT->getModel()->numVerts, this->total_VertRows, 
												  this->terrainCells[x][z].getTopLeft(), this->terrainCells[x][z].getTopRight(), 
												  this->terrainCells[x][z].getBotLeft(), this->terrainCells[x][z].getBotRight() );

			//Ugly, but just goin with it for now
			//TopLeft and BotRight are the opposites
			maxAltitude = this->vertList[this->terrainCells[x][z].getTopLeft()][y];
			maxAltitude = MathTools::getMax( maxAltitude, vertList[this->terrainCells[x][z].getTopRight()][y] );
			maxAltitude = MathTools::getMax( maxAltitude, vertList[this->terrainCells[x][z].getBotLeft()][y] );
			maxAltitude = MathTools::getMax( maxAltitude, vertList[this->terrainCells[x][z].getBotRight()][y] );

			minAltitude = this->vertList[this->terrainCells[x][z].getTopLeft()][y];
			minAltitude = MathTools::getMin( minAltitude, vertList[this->terrainCells[x][z].getTopRight()][y] );
			minAltitude = MathTools::getMin( minAltitude, vertList[this->terrainCells[x][z].getBotLeft()][y] );
			minAltitude = MathTools::getMin( minAltitude, vertList[this->terrainCells[x][z].getBotRight()][y] );

			//Keeping same XZ orientation per all Cells
			this->terrainCells[x][z].getMax().set( this->vertList[this->terrainCells[x][z].getTopLeft()] );
			this->terrainCells[x][z].getMax()[y] = maxAltitude;

			this->terrainCells[x][z].getMin().set( this->vertList[this->terrainCells[x][z].getBotRight()] );
			this->terrainCells[x][z].getMin()[y] = minAltitude;

			//Then apply worldTransform to the Vectors
			this->terrainCells[x][z].getMax() = this->terrainCells[x][z].getMax() * this->WorldMat;
			this->terrainCells[x][z].getMin() = this->terrainCells[x][z].getMin() * this->WorldMat;
		}
	}
}

MadeTerrain::~MadeTerrain()
{
	for( int i = 0; i < this->total_CellRows; ++i )
	{
		delete[] this->terrainCells[i];
	}
	delete[] this->terrainCells;
}


void MadeTerrain::drawTerrain()
{
 	this->pGObjFT->Render();
}


void MadeTerrain::getTerrainSegmentIterator( const Vect& min, const Vect& max, CellIterator& begin, CellIterator& end )
{
	int colMin, colMax;
	int rowMin, rowMax;

	TerrainTools::cell_getCellFromWorldSpace( max, this->cellWidth, this->total_CellRows, colMax, rowMax );
	TerrainTools::cell_getCellFromWorldSpace( min, this->cellWidth, this->total_CellRows, colMin, rowMin );

	begin = CellIterator( this->terrainCells, colMin, rowMin, colMax, rowMax );
	end = CellIterator( this->terrainCells,  colMin, colMax, rowMax );
}