#ifndef BURSTPOOL_H
#define BURSTPOOL_H

#include "Azul.h"

#include "ParticleHeader.h"

#include <stack>

class ParticleBurst;

class ParticleBurstManager
{
	friend class ParticleEffect;

public:
	explicit ParticleBurstManager( int maxBursts, int maxParticles, P_BurstType burstType, GraphicsObjectColorNoTexture* gObj );
	~ParticleBurstManager();

	//DEBUG
	int particlesPerBurst;
	int particlesLive;


	ParticleBurst*	getBurst();
	void returnBurst( int id );
private:
	ParticleBurst*		particleBurstArray;
	int					numBursts;
	std::stack<int>		availableBursts;
};


#endif