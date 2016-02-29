#include "W14Engine.h"

#include "AssetManager.h"
#include "GraphicsObjectManager.h"
#include "TerrainObjectManager.h"

#include "SceneManager.h"
#include "TimeManager.h"
#include "CameraManager.h"

#include "ParticleEffectManager.h"

#include "Tools\ErrorOut.h"
#include "Tools\Visualizer.h"
#include "Tools\TestGlobals.h"


 Game* Game::ptrGame = 0;

Game::Game( const char * const windowName, int widthScreen, int heightScreen )
: Engine( windowName, widthScreen, heightScreen)
{
	ptrGame = this;
}


void Game::Initialize()
{
	TimeManager::init();
	CameraManager::init( this->screenWidth, this->screenHeight );
	
	//User Defined
	initializeContext();
}


void Game::LoadContent()
{
	AssetManager::loadAssets();

	ParticleEffectManager::init();

	//User Defined
	loadGameContent();
}


void Game::Update()
{
	
//	printf("TotalTime: %.2f s lastFrame: %.4f s (%.0f FPS)\n",TimeManager::getTotalTime(), TimeManager::getFrameTime(), 1/TimeManager::getFrameTime());
	char buff[100];
	sprintf_s(buff, "TotalTime: %.2f s lastFrame: %.4f s (%.0f FPS)",TimeManager::getTotalTime(), TimeManager::getFrameTime(), 1/TimeManager::getFrameTime());
	glfwSetWindowTitle( this->window, buff );

	
	printf( "NumberOfParticles: %d \n", TestGlobals::numParticles );

	//TimeUpdate
	TimeManager::update();
	//SceneUpdate
	SceneManager::updateCurrentScene();
	//CameraUpdate
	CameraManager::update();
}


void Game::Draw()
{ 
	SceneManager::drawCurrentScene();

	//Tool
	Visualizer::drawAllVisuals();
}


void Game::UnLoadContent()
{
	unloadGameContent();//User Defined

	SceneManager::destroy();
	TimeManager::destroy();
	CameraManager::destroy();
	
	TerrainObjectManager::destroy();
	GraphicsObjectManager::destroy();
	AssetManager::destroy();

	ParticleEffectManager::destroy();

	//managing my Tools
	ErrorOut::destroy();
	Visualizer::destroy();

	terminateContext();//User Defined
}
