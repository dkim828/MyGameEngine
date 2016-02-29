#ifndef PARTICLEEFFECT_H
#define PARTICLEEFFECT_H

#include "ParticleHeader.h"

#include <stack>
#include <set>

class ParticleEmitter;
class ParticleBurst;
class ParticleBurstManager;

class ParticleEffect
{
	friend class ParticleEffectManager;

public:
	ParticleEffect();
	~ParticleEffect();

	void setGraphicsObject( GraphicsObjectColorNoTexture* particleG );

	//Life defaults to 0
	void setEmitterLife( float life );
	void setMaxPossibleBursts( int count );
	void setBurstType( P_BurstType type );
	void setBurstIntervalAndCount( float interval, int count );
	void setBurstLife( float life );
	void setBurstScale( const Vect& minScale, const Vect& maxScale, P_BoundaryType delta );
	void setBurstColor( const Vect& minColor, const Vect& maxColor, P_BoundaryType delta ); 
	void setBurstSpeed( float min, float max, P_BoundaryType delta );
	void setBurstAngle( float min, float max);

	//Accessors for emitter
	float	getEmitterLife();

	int		getBurstCount();
	float	getBurstFreq();
	float	getBurstLife();
	void	getBurstScaleAndDelta( Vect& scale, Vect& delta );
	void	getBurstColorAndDelta( Vect& color, Vect& delta );
	void	getBurstSpeedAndDelta( float& speed, float& acceleration );
	void	getBurstAngles( float& min, float& max );


	//Emitter Management
	void spawnEmitter(const Vect& pos, const Vect& rot);
	void returnEmitter( ParticleEmitter* emitter );
	void recallEmitters( );

	//Burst Management
	ParticleBurst* getBurst();
	void returnBurst(int id);


private:
	//Object pool for bursts per Effect
	ParticleBurstManager* burstPool;

	//Recycling Factory for emitters per Effect
	std::set< ParticleEmitter* > activeEmitters;
	std::stack< ParticleEmitter* > recycledEmitters;

	//Effect Data
	GraphicsObjectColorNoTexture* gObj;

	float		e_life;

	int			b_maxPossibleBursts;
	int			b_numParticles;
	float		b_frequency;

	float		b_life;

	float		b_angleMin;
	float		b_angleMax;

	P_BurstType	b_type;
	
	Vect			b_scale;
	Vect			b_scaleMax;
	P_BoundaryType	b_scaleDeltaType;
	Vect			b_color;
	Vect			b_colorMax;
	P_BoundaryType	b_colorDeltaType;

	float			b_speed;
	float			b_speedMax;
	P_BoundaryType	b_speedDeltaType;


};

#endif