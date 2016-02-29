#ifndef DEFAULTNOTERRAIN_H
#define DEFAULTNOTERRAIN_H

#include "TerrainObject.h"

class NoTerrain: public TerrainObject
{
public:
	NoTerrain(){};
	virtual ~NoTerrain(){};

	void drawTerrain() override
	{
		//Nothing Drawn
	}

	virtual void getTerrainSegmentIterator( const Vect& , const Vect&, CellIterator& begin, CellIterator& end  ) override 
	{
		//using default Constructor for both begin and end
		//makes it so both are pointing to 0
		begin = CellIterator();
		end = CellIterator();
	}

private:
};


#endif