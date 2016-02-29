#include "ParticleEmitter.h"

#include "TimeManager.h"
#include "ParticleBurst.h"
#include "ParticleEffect.h"
#include "ParticleEffectManager.h"

ParticleEmitter::ParticleEmitter( ParticleEffect* inEffect )
{
	this->p_ParticleEffect = inEffect;

	this->emitterLife = this->p_ParticleEffect->getEmitterLife();
	this->burstCount = this->p_ParticleEffect->getBurstCount();
	this->burstFreq = this->p_ParticleEffect->getBurstFreq();
	
	this->p_ParticleEffect->getBurstColorAndDelta( this->burstColor, this->burstColorDelta );
	this->p_ParticleEffect->getBurstScaleAndDelta( this->burstScale, this->burstScaleDelta );
	this->p_ParticleEffect->getBurstSpeedAndDelta( this->burstSpeed, this->burstAccel );
	this->p_ParticleEffect->getBurstAngles( this->burstAngleMin, this->burstAngleMax );
}
ParticleEmitter::~ParticleEmitter()
{	
	while( !this->bursts.empty() )
	{
		p_ParticleEffect->returnBurst( this->bursts.front()->BurstID );
		this->bursts.pop_front();
	}

	bursts.clear();
}


void ParticleEmitter::init( const Vect& pos, const Vect& rot )
{
	this->position.set( pos );
	this->orientation.set( rot );

	this->activate();
}

void ParticleEmitter::activate()
{
	//Start emitter with a burst
	this->addBurst();

	//start updating/drawing burst
	this->registerDrawable();

	//set alarm for next emit
	this->setAlarm( Alarm::ID_0, this->burstFreq );

	//set alarm for emitter death
	this->setAlarm( Alarm::ID_1, this->emitterLife );
}
void ParticleEmitter::deactivate()
{
	//cancel alarms to stop emitting
	this->cancelAlarm( Alarm::ID_0 );
	//stop updating/drawing
	this->deregisterDrawable();

	//returning all bursts
	while( !this->bursts.empty() )
	{
		p_ParticleEffect->returnBurst( this->bursts.front()->BurstID );
		this->bursts.pop_front();
	}
}


void ParticleEmitter::draw()
{
	if(! bursts.empty() )
	{
		for( auto it = this->bursts.begin(); it != this->bursts.end(); ++it )
		{
			(*it)->updateDraw( TimeManager::getFrameTime() );
		}

		if( TimeManager::getTotalTime() >= this->bursts.front()->TimeToEnd )
		{
			p_ParticleEffect->returnBurst( this->bursts.front()->BurstID );
			this->bursts.pop_front();
		}
	}
}


void ParticleEmitter::addBurst()
{
	ParticleBurst* temp = p_ParticleEffect->getBurst();

	temp->init( this );

	this->bursts.push_back( temp );
}

void ParticleEmitter::alarm0()
{
	this->addBurst();
	
	this->setAlarm( Alarm::ID_0, this->burstFreq );
}
void ParticleEmitter::alarm1()
{
	this->p_ParticleEffect->returnEmitter( this );
}
void ParticleEmitter::alarm2()
{
}
