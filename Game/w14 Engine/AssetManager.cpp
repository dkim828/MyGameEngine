#include "AssetManager.h"

#include "GraphicsObjectManager.h"
AssetManager* AssetManager::assetManagerInst = NULL;

AssetManager::AssetManager()
{
	//Create Primitive Models
	modelStash[ "UnitSphere" ] = GpuModel::Create( "BoundingSphere.azul" );
	modelStash[ "UnitBox" ] = GpuModel::Create( "BoundingBox.azul" );
	modelStash[ "UnitPyramid" ] = GpuModel::Create( "pyramid.azul" );
}

AssetManager::~AssetManager()
{
	unloadAll();
	assetManagerInst = 0;
}

void AssetManager::destroy()
{
	delete assetManagerInst;
}
	//=========================================================================//
	//AssetManager::unloadAll()
	//---->Cleans up all the maps, and deletes all the created Models/Textures
	//---->Used by destructor for cleanup
	//=========================================================================//
void AssetManager::unloadAll()
{
// unload TEXTURE map
	std::map< std::string, Texture* >::iterator it;
	
	if( !textureStash.empty() )
	{
		it = textureStash.begin();

		//going through the map to get the list of textures
		while( it != textureStash.end() )
		{
			delete it->second;
			it++;
		}

		textureStash.clear();
	}

// unload Model map
	std::map< std::string, Model*>::iterator mt;
	
	if( !modelStash.empty() )
	{
		mt = modelStash.begin();

		while( mt != modelStash.end() )
		{
			delete mt->second;
			mt++;
		}

		modelStash.clear();
	}
}




//==========================================================================================//
//PRIVATE		Add Assets Functions		//START//
//==========================================================================================//
void AssetManager::addTexture( std::string key, std::string textureName)
{
	instance().loadTexture( key, textureName );
}
void AssetManager::loadTexture(std::string key, std::string textureName)
{
	auto it = textureStash.find( key );

	if( it == textureStash.end() )
	{
		textureStash[ key ] = GpuTexture::Create( textureName.c_str() );
	}
	else
	{
		printf( "Message from AssetManager::loadTexture() : Key already EXISTs on the texture map\n");
	}
}

void AssetManager::addModel(std::string key, std::string modelName)
{
	instance().loadModel( key, modelName );
}
void AssetManager::loadModel(std::string key, std::string modelName)
{
	std::string modelNameAZUL;

	//Only convert to .azul if model is NOT a .azul
	if( modelName.find( ".azul", 0 ) == std::string::npos )
	{
	// Converting models from FBX format to AZUL format
		char systemConvertCmd[80] = "ConverterDebug ";
		strcat_s( systemConvertCmd, modelName.c_str() );
		strcat_s( systemConvertCmd, " > DebugInfo.txt" );

		printf("Converting FBX to AZUL\n");
		system( systemConvertCmd );
		printf("Converting completed\n");
	// Done Converting to .azul
	

	// setting modelNameAZUL to .azul formatted string
		modelNameAZUL = modelName.substr( 0, modelName.find(".fbx") );
		modelNameAZUL += ".azul";
	}
	else
	{
		modelNameAZUL = modelName;
	}



// Creating Model and then Push onto Map
	auto it= modelStash.find( key );

	if( it == modelStash.end() )
	{
		modelStash[ key ] = GpuModel::Create( modelNameAZUL.c_str() );
	}
	else
	{
		printf( "Message from AssetManager::loadModel() : Key already EXISTs on the model map\n");
	}
}
//==========================================//END//=========================================//



//==========================================================================================//
//PUBLIC		Get Assets Functions		//START//
//==========================================================================================//
Texture* AssetManager::getTexture( std::string key )
{
	if( instance().textureStash.find( key ) == instance().textureStash.end() )
	//Key does not exist
	{
		printf( "Message from AssetManager::getTexture() : Key does NOT EXIST\n");
		system("pause");
		exit(EXIT_FAILURE);
	}
	//Key exists
	else
	{
		return instance().textureStash[ key ];
	}
}
Model* AssetManager::getModel( std::string key )
{
	if( instance().modelStash.find( key ) == instance().modelStash.end() )
	//Key does not exist
	{
		printf( "Message from AssetManager::getModel() : Key does NOT EXIST\n");
		system("pause");
		exit(EXIT_FAILURE);
	}
	//Key exists
	else
	{
		return instance().modelStash[ key ];
	}
}