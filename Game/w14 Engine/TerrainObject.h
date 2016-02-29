#ifndef TERRAINOBJECT_H
#define TERRAINOBJECT_H

#include "Azul.h"

#include "Cell.h"
#include <assert.h>

class TerrainObject
{
public:
	class CellIterator
	{
	public:
		CellIterator()
		{
			this->curPtr = 0;
		}
		//for BEGIN
		CellIterator( Cell** inArray, int colMin, int rowMin,
									  int colMax, int rowMax )
		{
			this->cells = inArray;

			this->colStart = colMin;
			this->colRange = colMax - colMin;
			this->colCounter = 0;

			this->col = colMin;
			this->row = rowMin;

			//Means cell is not within bounds
			if( this->colRange < 0 ||
				(rowMax - rowMin) < 0 )
			{
				this->curPtr = &this->cells[ colMax ][ rowMax ];
			}
			else
				this->curPtr = &this->cells[ this->col ][ this->row ];
		}
		//for END
		CellIterator( Cell** inArray, int colMin, int colMax, int rowMax)
		{
			this->cells = inArray;
			colMax;//notused
			this->curPtr = &this->cells[ colMin ][ rowMax+1 ];
		}
		~CellIterator(){};
		
		CellIterator( const CellIterator&  ){};

		bool operator==( const CellIterator& other ){ return this->curPtr==other.curPtr; };
		bool operator!=( const CellIterator& other ){ return this->curPtr!=other.curPtr; };

		CellIterator& operator++()
		{
			if( this->colCounter < this->colRange )
			{
				this->col++;
				this->curPtr = &this->cells[this->col][this->row];
				this->colCounter++;
			}
			else
			{
				this->row++;
				this->col = this->colStart;
				this->curPtr = &this->cells[this->col][this->row];
				this->colCounter = 0;
			}

			return *this;
		}
		CellIterator& operator++( int unused )
		{
			unused;
			//for the sake of easiness, forcing this not to be used
			assert( false );
		}

		Cell* operator*() { return this->curPtr; }
		
	private:
		Cell** cells;

		Cell* curPtr;

		int colRange;
		int colStart;
		int colCounter;

		int row;
		int col;
	};


	TerrainObject(){};
	virtual ~TerrainObject(){};

	virtual void drawTerrain() = 0;

	//CellIterator For collision
	//First Vect is the Minimum position
	//2nd Vect is the max position
	// CellIterators ARE REFERENCESESE
	virtual void getTerrainSegmentIterator( const Vect& , const Vect&, CellIterator&, CellIterator&   ) = 0 ;

private:
};


#endif