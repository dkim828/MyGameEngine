#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "ParticleHeader.h"

#include "Drawable.h"
#include "Alarmable.h"
#include <list>

class ParticleEffect;

class ParticleEmitter : public Drawable, public Alarmable
{
	friend class ParticleBurst;
	friend class ParticleBurst_Round;
	friend class ParticleBurst_Spray;

public:
	ParticleEmitter( ParticleEffect* inEffect );
	~ParticleEmitter();

	void init( const Vect& pos, const Vect& rot );

	void activate();
	void deactivate();

	//FROM DRAWABLE
	virtual void draw();

	//FROM ALARMABLE
	virtual void alarm0();
	virtual void alarm1();
	virtual void alarm2();
private:
	std::list< ParticleBurst* > bursts;

	ParticleEffect*		p_ParticleEffect;

	Vect	position;
	Vect	orientation;

	//Emitter's Pre-computed data
	Vect		burstColor;
	Vect		burstColorDelta;

	Vect		burstScale;
	Vect		burstScaleDelta;

	float		burstSpeed;
	float		burstAccel;

	float		burstAngleMin;
	float		burstAngleMax;

	float		emitterLife;
	int			burstCount;
	float		burstFreq;

	//Private functions
	void addBurst();
};



#endif