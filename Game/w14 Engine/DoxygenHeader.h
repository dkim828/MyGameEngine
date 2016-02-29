
/** \defgroup DEMO W14Engine Demo
\brief This has the setup for a basic demo. The examples within the documentation use code from this demo

I did not know how to approach this without including the Demo Files within the Doxygen visibility thing.

*/


/**************************************************************************************************************/
/**************************************************************************************************************/
/**************************************************************************************************************/

/** \defgroup W14_MODULE W14Engine Components

\brief These components and functions available to the user
*/


/** \defgroup GAMEENTITY GameEntity
\ingroup W14_MODULE

\brief All game entities will be derived from GameEntity
*/


/** \defgroup AUTOEVENTS Default Components
\ingroup GAMEENTITY

\brief Certain components of GameEntitt are automatically registered/deregistered to the engine
*/

/** \defgroup UPDATE Update
\ingroup AUTOEVENTS

\brief Callbacks associated with updating the GameEntity
*/

/** \defgroup DRAW Draw 
\ingroup AUTOEVENTS

\brief Callbacks associated with drawing/rendering the GameEntity
*/

/** \defgroup TERMINATION Termination
\ingroup AUTOEVENTS

\brief Callbacks associated with termination or destroying the GameEntity
*/

/** \defgroup INPUT Input
\ingroup GAMEENTITY

\brief Callbacks associated with keyboard key events. In order for any of these callbacks to be activated, the 
GameEntity must be registered for keys and the type of events by using the registerKeyboardKey() function using InputFlags
*/

/** \defgroup ALARM Alarms
\ingroup GAMEENTITY

\brief Each GameEntity can set up to 3 separate alarms (ID_0 through ID_2) and have the associated callback triggered

*/

/** \defgroup COLLISION Collision
\ingroup GAMEENTITY

\brief Basic structure and operations of the collision system
*/

/** \defgroup MANAGEMENT Management Functions
\ingroup GAMEENTITY
\brief Various methods to control internal aspects of the GameEntity.
*/

/** \defgroup SCENE Scene
\ingroup W14_MODULE
\brief A Scene is the space in which GameEntities exist. 

When deriving from Scene, there are two functions to implement: Scene::initScene() and Scene::endScene()
initScene is called when creating a new Scene and endScene is called when deleting a scene (whether is was by deletion
or change in scene).

Within initScene(), registration of specific GameEntity types for collision has to happen to set up collision for the
life of the scene.

Within endScene(), anything that should be resolved at the end of a scene should be here. Unhandled Game Entities are handled
per scene, so if a recycling factory is implemented, a recall function should be in endScene().
*/

/** \defgroup SCENEMAN Scene Management
\ingroup W14_MODULE
\brief W14 allows for multiple scenes in sequence

The SceneManager is a singleton manager that has life throughout the life of the game application.
It allows for a setting of a start Scene and a setting of a next Scene.

The SceneManager also has an accesor function to get a pointer to the current Scene
*/

/** \defgroup ASSETS Assets
\ingroup W14_MODULE
\brief Loading external assets into the game.
*/


/** \defgroup NOTFORUSER Internal Components - NOT for users
\ingroup W14_MODULE
\brief Classes/Functions/Members/Etc that are for W14 developers
*/

/** \defgroup NOTFORUSER_COL Collision
\ingroup NOTFORUSER
\brief Background Collision stuff
*/
/** \defgroup NOTFORUSER_AL Alarm
\ingroup NOTFORUSER
\brief Background Alarm stuff
*/


/**************************************************************************************************************/
/**************************************************************************************************************/
/**************************************************************************************************************/



/*! \mainpage W14Engine - David Kim

W14Engine is an educational 3D game engine being developed for GAM374 and GAM377 at Depaul University
\n
As it is now, W14 provides the user with basic functionality that allows the user to start creating a basic 3D game\n

*/

