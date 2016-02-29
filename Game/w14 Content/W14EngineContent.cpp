#include "..\w14 Engine\W14Engine.h"
#include "..\w14 Engine\SceneManager.h"
#include "..\w14 Engine\CameraManager.h"
#include "..\w14 Engine\TerrainObjectManager.h"

#include "..\w14 Engine\ParticleEffectManager.h"

#include "..\w14 Engine\ParticleEffect.h"

#include "../User Files/BulletFactory.h"

#include "..\User Files\SceneParticles.h"
#include "..\User Files\SceneTerrain.h"

void Game::initializeContext()
{
	printf("Game(): started\n");

	glfwSetWindowPos(this->window, 10, 30);
}

void Game::loadGameContent()
{
	TerrainObjectManager::loadTerrainModel( "m_mainTerrain", "TESTMAP_256_256_teardrops.tga", 1, 1 );
	TerrainObjectManager::loadTerrainModel( "m_smallTerrain", "TESTMAP_32_32_gradual.tga", 3, 3 );

	TerrainObjectManager::loadTerrainObject("mainTerrain", "m_mainTerrain", "stealNotSeamless", 512,64,0 );
	TerrainObjectManager::loadTerrainObject("mainTerrainGrassAndBigger", "m_mainTerrain", "grassSeamless", 1024,128,0 );
	TerrainObjectManager::loadTerrainObject( "smallTerrain", "m_smallTerrain","grassSeamless", 512, 64, 0 );


	ParticleEffect* temp = new ParticleEffect();
	temp->setMaxPossibleBursts( 200 );
	temp->setBurstType( P_BurstType::ROUND );
	temp->setBurstColor( Colors::Red, Colors::Green, P_BoundaryType::MIN_TO_MAX );
	temp->setBurstIntervalAndCount( 0.05f, 500 );
	temp->setBurstLife( 1.0f );
	temp->setBurstScale( Vect( 1.5f, 1.5f, 0.0f ), Vect( 0.0f,0.0f,0.0f), P_BoundaryType::MIN_TO_MAX);
	temp->setBurstSpeed( 50.0f, 100.0f, P_BoundaryType::MIN_TO_MAX);
	temp->setEmitterLife( 10.0f );
	ParticleEffectManager::LoadEffect( "Round1000", temp );

	ParticleEffect* tempTwo = new ParticleEffect();
	tempTwo->setMaxPossibleBursts( 100 );
	tempTwo->setBurstType( P_BurstType::SPRAY );
	tempTwo->setBurstColor( Colors::White, Colors::Magenta, P_BoundaryType::MIN_TO_MAX );
	tempTwo->setBurstIntervalAndCount( 0.1f, 1000 );
	tempTwo->setBurstLife( 1.0f );
	tempTwo->setBurstScale( Vect( 1.5f, 1.5f, 0.0f ), Vect( 0.0f,0.0f,0.0f), P_BoundaryType::MIN_TO_MAX);
	tempTwo->setBurstSpeed( 30.0, 0.0f, P_BoundaryType::MIN_TO_MAX);
	tempTwo->setEmitterLife( 10.0f );
	tempTwo->setBurstAngle( -MATH_2PI, MATH_2PI );
	ParticleEffectManager::LoadEffect( "Confetti", tempTwo );

	ParticleEffect* spout = new ParticleEffect();
	spout->setMaxPossibleBursts( 512 );
	spout->setBurstType( P_BurstType::SPRAY );
	spout->setBurstColor( Colors::White, Colors::Blue, P_BoundaryType::MIN_TO_MAX );
	spout->setBurstIntervalAndCount( 0.05f, 50 );
	spout->setBurstLife( 1.0f );
	spout->setBurstScale( Vect( 1.5f, 1.5f, 0.0f ), Vect( 0.0f,0.0f,0.0f), P_BoundaryType::MIN_TO_MAX);
	spout->setBurstSpeed( 20.0f, 0.0f, P_BoundaryType::MIN_TO_MAX);
	spout->setEmitterLife( 10.0f );
	spout->setBurstAngle( -0.25, 0.25f );
	ParticleEffectManager::LoadEffect( "WaterSpout", spout );
	
	ParticleEffect* explosion = new ParticleEffect();
	explosion->setMaxPossibleBursts( 100 );
	explosion->setBurstType( P_BurstType::SPRAY );
	explosion->setBurstColor( Colors::Red, Colors::Yellow, P_BoundaryType::MIN_TO_MAX );
	explosion->setBurstIntervalAndCount( 1.0f, 500 );
	explosion->setBurstLife( 0.5f );
	explosion->setBurstScale( Vect( 1.5f, 1.5f, 1.5f ), Vect( 0.0f,0.0f,0.0f), P_BoundaryType::MIN_TO_MAX);
	explosion->setBurstSpeed( 30.0f, 0.0f, P_BoundaryType::MIN_TO_MAX);
	explosion->setEmitterLife( 1.0f );
	explosion->setBurstAngle( -MATH_2PI, MATH_2PI );
	ParticleEffectManager::LoadEffect( "ExplosionOne", explosion );

	ParticleEffect* explosion1 = new ParticleEffect();
	explosion1->setMaxPossibleBursts( 100 );
	explosion1->setBurstType( P_BurstType::SPRAY );
	explosion1->setBurstColor( Colors::White, Colors::Yellow, P_BoundaryType::MIN_TO_MAX );
	explosion1->setBurstIntervalAndCount( 1.5f, 1000 );
	explosion1->setBurstLife( 1.5f );
	explosion1->setBurstScale( Vect( 1.0f, 1.0f, 1.0f ), Vect( 0.0f,0.0f,0.0f), P_BoundaryType::MIN_TO_MAX);
	explosion1->setBurstSpeed( 50.0f, 0.0f, P_BoundaryType::MIN_TO_MAX);
	explosion1->setEmitterLife( 1.5f );
	explosion1->setBurstAngle( -MATH_2PI, MATH_2PI );
	ParticleEffectManager::LoadEffect( "ExplosionTwo", explosion1 );



	SceneManager::setStartScene( new SceneParticles );
}

void Game::unloadGameContent()
{
	BulletFactory::destroy();
}

void Game::terminateContext()
{
}