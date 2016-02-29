#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "Azul.h"

#include <string>
#include <vector>
#include <map>

class AssetManager
{
friend class Game;
friend class GraphicsObjectManager;

public:
	/**
	\brief A function to retrieve a texture based on a loaded model
	\ingroup ASSETS

	This function returns a pointer to a Texture object that was created when AssetManager::addModel() is used within
	AssetManager::loadAssets().

	The texture map is a map of string keys(which are user defined in loadAssets()) to a std::vector of
	texture objects. The reason for this is that some models use multiple textures as defaults in order to
	cover all parts of the mesh. Since a lot of models tend to only have one default texture, function can be
	called without the textureNum argument and it defaults to retrieving that one texture. 

	\b Example: There is no where in the demo a texture needs to be accessed, but this is how one
	would access a default texture
	\code
	void MyClass::someFunction()
	{
		Texture* myNeededTexture = AssetManager::getTexture( "modelKey", 1 );
		Texture* myNeededTextureTwo = AssetManager::getTexture( "modelKeyTwo" );
	}
	\endcode

	\param	key	string key that correlates to wanted texture based on model loaded
	\param	textureNum	defaulted to 0, this is a necessary parameter in case the loaded model has multiple default textures
	*/
	static Texture* getTexture( std::string key );

	/**
	\brief A function to retrieve a model based on a loaded model
	\ingroup ASSETS

	This function returns a pointer to a Model object that was created when AssetManager::addModel() is used within
	AssetManager::loadAssets().

	The AssetManager has a map of Models that use the same key that the user defined when adding the models.

	\b Important: This returns raw Model pointers, NOT GraphicsObjects. Models cannot be rendered onto the screen.

	\b Example: There is no where in the demo where a model is needed. However, within Collideable's registration process, the
	Collideable needs access to some base model of the GraphicsObject to scale from. \b NOTE: this is NOT a user accessible
	function. It is solely shown to show how this function is used.
	\code
	void Collideable::setCollidingModel( std::string mKey )
	{
		collidingModel = AssetManager::getModel( mKey ); //function call HERE

		if( mKey == "UnitSphere" ||
			mKey == "UnitPyramid" ||
			mKey == "UnitBox" )
			collidingRadius = 1;
		else
			collidingRadius = collidingModel->radius;
	
		collidingCenter = collidingModel->center;
	
		boundingSphere = AssetManager::getUnitSphere_wire();
		boundingSphereBase = Matrix(SCALE, collidingRadius, collidingRadius, collidingRadius)
							 * Matrix( TRANS, collidingCenter );
	}
	\endcode

	\param	key	string key that correlates to wanted texture based on model loaded
	*/
	static Model* getModel( std::string key );	
	
	//Private Functions
	static void addTexture( std::string key, std::string textureName );
	void loadTexture( std::string key, std::string textureName );

	static void addModel( std::string key, std::string modelName );
	void loadModel( std::string key, std::string modelName );
private:
	//Asset Maps
	//Texture and Model Stash use same key
	std::map< std::string, Texture* > textureStash;
	std::map< std::string, Model*> modelStash;


	

	//=========================================================================//
	//AssetManager::unloadAll()
	//---->Cleans up all the maps, and deletes all the created Models/Textures
	//---->Used by destructor for cleanup
	//=========================================================================//
	void unloadAll();


	//Singleton Instance
	static AssetManager* assetManagerInst;

	//PRIVATE Constructor/Destructor
	AssetManager();
	AssetManager( const AssetManager& ) {};
	~AssetManager();

	//Singular Instance Access
	static AssetManager& instance()
	{
		if( !assetManagerInst )
			assetManagerInst = new AssetManager();

		return *assetManagerInst;
	};

	static void destroy();
	
	/**
	\brief A function in a separate LoadAssets.cpp that the user must use to load assets
	\ingroup ASSETS

	loadAssets() is a function the user must define in a user defined file called LoadAssets.cpp

	The purpose is to have a central place to load all assets needed to run a game. So far, the
	ability to load models with default textures is the only thing implemented.

	\b Example: Within the demo there is a Ship, Pyramid, Cottage, and GroundPlane GameEntities. 
	The Ship uses a "space_frigate.fbx" model to load onto the AssetManager with the key "shipModel" 
	in this function which is located in LoadAssets.cpp
	\code
	void AssetManager::loadAssets()
	{
		addModel("shipModel", "space_frigate.fbx");
		addModel("cottage", "Cottage.fbx");
		addModel("groundPlane" , "Plane.fbx");
	}
	\endcode
	*/
	static void loadAssets();
};


#endif ASSETMANAGER_H