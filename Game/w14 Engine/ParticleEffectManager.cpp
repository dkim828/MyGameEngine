#include "ParticleEffectManager.h"

#include <vector>
#include <string>
#include <assert.h>
#include "AssetManager.h"
#include "GraphicsObjectManager.h"
#include "Tools\Visualizer.h"

#include "TimeManager.h"

#include "ParticleEffect.h"


ParticleEffectManager* ParticleEffectManager::inst = 0;

ParticleEffectManager::ParticleEffectManager()
{
}
void ParticleEffectManager::init()
{
	instance().makeParticleModel();
	instance().particleGObj = GraphicsObjectManager::makeGObj_NoTexture( AssetManager::getModel("particle"), Colors::Black );
}
ParticleEffectManager::~ParticleEffectManager()
{
	std::map< std::string, ParticleEffect* >::iterator it;
	if( !allEffects.empty() )
	{
		it = allEffects.begin();

		while( it != allEffects.end() )
		{
			delete it->second;
			it++;
		}

		allEffects.clear();
	}
}
void ParticleEffectManager::destroy()
{
	delete inst;
}

void ParticleEffectManager::SpawnEffect( std::string effectKey, const Vect& pos, const Vect& rot  )
{
	if( instance().allEffects.find( effectKey ) == instance().allEffects.end() )
	//Key does not exist
	{
		printf( "Emitterhandle get failed \n");
		system("pause");
		assert(0);
	}
	//Key exists
	else
	{
		instance().allEffects[effectKey]->spawnEmitter( pos, rot );
	}
}



void ParticleEffectManager::LoadEffect( std::string effectKey, ParticleEffect* inEffect  )
{
	auto it = instance().allEffects.find( effectKey );

	if( it == instance().allEffects.end() )
	{
		if( inEffect->gObj == 0 )
			inEffect->setGraphicsObject( instance().particleGObj );

		instance().allEffects[ effectKey ] = inEffect;
	}
	else
	{
		printf( "Effect Key already EXISTs on the Effects map\n");
	}
}


//==============================================Particle Model STUFF==============================================//



void ParticleEffectManager::makeParticleModel()
{
	const int num_verts = 4;
	VertexStride_VUN pVerts[ num_verts ];
	const int num_tri = 2;
	TriangleIndex tlist[ num_tri ];

	pVerts[0].x = 0.5f;
	pVerts[0].y = 0.5f;
	pVerts[0].z = 0.0f;
	pVerts[0].nx = 0.0f;
	pVerts[0].ny = 0.0f;
	pVerts[0].nz = 0.0f;
	
	pVerts[1].x = -0.5f;
	pVerts[1].y = 0.5f;
	pVerts[1].z = 0.0f;
	pVerts[1].nx = 0.0f;
	pVerts[1].ny = 0.0f;
	pVerts[1].nz = 0.0f;
	
	pVerts[2].x = 0.5f;
	pVerts[2].y = -0.5f;
	pVerts[2].z = 0.0f;
	pVerts[2].nx = 0.0f;
	pVerts[2].ny = 0.0f;
	pVerts[2].nz = 0.0f;
	
	pVerts[3].x = -0.5f;
	pVerts[3].y = -0.5f;
	pVerts[3].z =  0.0f;
	pVerts[3].nx = 0.0f;
	pVerts[3].ny = 0.0f;
	pVerts[3].nz = 0.0f;
	
	tlist[0].v0 = 1;
	tlist[0].v1 = 0;
	tlist[0].v2 = 3;

	tlist[1].v0 = 3;
	tlist[1].v1 = 0;
	tlist[1].v2 = 2;



	std::string modelKey = "particle";
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

	int k = 0;k;
	
	AssetManager::addModel( modelKey, modelKey+".azul" );
}
