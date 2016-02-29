#include "ParticleBurst_Spray.h"

#include "ParticleEmitter.h"
#include "ParticleEffect.h"
#include "Particle.h"

#include "TimeManager.h"
#include "CameraManager.h"

#include "ParticleEffectManager.h"


const Vect ParticleBurst_Spray::grav = Vect(0.0f, -98.0f, 0.0f );

ParticleBurst_Spray::ParticleBurst_Spray( ) : ParticleBurst()
{
}
ParticleBurst_Spray::~ParticleBurst_Spray( )
{
}

void ParticleBurst_Spray::init( ParticleEmitter* emitter )
{
	this->p_Emitter = emitter;
	this->curColor = this->p_Emitter->burstColor;
	this->curColorDelta = this->p_Emitter->burstColorDelta;
	this->curScale = this->p_Emitter->burstScale;
	this->curScaleDelta = this->p_Emitter->burstScaleDelta;
	

	//init all Particles
	for( int i = 0; i < this->numParticles; i++ )
	{
		this->particleArray[i].pos.set( emitter->position );

		this->particleArray[i].vel.set( emitter->orientation );
		this->particleArray[i].vel = this->particleArray[i].vel + Vect( MathTools::getRandFloat(p_Emitter->burstAngleMin, p_Emitter->burstAngleMax), 
																		MathTools::getRandFloat(p_Emitter->burstAngleMin, p_Emitter->burstAngleMax),  
																		MathTools::getRandFloat(p_Emitter->burstAngleMin, p_Emitter->burstAngleMax) );
		this->particleArray[i].vel = this->particleArray[i].vel * this->p_Emitter->burstSpeed;
	}


	this->TimeToEnd = TimeManager::getTotalTime() + emitter->p_ParticleEffect->getBurstLife();
}



void ParticleBurst_Spray::updateDraw( float deltaTime )
{
	CameraManager::getCurrentCam()->getPos( this->CamPos );

	//COLOR
	this->curColor += this->curColorDelta * deltaTime;
	this->gObj->color.set( this->curColor );


	//SCALE - outside of loop b/c burst has same scale
	this->curScale +=  this->curScaleDelta * deltaTime;
	this->Scale.set( SCALE, this->curScale );

	Vect acc = ParticleBurst_Spray::grav * deltaTime;

	//UPDATE then DRAW individual particles
	for( int i = 0; i < this->numParticles; ++i )
	{
		//UPDATE PARTICLES
		this->particleArray[i].vel = this->particleArray[i].vel + acc;
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