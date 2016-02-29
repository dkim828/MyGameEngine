#ifndef PARTICLEBURST_ROUND_H
#define PARTICLEBURST_ROUND_H


#include "ParticleHeader.h"
#include "ParticleBurst.h"

class ParticleBurst_Round : public ParticleBurst
{
public:
	ParticleBurst_Round();
	~ParticleBurst_Round();
	

	virtual void init( ParticleEmitter* emitter );
	
	virtual void updateDraw( float deltaTime );

private:
};

#endif