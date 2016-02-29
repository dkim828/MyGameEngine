#ifndef GRAPHICSOBJECTMANAGER_H
#define GRAPHICSOBJECTMANAGER_H

#include "Azul.h"

#include <list>
#include <string>


class GraphicsObjectManager
{
friend class Game;
friend class GameEntity;
friend class CollisionVolume;

public:
	static GraphicsObjectFlatTexture* makeGObj( Model* model, Texture* t1, Texture* t2 = 0 , Texture* t3 = 0 , Texture* t4 = 0 );
	static GraphicsObjectFlatTexture* makeGObj_DefaultTextures( Model* model );

	static GraphicsObjectWireFrame* makeGObj_WireFrame( Model* model );
	static GraphicsObjectColorNoTexture* makeGObj_NoTexture( Model* model, const Vect& color );

private:
	static const int MAXTEXTURECOUNT =4;
	std::list< GraphicsObject* > graphicsObjectBin;

	//private calls for static functions
	GraphicsObjectFlatTexture* priv_makeGObj( Model* model, Texture* t1, Texture* t2 , Texture* t3 , Texture* t4 );
	GraphicsObjectFlatTexture* priv_makeGObj_DefaultTextures( Model* model );

	GraphicsObjectWireFrame* priv_makeGObj_WireFrame( Model* model );
	GraphicsObjectColorNoTexture* priv_makeGObj_NoTexture( Model* model, const Vect& color );

	//Return
	static void removeGraphicsObject( GraphicsObject* gObj );
	void priv_removeGraphicsObject( GraphicsObject* gObj );

	//=========================================================================//
	//GraphicsObjectManager::unloadAll()
	//---->Cleans up all the maps, and deletes all the created Graphics Objects
	//---->Used by destructor for cleanup
	//=========================================================================//
	void unloadAll();

	
	//Singleton Instance
	static GraphicsObjectManager* gObjManInst;

	//PRIVATE Constructor/Destructor
	GraphicsObjectManager();
	GraphicsObjectManager( const GraphicsObjectManager& ) {};
	~GraphicsObjectManager();

	//Singular Instance Access
	static GraphicsObjectManager& instance()
	{
		if( !gObjManInst )
			gObjManInst = new GraphicsObjectManager();

		return *gObjManInst;
	};

	static void destroy();
};

#endif GRAPHICSOBJECTMANAGER_H