/*! \page tutorial W14 Tutorial
While W14 does take care of basic game tasks such as updating or drawing entities in the background, there is \n
nothing explicitly created from just the engine. Thus, the user must derive from Scene and GameEntity in order\n
to properly create a game. The user must also properly load assets in LoadAssets.cpp and load their wanted\n
content and start scenes in W14EngineContent.cpp.\n\n

<b>For a more detailed look at these components of W14Engine, have a look at the Modules section of this site</b>

\n

\section usage W14 Basic Usage
	- Every derived class that is directly connected to the W14Engine should #include "W14Common.h"
		- This header files has all the necessary includes for the user to have access to all the\n
		functions and classes that he/she should have access to.
	- W14 has a singleton AssetManager where the user can retrieve necessary GraphicsObjects to\n
	  draw their game entities.
		- The AssetManager by default loads three primitive objects without textures:
			- UnitBox
			- UnitSphere
			- UnitPyramid
		- However, if the user wants to use their own assets, the user must load their assets through a user\n
		  defined loadAssets() function in LoadAssets.cpp
		  \code		  
			void AssetManager::loadAssets()
			{
				addModel("ship", "myShipModel.fbx");
				addModel("boat", "myBoatModel.fbx");
			}
		  \endcode
				- The AssetManager keeps track of user-added models by use of string keys. In the above case,\n
				the model for a ship has the key "ship". In order to retrieve a pointer to the created ship's \n
				GraphicsObject, one would access the AssetManager by:
				\code
				AssetManager::getGObj( "ship" );
				\endcode

				\n

	- W14 has a base GameEntity class for users to derive their own game objects. It supplies basic functionality\n
	needed for a game object to "exist" within a scene.
		- The Framework decouples and encapsulates different properties of a GameEntity into separate classes\n
		(known as X-ables) and GameEntity derives from them. Thus GameEntity has many virtual functions the user\n
		may define in their own game objects as needed depending on their game object's properties\n
			- The X-ables are:
				- Drawable
				- Updateable
				- Inputable
				- Alarmable
				- Collideable
				- Terminateable
		\code
		class MyShip : public GameEntity
		{
		public:
			MyShip();
			~MyShip();

			//This is a function that allows users to define object termination based code. 
			//MyShip defines this because it wants to set game scores and
			//because MyShip registers for Collision, it needs to deregister
			//collision in this function
				virtual void terminationEvent(){}; //virtual function from Terminateable

			//This is a callback function that gets called back upon collision
			//MyShip defines this because it will be colliding with
			//other game entities. This function is overloaded based
			//upon what kind of entities it may collide with
				virtual void collided( Collideable*  ){}; //virtual function from Collideable
				virtual void collided( MyShip*  ){};
				virtual void collided( MyBoat*  ){};

			//These are callback functions that are called upon keyboard pressed events.
			//MyShip defines keyPressed, but not keyReleased
			//as it wants to only move the ship upon keyPresses
				virtual void keyPressed( AZUL_KEY k, bool Ctrl, bool Shift, bool Alt ); //virtual functions from Inputable
				//virtual void keyReleased(  AZUL_KEY k, bool Ctrl, bool Shift, bool Alt );
	
			//This is a function that gets called upon every loop of the game
			//MyShip defines this because it wants to
			//increment some of its member values upon each game loop
				virtual void update(); //virtual function from Updateable

			//This is a function that gets called upon every draw event of the game
			//The draw() function is similar to update(), but the rendering related
			//code should be in here.
			//MyShip defines this because it wants to draw a
			//a ship onto the scene
				virtual void draw(); //virtual function from Drawable

			//These are callback functionss that are called upon alarm events
			//The user can set and cancel alarms by calling on functions through GameEntity.
			//MyShip does not define these because it will not be using any alarms
				//virtual void alarm0(){}; //virtual functions from Alarmable
				//virtual void alarm1(){};
				//virtual void alarm2(){};
		};
		\endcode
		
		\n

	- W14 has a base Scene class for users to derive their own scenes.
		- In order to make the different properties of GameEntity work, each Scene holds many managers\n
		that take care of specific duties that relate to the game entity properties such that user defined\n
		game entities within a scene run properly.
		- Luckily, all of that runs behind the scenes and the user only defines two functions and has access\n
		to two functions:
			- The two functions to define are:
				- initScene()
				- endScene()
			- The two functions that the user has access to are:
				- setCollisionPair< C1, C2>()
				- setCollisionSelf< C1 >()
			- The init and end scene functions are functions that are called upon the start of a scene and \n
			upon the end of a scene (be it through ending the game or switching scenes).
			- The two setCollision functions are directions given to W14's collision system that specify which\n
			game entities to test collision for within the user defined scene.
		\code
		void myScene::initScene()
		{
			//creating game entities to be put onto the scene
			new MyShip();
			Factory< MyBoat >::createBoat();

			//giving directions to the collision system
			setCollisionPair< MyShip, MyBoat >();
			setCollisionSelf< MyShip >();
			setCollisionSelf< MyBoat >();
		}
		void myScene::endScene()
		{
			//recalling boats that may be still on the scene to
			//a factory that owns them
			Factory< MyBoat >::recallBoats();
		}
		\endcode

		\n

	- One part of the W14 internal engine that the user has access to are 4 functions that are defined in \n
	W14EngineContent.cpp. These functions give access, to the user, places to add code upon startup of the\n
	of the game as well as the closing of it.
		- The four functions are:
			- initializeContext()
			- loadGameContent()
			- unloadGameContent()
			- terminateContext()
		- The two context functions are where the user should implement code that affects the game as an application
		- The two content functions are where the user should implement code directly related to the game such as\n
		initializing/deleting a factory, starting sounds(NOT IMPLEMENTED), or starting a scene to begin the game at.
		\code
		void Game::initializeContext()
		{
			printf("Ship and Boats Game started\n");

			glfwSetWindowPos(this->window, 10, 30);
		}

		void Game::loadGameContent()
		{
			SceneManager::setStartScene( new myScene() );
		}

		void Game::unloadGameContent()
		{
			Factory< MyBoat >::destroy();
		}

		void Game::terminateContext()
		{
		}
		\endcode
*/