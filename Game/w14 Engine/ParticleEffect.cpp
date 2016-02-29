#include "ParticleEffect.h"

#include "ParticleBurstManager.h"
#include "ParticleEffectManager.h"
#include "ParticleEmitter.h"
#include "ParticleBurst.h"

ParticleEffect::ParticleEffect()
{
	this->burstPool = 0;
	this->gObj = 0;
}
ParticleEffect::~ParticleEffect()
{
	while( !recycledEmitters.empty() )
	{
		delete recycledEmitters.top();
		recycledEmitters.pop();
	}	
	
	for( auto it = activeEmitters.begin();
		 it != activeEmitters.end(); it++ )
	{
		delete (*it);
	}
	activeEmitters.clear();


	if( this->burstPool != 0 )
		delete this->burstPool;
}


void ParticleEffect::setBurstType( P_BurstType type )
{
	this->b_type = type;
}
void ParticleEffect::setGraphicsObject( GraphicsObjectColorNoTexture* particleG )
{
	this->gObj = particleG;
	this->burstPool = new ParticleBurstManager( b_maxPossibleBursts, b_numParticles, b_type, this->gObj );
}
void ParticleEffect::setMaxPossibleBursts( int count )
{
	this->b_maxPossibleBursts  = count;
}
void ParticleEffect::setEmitterLife( float life )
{
	this->e_life = life;
}
void ParticleEffect::setBurstIntervalAndCount( float interval, int count )
{
	this->b_numParticles = count;
	this->b_frequency	 = interval;
}
void ParticleEffect::setBurstLife( float life )
{
	this->b_life = life;
}
void ParticleEffect::setBurstScale( const Vect& minScale, const Vect& maxScale, P_BoundaryType delta )
{
	this->b_scale= minScale;
	this->b_scaleMax = maxScale;
	this->b_scaleDeltaType = delta;
}
void ParticleEffect::setBurstColor( const Vect& minColor, const Vect& maxColor, P_BoundaryType delta )
{
	this->b_color= minColor;
	this->b_colorMax = maxColor;
	this->b_colorDeltaType = delta;
}
void ParticleEffect::setBurstSpeed( float min, float max, P_BoundaryType delta )
{
	this->b_speed = min;
	this->b_speedMax = max;
	this->b_speedDeltaType = delta;
}
void ParticleEffect::setBurstAngle( float min, float max)
{
	this->b_angleMin = min;
	this->b_angleMax = max;
}



float ParticleEffect::getEmitterLife()
{
	return this->e_life;
}
int ParticleEffect::getBurstCount()
{
	return this->b_numParticles;
}
float ParticleEffect::getBurstFreq()
{
	return this->b_frequency;
}
float ParticleEffect::getBurstLife()
{
	return this->b_life;
}
void ParticleEffect::getBurstScaleAndDelta( Vect& scale, Vect& delta )
{
	scale.set( this->b_scale );

	Vect deltaCalc = this->b_scaleMax - this->b_scale;
	deltaCalc = deltaCalc * ( 1 / this->b_life );
	delta = deltaCalc;
}
void ParticleEffect::getBurstColorAndDelta( Vect& color, Vect& delta )
{
	color.set( this->b_color );

	Vect deltaCalc = this->b_colorMax - this->b_color;
	deltaCalc = deltaCalc * ( 1 / this->b_life ) ;
	delta = deltaCalc;
}
void ParticleEffect::getBurstSpeedAndDelta( float& speed, float& acceleration )
{
	float acc = this->b_speedMax - this->b_speed;
	acceleration = acc * ( 1 / this->b_life );
	speed = this->b_speed;
}
void ParticleEffect::getBurstAngles( float& min, float& max )
{
	min = this->b_angleMin;
	max = this->b_angleMax;
}



ParticleBurst* ParticleEffect::getBurst()
{
	return this->burstPool->getBurst();
}
void ParticleEffect::returnBurst(int id)
{
	this->burstPool->returnBurst( id );
}



void ParticleEffect::spawnEmitter( const Vect& pos, const Vect& rot )
{
	ParticleEmitter* e;

	if( this->recycledEmitters.empty() )
	{
		e = new ParticleEmitter( this );
	}
	else
	{
		e = this->recycledEmitters.top();
		this->recycledEmitters.pop();
	}

	this->activeEmitters.insert( e );
	
	//**********************************************
	//**********************************************
	e->init( pos, rot );
	//RETURN OR e->init or something here
	//**********************************************
	//**********************************************
}
void ParticleEffect::returnEmitter( ParticleEmitter* emitter )
{
	this->activeEmitters.erase( emitter );
	this->recycledEmitters.push( emitter );
	
	//Maybe not????
	emitter->deactivate();
}
void ParticleEffect::recallEmitters( )
{
	ParticleEmitter* e;

	for( auto it = activeEmitters.begin();
		it != activeEmitters.end(); it++ )
	{
		e = (*it);
		e->deactivate();
		this->recycledEmitters.push( e );
	}

	this->activeEmitters.clear();
}