//#include "TerrainModel.h"
#include <Azul.h>
#include <assert.h>
#include <string>
#include <vector>
#include <assert.h>

#include "AssetManager.h"
#include "Tools\TerrainTools.h"


#include "Tools\TestGlobals.h"
Vect TestGlobals::shipCoor;
Vect TestGlobals::maxGroup;
Vect TestGlobals::minGroup;
/*


// Note: the heightmap file should not be a pre-loaded texture from the texture manager
TerrainModel::TerrainModel( char* heightmapFile, float Sidelength, float maxheight, float zeroHeight, char* TextureKey, int RepeatU, int RepeatV)
{
	// Create the model 
	// *** and save it to an .azul file ***
	// *** and loads in the the Model Manager ***
	CreateTerrainModel( heightmapFile, RepeatU, RepeatV);

	// and then load it back in through the model manager... Because it's easier than modding AZUL
	AssetManager::addModel( "AzulTerrain", "AZULTERRAIN.azul" );

	// Scale and adjust position if needed

	WorldMat =	Matrix(SCALE, Sidelength, maxheight, Sidelength ) *
				Matrix( ROT_XYZ, 0,0,0 ) *
				Matrix(TRANS, Vect(0, zeroHeight, 0 ) );

	this->cellWidth = Sidelength / this->numCellsOnSide;

	// Connect the model to a graphics object
	pGObjFT = new GraphicsObjectFlatTexture( AssetManager::getModel("AzulTerrain"), AssetManager::getTexture( TextureKey )	);

	pGObjFT->setWorld( WorldMat );


	for( int z = 0; z < this->numCellsOnSide; ++z )
	{
		for( int x = 0; x < this->numCellsOnSide; ++x )
		{
			this->terrainCells[x][z].max = this->terrainCells[x][z].max * WorldMat;
			this->terrainCells[x][z].min = this->terrainCells[x][z].min * WorldMat;

			this->terrainCells[x][z].topLeft = this->terrainCells[x][z].topLeft * WorldMat;
			this->terrainCells[x][z].topRight = this->terrainCells[x][z].topRight * WorldMat;
			this->terrainCells[x][z].botLeft = this->terrainCells[x][z].botLeft * WorldMat;
			this->terrainCells[x][z].botRight = this->terrainCells[x][z].botRight * WorldMat;
		}
	}
	  
	// This is for debugging only
//	pGObjFT2 = new GraphicsObjectWireFrame( AssetManager::getModel("AzulTerrain") ); TextureKey;
//	pGObjFT2->color.set( Colors::Green );
//	pGObjFT2->setWorld( WorldMat );
}

TerrainModel::~TerrainModel()
{
	for( int i = 0; i < this->numCellsOnSide; ++i )
	{
		delete[] this->terrainCells[i];
	}
	
	delete[] this->terrainCells;
}

void TerrainModel::highlightCellAtPoint( const Vect& pos )
{
	int x, z;
	TerrainTools::cell_getCellFromWorldSpace( pos, this->cellWidth, this->numCellsOnSide, x, z );

	Visualizer::showBox( this->terrainCells[x][z].min, this->terrainCells[x][z].max, Colors::Yellow );
}

void TerrainModel::highlightCellsAtBox( const Vect& min, const Vect& max )
{
	int xMax, xMin;
	int zMax, zMin;
	
	TerrainTools::cell_getCellFromWorldSpace( max, this->cellWidth, this->numCellsOnSide, xMin, zMin );
	TerrainTools::cell_getCellFromWorldSpace( min, this->cellWidth, this->numCellsOnSide, xMax, zMax );

	for( int z = zMin; z < zMax; ++z )
	{
		for( int x = xMin; x < xMax; ++x )
		{	
			Visualizer::showBox( this->terrainCells[x][z].min, this->terrainCells[x][z].max, Colors::Yellow );
		}
	}
}

void TerrainModel::draw()
{
	pGObjFT->Render();
//	pGObjFT2->Render();  // Debug tool only

//	this->highlightCellAtPoint( TerrainModel::shipCoor );
	this->highlightCellsAtBox( TestGlobals::minGroup, TestGlobals::maxGroup );
}

// Creates the actual model mesh
void TerrainModel::CreateTerrainModel( char* heightmapFile, int RepeatU, int RepeatV)
{
	// Using GLTools to read in the file
	int imgWidth, imgHeigth, icomp;
	unsigned int dtype;
	GLbyte* imgData = gltReadTGABits( heightmapFile, &imgWidth, &imgHeigth, &icomp, &dtype);
	assert( imgWidth == imgHeigth); // We need square images for heightmaps


	/// Insert much work to create and the model
	int numPixels = imgWidth*imgWidth;
	int numVerts = numPixels;
	this->numCellsOnSide = imgWidth - 1 ;
	int numTriangles = 2* ( this->numCellsOnSide * this->numCellsOnSide );
	
	VertexStride_VUN *allVerts = new VertexStride_VUN[ numVerts ];
	TriangleIndex *allTriangles = new TriangleIndex[ numTriangles ];

	//Initialize Cell array for AABB
	this->terrainCells = new Cell*[ this->numCellsOnSide ];
	for( int i = 0; i < this->numCellsOnSide; ++i )
	{
		this->terrainCells[i] = new Cell[ this->numCellsOnSide ];
	}


	//Variables to setup Vertex List
	float unitCellWidth = 1.0f / ( imgWidth - 1 );
	float xWorldLoc;
	float zWorldLoc = 0.5f;
		//height stuff
	unsigned char heightData;
	int pixelByteIndex = 0;

	//Variables to setup UV
	float UVcellWidthU = (float)RepeatU / ( imgWidth - 1 );
	float UVcellWidthV = (float)RepeatV / ( imgWidth - 1 );
	float uLoc = 0.0f;
	float vLoc = 0.0f;

	int curVert;
	for( int z = 0; z < imgWidth; ++z )
	{
		xWorldLoc = 0.5f;
		uLoc = 0.0f;

		for( int x = 0; x < imgWidth; ++x )
		{
			//Set VertexList index using (x,z) coordinates of vertex space
			curVert = TerrainTools::vert_getIndexFromVERTLOC( x, z, numVerts, imgWidth );

			allVerts[ curVert ].x = xWorldLoc;
			allVerts[ curVert ].z = zWorldLoc;	

			//Separately do height find
			heightData = static_cast<unsigned char>( imgData[ pixelByteIndex ] );
				//Unit sized Vertex Locations
			allVerts[ pixelByteIndex/3 ].y = heightData / 255.0f;
			pixelByteIndex += 3;

			//Set all other members to 0s
			allVerts[ curVert ].txt = 0.0f;
			allVerts[ curVert ].nx = 0.0f;
			allVerts[ curVert ].ny = 0.0f;
			allVerts[ curVert ].nz = 0.0f;
			
			//update next X location value
			xWorldLoc -= unitCellWidth;


			//Set VertexList index using(x,z) coordinates of UV space
			curVert = TerrainTools::vert_getIndexFromUVLOC( x, z, imgWidth );

			allVerts[ curVert ].u = uLoc;
			allVerts[ curVert ].v = vLoc;

			//update next UV- U value
			uLoc += UVcellWidthU;
		}

		//update Z value for next column
		zWorldLoc -= unitCellWidth;
		
		//update V value for next column
		vLoc += UVcellWidthV;
	}

	//Triangle stuff
	int tris = 0;
	int topLeft;
	int topRight;
	int botLeft;
	int botRight;

	//Min/Max stuff
	float maxAltitude;
	float minAltitude;
	
	for( int z = 0; z < this->numCellsOnSide ; ++z )
	{
		for( int x = 0; x < this->numCellsOnSide ; ++x )
		{
			TerrainTools::vert_getIndicesFromCELL( x, z, numVerts, imgWidth, topLeft, topRight, botLeft, botRight );

			allTriangles[tris].v0 = topLeft;
			allTriangles[tris].v1 = botLeft;
			allTriangles[tris].v2 = topRight;

			tris++;

			allTriangles[tris].v0 = topRight;
			allTriangles[tris].v1 = botLeft;
			allTriangles[tris].v2 = botRight;

			tris++;

			//Probably inefficient, but just goin with it for now
			//TopLeft and BotRight are the opposites
			maxAltitude = allVerts[topLeft].y;
			maxAltitude = MathTools::getMax( maxAltitude, allVerts[topRight].y );
			maxAltitude = MathTools::getMax( maxAltitude, allVerts[botLeft].y );
			maxAltitude = MathTools::getMax( maxAltitude, allVerts[botRight].y );

			minAltitude = allVerts[topLeft].y;
			minAltitude = MathTools::getMin( minAltitude, allVerts[topRight].y );
			minAltitude = MathTools::getMin( minAltitude, allVerts[botLeft].y );
			minAltitude = MathTools::getMin( minAltitude, allVerts[botRight].y );

			//Keeping same XZ orientation per all Cells
			this->terrainCells[x][z].max.set( allVerts[topLeft].x, maxAltitude, allVerts[topLeft].z );
			this->terrainCells[x][z].min.set( allVerts[botRight].x, minAltitude, allVerts[botRight].z );

			//Set current cell's vertex values
			this->terrainCells[x][z].topLeft.set( allVerts[topLeft].x, allVerts[topLeft].y, allVerts[topLeft].z );
			this->terrainCells[x][z].topRight.set( allVerts[topRight].x, allVerts[topRight].y, allVerts[topRight].z );
			this->terrainCells[x][z].botLeft.set( allVerts[botLeft].x, allVerts[botLeft].y, allVerts[botLeft].z );
			this->terrainCells[x][z].botRight.set( allVerts[botRight].x, allVerts[botRight].y, allVerts[botRight].z );
		}
	}


	this->SaveTerrainModel( allVerts, numVerts, allTriangles, numTriangles);

	delete allVerts;
	delete allTriangles;
}

// Saves the model to file in the Azul format 
// (realistically, the filename should be parametrized)
void TerrainModel::SaveTerrainModel( VertexStride_VUN* pVerts, int num_verts, TriangleIndex* tlist, int num_tri)
{
	char* TerrainName = "AZULTERRAIN";
	char* TerrainFilename = "../Assets/AZULTERRAIN.azul";

	//// Write the data to a file ----------------------------
	FileHandle fh;
	FileError  ferror;
	std::vector<std::string> FBX_textNames; // (Ed) purposefully empty to be consistent 

	// 1) Create a blank header

		// // write the data
		AzulFileHdr  azulFileHdr;
		strcpy_s(azulFileHdr.objName, OBJECT_NAME_SIZE, TerrainName);

	// 2)  Write the data (Header, Buffers) to the files

	// write the header (Take 1) 

		// create the file, write the header
		ferror = File::open(fh, TerrainFilename, FILE_READ_WRITE );
		assert( ferror == FILE_SUCCESS );

		// write the data
		ferror = File::write( fh, &azulFileHdr, sizeof(azulFileHdr) );
		assert( ferror == FILE_SUCCESS );

	// update the header: numTextures, textureNamesOffset
		azulFileHdr.numTextures = FBX_textNames.size();

		// update the offset
		ferror = File::tell( fh, azulFileHdr.textureNamesOffset );
		assert( ferror == FILE_SUCCESS );

	
	std::vector<std::string>::iterator FBX_textNames_iterator;

	int i=0;
	for( FBX_textNames_iterator = FBX_textNames.begin(); 
		    FBX_textNames_iterator != FBX_textNames.end();
		    FBX_textNames_iterator++ )
	{
		const char *ss = (*FBX_textNames_iterator).c_str();
		// write the vertex data
		ferror = File::write( fh, ss, strlen(ss) + 1);
		assert( ferror == FILE_SUCCESS );
		i++;
	}

	// update the header: numVerts, VertBufferOffset

		// update the number of verts
		azulFileHdr.numVerts = num_verts;
   
		// update the offset
		ferror = File::tell( fh, azulFileHdr.vertBufferOffset );
		assert( ferror == FILE_SUCCESS );

	// write the vertex data
	ferror = File::write( fh, pVerts, num_verts * sizeof(VertexStride_VUN) );
	assert( ferror == FILE_SUCCESS );

	// update the header: numTriList, triListBufferOffset

		// update the number of verts
		azulFileHdr.numTriangles = num_tri;

		// update the offset
		ferror = File::tell( fh, azulFileHdr.triangleListBufferOffset );
		assert( ferror == FILE_SUCCESS );

	// write the triListBuffer data
	ferror = File::write( fh, tlist, num_tri * sizeof(TriangleIndex) );
	assert( ferror == FILE_SUCCESS );
	    
	// write the header (Take 2) now with updated data

		azulFileHdr.textureNamesInBytes = azulFileHdr.vertBufferOffset - azulFileHdr.textureNamesOffset;

		// reset to the beginning of file
		ferror = File::seek( fh, FILE_SEEK_BEGIN, 0 );
		assert( ferror == FILE_SUCCESS );

		// write the buffer
		ferror = File::write( fh, &azulFileHdr, sizeof(azulFileHdr) );
		assert( ferror == FILE_SUCCESS );

	// All done - bye bye
	ferror = File::close( fh );
	assert( ferror == FILE_SUCCESS );
}

*/