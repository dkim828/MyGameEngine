#ifndef PARTICLEEFFECTMANAGER
#define PARTICLEEFFECTMANAGER

#include "Azul.h"
#include "ParticleHeader.h"

#include <string>
#include <map>
#include <list>
#include <set>

class BurstPool;
class ParticleEffect;

class ParticleEffectManager
{
	friend class Game;//give access to destroy

public:
	static void SpawnEffect( std::string effectKey, const Vect& pos, const Vect& rot );

private:
	//Make ParticleModel
	void makeParticleModel();
	GraphicsObjectColorNoTexture*	particleGObj;

	//Effects
	std::map< std::string, ParticleEffect* > allEffects;
	static void LoadEffect( std::string effectKey, ParticleEffect* inEffect );


	

	//===========================================Singleton setup===========================================//
	static ParticleEffectManager* inst;
	ParticleEffectManager();
	~ParticleEffectManager();

	ParticleEffectManager& operator=( const ParticleEffectManager& other ); //Prevent assignment
	ParticleEffectManager( const ParticleEffectManager& other );

	static ParticleEffectManager& instance()
	{
		if( !inst )
			inst = new ParticleEffectManager();

		return *inst;
	};


	static void init();
	static void destroy();
};


#endif