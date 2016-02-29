#include "ParticleBurst.h"

#include "ParticleEmitter.h"
#include "ParticleEffect.h"
#include "Particle.h"

#include "TimeManager.h"
#include "CameraManager.h"

#include "ParticleEffectManager.h"

Matrix ParticleBurst::Scale = Matrix(IDENTITY);
Matrix ParticleBurst::Rotation = Matrix(IDENTITY);
Matrix ParticleBurst::Translation = Matrix(IDENTITY);
Matrix ParticleBurst::Transform = Matrix(IDENTITY);

ParticleBurst::ParticleBurst( )
{
	this->Up.set(0, 1, 0);
}
ParticleBurst::~ParticleBurst( )
{
	delete[] this->particleArray;
}


void ParticleBurst::burstSetup( int numParticles, int id, GraphicsObjectColorNoTexture* inGObj )
{
	this->particleArray = new Particle[ numParticles ];

	this->BurstID = id;
	this->numParticles = numParticles;
	this->gObj = inGObj;
}