#ifndef PARTICLEBURST_H
#define PARTICLEBURST_H

#include "ParticleHeader.h"

class ParticleEmitter;
class Particle;

class ParticleBurst
{
public:
	ParticleBurst();
	void burstSetup( int numParticles, int id, GraphicsObjectColorNoTexture* inGObj );
	~ParticleBurst();
	

	virtual void init( ParticleEmitter* emitter ) = 0;
	
	virtual void updateDraw( float deltaTime ) = 0;


	int		BurstID;
	float	TimeToEnd;
protected:
	//Particle Draw members 64 bytes per matrix
	//ParticleBurst used to be 400 byte object
	static	Matrix Scale;
	static	Matrix Rotation;
	static	Matrix Translation;
	static	Matrix Transform;

	//BillBoarding setup members
	Vect Up;
	Vect DirTowardsCam;
	Vect CamPos;

	//For Particles
	Vect	curColor;
	Vect	curColorDelta;
	Vect	curScale;
	Vect	curScaleDelta;

	int			numParticles;

	Particle*	particleArray;
	ParticleEmitter*	p_Emitter;
	GraphicsObjectColorNoTexture* gObj;
};


#endif