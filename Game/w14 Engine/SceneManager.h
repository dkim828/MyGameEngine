#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <list>

class Scene;

class SceneManager
{
friend class Game;

public:
	/**
	\brief Sets the Scene that is to be the starting scene of the game
	\ingroup SCENEMAN

	This function is within a singleton called SceneManager so it is able to be called from almost anywhere
	on the user's code. The argument is a pointer to a scene which would a derived scene class made by the
	user. However, this is a function to just set the starting scene.

	\b Note: this function is set START scene. Meaning this function will only be called once at the beginning of
	the game in Game::LoadGameContent()

	\b Example: Before the game actually starts running, there are four functions in W14EngineContent.cpp that are
	used for the startup of the game as well as the closing of it. Within that .cpp there is a function called 
	Game::loadGameContent(). This is a function that is called right before the start of the game loop and this is
	where the user should set the starting scene.
		\code
		void Game::loadGameContent()
		{
			SceneManager::setStartScene( new SceneOne );
		}
		\endcode

	\param s	The Scene to be set as the starting scene.
	*/
	static void setStartScene( Scene* s );

	/**
	\brief Sets the next Scene to be displayed once the current scene's cycles are done/cleaned up
	\ingroup SCENEMAN

	This function is within a singleton called SceneManager so it is able to be called from almost anywhere
	on the user's code. The argument is a pointer to a scene which would a derived scene class made by the
	user. 

	Once this function is called, the SceneManager runs through all the current Scene 's managers, calls its
	Scene::endScene() function, then the current scene is changed to the one entered into this function as an
	argument

	\b Example: In SceneOne of the Demo, there exists a Pyramid GameEntity. It is set within that scene to be
	able to be collided with Ships and Bullets. While the Pyramid is just marked for Termination when it collides
	with a Bullet, once it is collided with a ship, it changes scenes by
	calling SceneManager::setNextScene()
		\code
		void Pyramid::collided( Ship* )
		{
			SceneManager::setNextScene( new SceneTwo );
		}
		void Pyramid::collided( Bullet* )
		{
			markForTermination();
		}
		\endcode

	\param s	The Scene to be set as the next scene
	*/
	static void setNextScene( Scene* s );

	/**
	\brief An Accessor function to get a pointer to the current scene
	\ingroup SCENEMAN

	This function is an accessor function that that allows the
	user to access a pointer to the current scene.
	*/
	static Scene* getCurrentScene() { return instance().currentScene; };

private:
	//Functions only used by Game(engine cpp)
	static void destroy();

	static void drawCurrentScene();
	static void updateCurrentScene();
	//Functions only used by Game(engine cpp) END


	//Private Variables
	Scene*	currentScene;
	Scene*	nextScene;
	//std::list< Scene* > sceneList;

	//Private Functions
	void privSetStartScene( Scene* s );
	void privSetNextScene( Scene* s );

	void internalChangeScene();


	SceneManager();
	SceneManager( const SceneManager& ) {};
	~SceneManager();
	
	//Singleton Instance
	static SceneManager* SceneManagerInst;

	//Instance Access
	static SceneManager& instance()
	{
		if( !SceneManagerInst )
			SceneManagerInst = new SceneManager();

		return *SceneManagerInst;
	};
};

#endif SCENEMANAGER_H