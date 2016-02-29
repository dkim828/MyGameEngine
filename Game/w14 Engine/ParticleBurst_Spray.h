#ifndef PARTICLEBURST_SPRAY_H
#define PARTICLEBURST_SPRAY_H


#include "ParticleHeader.h"
#include "ParticleBurst.h"

class ParticleBurst_Spray : public ParticleBurst
{
public:
	ParticleBurst_Spray();
	~ParticleBurst_Spray();
	

	virtual void init( ParticleEmitter* emitter );
	
	virtual void updateDraw( float deltaTime );

private:
	static const Vect grav;
};

#endif