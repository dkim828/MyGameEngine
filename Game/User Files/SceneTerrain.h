#ifndef SCENETERRAIN_H
#define SCENETERRAIN_H

#include "..\w14 Engine\W14Common.h"

class SceneTerrain : public Scene
{
public:
	SceneTerrain(){};
	SceneTerrain( const SceneTerrain& ){};
	~SceneTerrain(){};

	void initScene() override; 
	void endScene() override;
private:
};

#endif