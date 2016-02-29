#include "ParticleBurstManager.h"
#include "ParticleEffect.h"

#include "ParticleBurst_Round.h"
#include "ParticleBurst_Spray.h"

#include "Tools\TestGlobals.h"

int TestGlobals::numParticles = 0;

ParticleBurstManager::ParticleBurstManager( int maxBursts, int maxParticles, P_BurstType burstType, GraphicsObjectColorNoTexture* gObj ) : numBursts( maxBursts )
{
	switch( burstType )
	{
	case P_BurstType::ROUND:
		particleBurstArray = new ParticleBurst_Round[ numBursts ];
		break;
		
	case P_BurstType::SPRAY:
		particleBurstArray = new ParticleBurst_Spray[ numBursts ];
		break;
	default:
		assert(0);
	}


	for( int i = 0; i < numBursts; ++i )
	{
		this->particleBurstArray[i].burstSetup( maxParticles, i, gObj );
		this->availableBursts.push( i );
	}

	//DEBUG STUFF================================================//
		this->particlesPerBurst = maxParticles;
		this->particlesLive = 0;
	//-DEBUG STUFF================================================//
}
ParticleBurstManager::~ParticleBurstManager()
{
	int checking = sizeof( ParticleBurst );
 	delete[] this->particleBurstArray;
	checking = 1;
}


ParticleBurst* ParticleBurstManager::getBurst( )
{
	assert( !this->availableBursts.empty() );

	//DEBUG STUFF================================================//
		this->particlesLive+= this->particlesPerBurst;

		TestGlobals::numParticles += particlesPerBurst;
	//-DEBUG STUFF================================================//

	int out = this->availableBursts.top();
	this->availableBursts.pop();

	return &this->particleBurstArray[ out ];
}
void ParticleBurstManager::returnBurst( int id )
{
	this->availableBursts.push(id);

	//DEBUG STUFF================================================//
		this->particlesLive-= this->particlesPerBurst;

		TestGlobals::numParticles -= particlesPerBurst;
	//-DEBUG STUFF================================================//
}