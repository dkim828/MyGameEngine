/*
* TO BE DONE BY USER
*/


#include "../W14 Engine/AssetManager.h"

void AssetManager::loadAssets()
{
	addModel("ship", "space_frigate.fbx");
	addModel("cottage", "Cottage.fbx");
	addModel("ground" , "Plane.fbx");

	addTexture("t_ship", "space_frigate.tga");
	addTexture("t_ground", "grid.tga");

	addTexture("grassSeamless", "GrassTextureSeamless.tga");
	addTexture("stealNotSeamless", "SteelTextureNOTseamless.tga");


	addModel( "tank_body", "TankBody.fbx" );
}