#include "GraphicsObjectManager.h"

#include "AssetManager.h"
#include "Tools\Visualizer.h"

GraphicsObjectManager* GraphicsObjectManager::gObjManInst = 0;

GraphicsObjectManager::GraphicsObjectManager()
{
}

GraphicsObjectManager::~GraphicsObjectManager()
{
	unloadAll();
	gObjManInst = 0;
}
void GraphicsObjectManager::destroy()
{
	if( gObjManInst != 0 )
		delete gObjManInst;
}

	//=========================================================================//
	//GraphicsObjectManager::unloadAll()
	//---->Cleans up all the maps, and deletes all the created Graphics Objects
	//=========================================================================//
void GraphicsObjectManager::unloadAll()
{
// unload all Graphics Objects culminated during runtime
	std::list< GraphicsObject* >::iterator it;
	
	if( !graphicsObjectBin.empty() )
	{
		it = graphicsObjectBin.begin();

		while( it != graphicsObjectBin.end() )
		{
			delete (*it);
			it++;
		}

		graphicsObjectBin.clear();
	}
}

void GraphicsObjectManager::removeGraphicsObject( GraphicsObject* gObj )
{
	instance().priv_removeGraphicsObject( gObj );
}
void GraphicsObjectManager::priv_removeGraphicsObject( GraphicsObject* gObj )
{
	for( auto it = graphicsObjectBin.begin();
		it != graphicsObjectBin.end(); it ++ )
	{
		if( (*it) == gObj )
		{
			delete (*it);
			graphicsObjectBin.erase( it );
			break;
		}
	}
}
	
GraphicsObjectFlatTexture* GraphicsObjectManager::makeGObj( Model* model, Texture* t1, Texture* t2 , Texture* t3 , Texture* t4 )
{
	return instance().priv_makeGObj( model, t1, t2, t3, t4 );
}

GraphicsObjectFlatTexture* GraphicsObjectManager::makeGObj_DefaultTextures( Model* model )
{
	return instance().priv_makeGObj_DefaultTextures( model );
}

GraphicsObjectWireFrame* GraphicsObjectManager::makeGObj_WireFrame( Model* model )
{
	return instance().priv_makeGObj_WireFrame( model );
}

GraphicsObjectColorNoTexture* GraphicsObjectManager::makeGObj_NoTexture( Model* model, const Vect& color = Colors::Black )
{
	return instance().priv_makeGObj_NoTexture( model, color );
}


GraphicsObjectFlatTexture* GraphicsObjectManager::priv_makeGObj( Model* model, Texture* t1, Texture* t2 , Texture* t3 , Texture* t4 )
{
	GraphicsObjectFlatTexture* temp = new GraphicsObjectFlatTexture( model, t1, t2, t3, t4 );
	graphicsObjectBin.push_back(temp);

	return temp;
}
GraphicsObjectFlatTexture* GraphicsObjectManager::priv_makeGObj_DefaultTextures( Model* model )
{	
	Texture* texArray[MAXTEXTURECOUNT];
	for(int i =0; i<MAXTEXTURECOUNT;++i)
	{
		texArray[i] = 0;
	}

	//load all Textures associated with model
	int numText = model->numTextures;
	for( int i = 0; i < numText; i++ )
	{
		//load texture into AssetManager
		AssetManager::addTexture( model->getTextureName(i), model->getTextureName(i) );

		//keep track of textures
		texArray[i] = AssetManager::getTexture( model->getTextureName(i) );
	}


	//store graphics object before sending it out.
	GraphicsObjectFlatTexture* temp = new GraphicsObjectFlatTexture(model,texArray[0],texArray[1],texArray[2],texArray[3]);
	graphicsObjectBin.push_back(temp);

	return temp;
}
GraphicsObjectWireFrame* GraphicsObjectManager::priv_makeGObj_WireFrame( Model* model )
{
	GraphicsObjectWireFrame* temp = new GraphicsObjectWireFrame( model );
	graphicsObjectBin.push_back(temp);

	return temp;
}
GraphicsObjectColorNoTexture* GraphicsObjectManager::priv_makeGObj_NoTexture( Model* model, const Vect& color )
{
	GraphicsObjectColorNoTexture* temp = new GraphicsObjectColorNoTexture( model );
	temp->color = color;

	graphicsObjectBin.push_back(temp);

	return temp;
}
