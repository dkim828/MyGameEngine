#ifndef SCENE_H
#define SCENE_H

#include "CollisionManager.h"
#include <string>

class AlarmManager;
class InputableManager;
class UpdateableManager;
class DrawableManager;
class TerrainManager;
class TerminateableManager;

class TerminateableDumpster;


class Scene
{
friend class SceneManager;
friend class Alarmable;
friend class Inputable;
friend class Drawable;
friend class GameEntity;
friend class Terminateable;
friend class TerminateableManager;
template<class C> friend class CollisionTerrainProcessor;

public:
	Scene();
	Scene( const Scene& ){};
	virtual ~Scene();

	/// \brief Initializes the Scene with the new GameEntities and prepares the collision system
	/// \ingroup SCENE
	/// 
	/// This function is implemented in a derived Scene class. It will be called once when the scene is created and
	/// the user is responsible of creating Game Entities here as well as setting proper Collision Tests
	///
	///  
	///  \b Example: The following is from the Demo's SceneTwo. Two ships and a ground plane (all
	///		derived from GameEntity) are created in this function. Then the collision is set through the
	///		setCollisionFunctions. With the way the collision functions are called, with the scene: 
	///		all Bullet objects can collide against one another; all Ship Objects can collide against one
	///		another; and all Ship objects can collide with Bullet objects.
	///		\code
	///		void SceneTwo::initScene()
	///		{
	///			new Ship(0,25,0, 0);
	///			new Ship(0,25,60, 1, 3.14f);
	///			new GroundPlane();
	///
	///			setCollisionSelf<Bullet>();
	///			setCollisionSelf<Ship>();
	///			setCollisionPair<Ship, Bullet>();
	///		}
	///		\endcode
	virtual void initScene() = 0;

	/// \brief Ends the Scene
	/// \ingroup SCENE
	/// 
	/// This function is implemented in a derived Scene class. It will be called once when the scene is destroyed
	/// and a Scene is destroyed by a SceneManager when a scene is changed or when the game is exited.
	/// The user is responsible of taking care of any management or deletions of user created factories, objects,
	/// lists, etc that should lose scope once the scene ends.
	///  
	///	\b Note: Memory Management of GameEntities are handled behind the scenes by the TerminateableDumpster unless
	///		the user explicitly sets GameEntities to have a different owner a la Factory.
	///
	///  \b Example: The following is from the Demo's SceneTwo. The only GameEntity through the entirety of the demo
	///		are the Bullet GameEntities created by the Ship when it fires. So when a Scene ends, the BulletFactory
	///		recalls all the bullets on the scene before the scene change. Otherwise, the loose Bullets on the scene
	///		may cause a memory leak depending on the implementation of the factory
	///		\code
	///		void SceneTwo::endScene()
	///		{
	///			BulletFactory::recallBullets();
	///		}
	///		\endcode
	virtual void endScene() = 0;

protected:

	/// \brief Informs the collision system on what kinds of GameEntities to test collisions with
	/// \ingroup SCENE
	/// 
	/// This function is implemented in the Scene class for the user to call during initScene. It is
	///	a template function that tells the collision system to check for collision between the two 
	/// GameEntity types that are passed in as "arguments" through a scenes life.
	///
	///  
	///  \b Examples: Look in initScene()
	template< class C1, class C2 >
	void setCollisionPair()
	{
		collisionMan->setCollisionPair<C1, C2>();
	}

	/// \brief Informs the collision system on what kinds of GameEntities to test collisions with
	/// \ingroup SCENE
	/// 
	/// This function is implemented in the Scene class for the user to call during initScene. It is
	///	a template function that tells the collision system to check for collision between the same 
	/// GameEntity types that is passed in as "arguments" through a scenes life.
	///
	///  
	///  \b Examples: Look in initScene()
	template< class C1 >
	void setCollisionSelf()
	{
		collisionMan->setCollisionSelf<C1>();
	}

	template< class C >
	void setCollisionWithTerrain()
	{
		collisionMan->setCollisionWithTerrain<C>();
	}

	/**
	*/
	void setTerrain( std::string terrainKey );

private:
	InputableManager* inputableMan;
	DrawableManager* drawableMan;
	UpdateableManager* updateableMan;
	AlarmManager* alarmMan;
	CollisionManager* collisionMan;
	TerrainManager*	terrainMan;
	TerminateableManager* terminateableMan;

	TerminateableDumpster* dumpster;
	
	//Manager Accessors
	InputableManager* getInputableMan() { return inputableMan; };
	DrawableManager* getDrawableMan(){ return drawableMan; };
	UpdateableManager* getUpdateableMan(){ return updateableMan; };
	AlarmManager* getAlarmMan(){return alarmMan;};
	CollisionManager* getCollisionMan(){return collisionMan;};
	TerrainManager* getTerrainMan(){return terrainMan;};
	TerminateableManager* getTerminateableMan(){return terminateableMan;};

	TerminateableDumpster* getDumpster(){return dumpster;};

	/// \brief For Automatic Registration of X-Ables for GameEntities
	/// \ingroup NOTFORUSER
	/// 
	/// This function is the single place for developers to put registration to
	/// any X-Able manager to be done automatically.
	///
	/// GameEntity has a function called GameEntity::registerBasicFunctionality() 
	/// that calls this function.
	///
	/// This function requires static upcasting depending on which manager the
	/// GameEntity is being registered to.
	///  
	///  \param	toReg	A GameEntity to register to some Manager automatically
	void registerXables( GameEntity* toReg );

	/// \brief For Automatic Deregistration of X-Ables for GameEntities
	/// \ingroup NOTFORUSER
	/// 
	/// This function is the single place for developers to put deregistration from
	/// any X-Able manager to be done automatically.
	///
	/// GameEntity has a function called GameEntity::deregisterBasicFunctionality() 
	/// that calls this function.
	///  
	/// This function requires static upcasting depending on which manager the
	/// GameEntity is being deregistered from.
	///
	///  \param	toDereg	A GameEntity to deregister from some Manager automatically
	void deregisterXables( GameEntity* toDereg );

	void drawScene();
	void updateScene();
};

#endif SCENE_H