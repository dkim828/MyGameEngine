#include "TerrainObjectManager.h"
#include <vector>

#include "AssetManager.h"
#include "GraphicsObjectManager.h"
#include "MadeTerrain.h"

#include "Tools\MathTools.h"
#include "Tools\TerrainTools.h"

TerrainObjectManager* TerrainObjectManager::inst = 0;


TerrainObjectManager::TerrainObjectManager()
{
}
TerrainObjectManager::~TerrainObjectManager()
{
	unloadAll();
	TerrainObjectManager::inst = 0;
}
void TerrainObjectManager::destroy()
{
	delete TerrainObjectManager::inst;
}
void TerrainObjectManager::unloadAll()
{
	this->numCellRowsOnModelMap.clear();

	if( !this->terrainObjectMap.empty() )
	{
		auto it = this->terrainObjectMap.begin();

		while( it != this->terrainObjectMap.end() )
		{
			delete it->second;
			it++;
		}

		this->terrainObjectMap.clear();
	}
}



MadeTerrain* TerrainObjectManager::getTerrainObject( std::string key )
{
	assert( instance().terrainObjectMap.find( key ) != instance().terrainObjectMap.end() );
	
	return instance().terrainObjectMap[ key ];
}

void TerrainObjectManager::loadTerrainModel( std::string modelKey, char* heightmapFile, int RepeatU, int RepeatV )
{
	//Only add a new terrain model if the modelKey has not been used yet for a terrain, else crash
	auto it = instance().numCellRowsOnModelMap.find( modelKey );
	assert( it == instance().numCellRowsOnModelMap.end() );
	
	instance().CreateTerrainModel( modelKey, heightmapFile, RepeatU, RepeatV );
	AssetManager::addModel( modelKey, modelKey+".azul" );
}

void TerrainObjectManager::loadTerrainObject(  std::string TerrainKey, std::string ModelKey, std::string TextureKey, float sideLength, float maxHeight, float zeroHeight )
{
	instance().priv_loadTerrainObject( TerrainKey, ModelKey, TextureKey, sideLength, maxHeight, zeroHeight );
}

void TerrainObjectManager::priv_loadTerrainObject(  std::string TerrainKey, std::string ModelKey, std::string TextureKey, float sideLength, float maxHeight, float zeroHeight )
{
	//Only add a new TerrainObject With TerrainKey if it does not exist, else crash
	auto it = this->terrainObjectMap.find( TerrainKey );
	assert( it == this->terrainObjectMap.end() );
	
	this->terrainObjectMap[ TerrainKey ] = new MadeTerrain( GraphicsObjectManager::makeGObj( AssetManager::getModel( ModelKey), AssetManager::getTexture( TextureKey ) ),
														  this->numCellRowsOnModelMap[ModelKey], sideLength, maxHeight, zeroHeight );
}

void TerrainObjectManager::CreateTerrainModel( std::string modelKey, char* heightmapFile, int RepeatU, int RepeatV)
{
	// Using GLTools to read in the file
	int imgWidth, imgHeigth, icomp;
	unsigned int dtype;
	GLbyte* imgData = gltReadTGABits( heightmapFile, &imgWidth, &imgHeigth, &icomp, &dtype);
	assert( imgWidth == imgHeigth); // We need square images for heightmaps


	/// Insert much work to create and the model
	int numPixels = imgWidth*imgWidth;
	int numVerts = numPixels;
	this->numCellRowsOnModelMap[modelKey] = imgWidth - 1 ;
	int numTriangles = 2* ( this->numCellRowsOnModelMap[modelKey] * this->numCellRowsOnModelMap[modelKey] );
	
	VertexStride_VUN *allVerts = new VertexStride_VUN[ numVerts ];
	TriangleIndex *allTriangles = new TriangleIndex[ numTriangles ];


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
	
	for( int z = 0; z < this->numCellRowsOnModelMap[modelKey] ; ++z )
	{
		for( int x = 0; x < this->numCellRowsOnModelMap[modelKey] ; ++x )
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
		}
	}


	this->SaveTerrainModel( modelKey, allVerts, numVerts, allTriangles, numTriangles);

	delete allVerts;
	delete allTriangles;
}

void TerrainObjectManager::SaveTerrainModel( std::string modelKey, VertexStride_VUN* pVerts, int num_verts, TriangleIndex* tlist, int num_tri)
{
	std::string TerrainFilename = "../Assets/";
	TerrainFilename += modelKey;
	TerrainFilename += ".azul";

	//// Write the data to a file ----------------------------
	FileHandle fh;
	FileError  ferror;
	std::vector<std::string> FBX_textNames; // (Ed) purposefully empty to be consistent 

	// 1) Create a blank header

		// // write the data
		AzulFileHdr  azulFileHdr;
		strcpy_s(azulFileHdr.objName, OBJECT_NAME_SIZE, modelKey.c_str());

	// 2)  Write the data (Header, Buffers) to the files

	// write the header (Take 1) 

		// create the file, write the header
		ferror = File::open(fh, TerrainFilename.c_str(), FILE_READ_WRITE );
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