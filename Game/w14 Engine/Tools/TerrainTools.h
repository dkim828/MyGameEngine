#ifndef TERRAINTOOLS_H
#define TERRAINTOOLS_H


struct TerrainTools
{
	//(0, 0) is top left
	//(n, n) is bottom right
	static int vert_getIndexFromVERTLOC( int x, int z, int numVerts, int numWidth )
	{
		//0,0 index
		int index = numVerts - numWidth;

		index += x;
		index -= ( z * numWidth );

		return index;
	}

	//(0, 0) is bottom left
	//(n, n) is top Right
	static int vert_getIndexFromUVLOC( int u, int v, int numWidth )
	{
		int index = u;

		index += ( v * numWidth );

		return index;
	}


	//(0, 0) is top left
	//(n, n) is bottom right
	//topLeft, topRight, botLeft, botRight are arguments by REFERENCE. Passes references become indicated indices
	//on vert index
	static void vert_getIndicesFromCELL( int i, int j, int numVerts, int numWidth, int& topLeft, int& topRight, 
																				 int& botLeft, int& botRight )
	{
		topLeft = TerrainTools::vert_getIndexFromVERTLOC( i, j, numVerts, numWidth);
		topRight = TerrainTools::vert_getIndexFromVERTLOC( i+1, j, numVerts, numWidth);
		botLeft = TerrainTools::vert_getIndexFromVERTLOC( i, j+1, numVerts, numWidth);
		botRight = TerrainTools::vert_getIndexFromVERTLOC( i+1, j+1, numVerts, numWidth);
	}

	//(0, 0) is top left
	//(n, n) is bottom right
	//xOut and zOut are arguments by REFERENCE. Passed references become indicated indices for cellarray
	static void cell_getCellFromWorldSpace( const Vect& position, float cellWidth, int numCellsWide, int& xOut, int& zOut )
	{
		Vect maxRef( ( numCellsWide*cellWidth )/2.0f, 0.0f, ( numCellsWide*cellWidth )/2.0f );

		Vect temp = maxRef - position;
		
		xOut = (int)( temp[x]  / (float)cellWidth );
		if( xOut < 0 )
			xOut = 0;
		else if( xOut >= numCellsWide )
			xOut = numCellsWide - 1;

		zOut = (int)( temp[z]  / (float)cellWidth );
		if( zOut < 0 )
			zOut = 0;
		else if( zOut >= numCellsWide )
			zOut = numCellsWide - 1;
	}
};


#endif TERRAINTOOLS_H