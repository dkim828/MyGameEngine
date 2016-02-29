#include "ParticleBurst_Round.h"

#include "ParticleEmitter.h"
#include "ParticleEffect.h"
#include "Particle.h"

#include "TimeManager.h"
#include "CameraManager.h"

#include "ParticleEffectManager.h"

ParticleBurst_Round::ParticleBurst_Round( ) : ParticleBurst()
{
}
ParticleBurst_Round::~ParticleBurst_Round( )
{
}

void ParticleBurst_Round::init( ParticleEmitter* emitter )
{
	this->p_Emitter = emitter;
	this->curColor = this->p_Emitter->burstColor;
	this->curColorDelta = this->p_Emitter->burstColorDelta;
	this->curScale = this->p_Emitter->burstScale;
	this->curScaleDelta = this->p_Emitter->burstScaleDelta;
	
	Vect startAngle = emitter->orientation;
	float temp = startAngle[x];
	startAngle[x] = startAngle[y] * -1;
	startAngle[y] = startAngle[z] * -1;
	startAngle[z] = temp; 

	float angleDelta = MATH_2PI / this->numParticles;
	Matrix rotationDelta;
	rotationDelta.set(ROT_AXIS_ANGLE, emitter->orientation, angleDelta );

	//init all Particles
	for( int i = 0; i < this->numParticles; i++ )
	{
		this->particleArray[i].pos.set( emitter->position );

		this->particleArray[i].vel.set( startAngle );
		this->particleArray[i].vel = this->particleArray[i].vel * this->p_Emitter->burstSpeed;

		this->particleArray[i].acc.set( startAngle );
		this->particleArray[i].acc = this->particleArray[i].acc * this->p_Emitter->burstAccel;

		startAngle = startAngle * rotationDelta;
	}


	this->TimeToEnd = TimeManager::getTotalTime() + emitter->p_ParticleEffect->getBurstLife();
}



void ParticleBurst_Round::updateDraw( float deltaTime )
{
	CameraManager::getCurrentCam()->getPos( this->CamPos );

	//COLOR
	this->curColor += this->curColorDelta * deltaTime;
	this->gObj->color.set( this->curColor );


	//SCALE - outside of loop b/c burst has same scale
	this->curScale +=  this->curScaleDelta * deltaTime;
	this->Scale.set( SCALE, this->curScale );

	//UPDATE then DRAW individual particles
	for( int i = 0; i < this->numParticles; ++i )
	{
		//UPDATE PARTICLES
		this->particleArray[i].vel = this->particleArray[i].vel + this->particleArray[i].acc * deltaTime;
		this->particleArray[i].pos = this->particleArray[i].pos + this->particleArray[i].vel * deltaTime;
	
		//DRAW SETUP
			//ROTATION - Billboarded
		this->DirTowardsCam = this->CamPos - this->particleArray[i].pos;
		this->Rotation.set( ROT_ORIENT, this->DirTowardsCam, this->Up );
			//TRANSLATION - from particle::pos
		this->Translation.set( TRANS, this->particleArray[i].pos );
			//SCALE - set outside of loop;
	
		//DRAW PARTICLES
		this->Transform = this->Scale * this->Rotation * this->Translation;
		this->gObj->setWorld( this->Transform );
		this->gObj->Render();
	}
}