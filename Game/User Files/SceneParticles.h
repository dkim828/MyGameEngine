#ifndef SCENEPARTICLES_H
#define SCENEPARTICLES_H

#include "..\w14 Engine\W14Common.h"

class SceneParticles : public Scene
{
public:
	SceneParticles(){};
	SceneParticles( const SceneParticles& ){};
	~SceneParticles(){};

	void initScene() override; 
	void endScene() override;
private:
};

#endif