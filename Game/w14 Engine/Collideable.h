#ifndef COLLIDEABLE_H
#define COLLIDEABLE_H


#include "CollideableManager.h"

#include "CollisionType.h"
#include <string>

class Model;
class CollisionVolume;
class BoundingSphere;
class AxisAlignedBoundingBox;

class Collideable
{
template<class C1, class C2> friend class CollisionPairProcessor;
template<class C3> friend class CollisionSingleProcessor;
template<class C3> friend class CollisionTerrainProcessor;
template<class C4> friend class CollideableManager;

friend class GameEntity;

public:
	Collideable();
	Collideable( const Collideable& ){};
	virtual ~Collideable();
	
	virtual void collided( Collideable* ){};
	virtual void collidedTerrain(){};

protected:	
	void showCollisionArea();

	void setCollisionType( CollisionType type );
	CollisionVolume* getCollisionVolume(){return colVolume;};


	/**
	\brief A function that is called to register a given GameEntity onto the Scene to be considered for collision testing.
	\ingroup COLLISION

	This function is protected in Collideable, so it is accessible by any GameEntity.

	The collision system holds a list of Collideable objects (which are really GameEntities in-game) to test collision for.
	Therefore, a GameEntity that wants to be considered for collision must register itself onto the Scene through the SceneManager.
	However, like the way the other X-able base class's registers are done, Collideable has a passthrough function that does all that
	within a protected template function.

	Within the template parameters, you put in the name of the Class that is calling the function because the function is registering
	collision for itself. A string Key is a required argument and it is the key for whatever model that the GameEntity uses. The
	registration then takes care of setting a collidingModel with that key which is used for collision calculation.

	\b Example: In the Demo, the Bullet is recycled so the Bullet has an initialize function that initializes everything for the
	Bullet to behave properly, one of the aspects being collision registration. The string being passed in is the string key for the
	primitive model UnitSphere that is automatically loaded in the AssetManager.
		\code
		void Bullet::initialize( const Vect& dir, const Vect& Pos, int owner  )
		{	
			position = Pos;
			heading = dir;
			heading *= bulletSpeed;


			Rotation.set(ROT_XYZ, 0,0,0);
			Scale.set(SCALE, 1.0f, 1.0f, 1.0f);
			Translation.set(TRANS, position);
			worldTransformMatrix = Scale * Rotation * Translation;
			(bulletGObj)->setWorld(worldTransformMatrix);

			ownerID = owner;
			life = 100;

			registerCollision< Bullet > (this, "UnitSphere" );	//function call HERE
		}
		\endcode
	\b Example: An example from ship to show a registration of Ship that does not use a primitive model.
		\code
		Ship::Ship(float x, float y, float z, int shipID, float yAngle )
		{	
			//Lots of other code

			shipGObj =  AssetManager::getGObj("shipModel"); //setting Ship's GraphicsObject
			registerCollision< Ship > (this, "shipModel" ); //function call HERE
		}
		\endcode

		\param	C		TEMPLATE PARAMETER: it is the Class that is calling this function
		\param toReg	a pointer to a class registering (almost always 'this')
		\param mKey		a string the is the key that is registered onto the AssetManager that represents the GameEntity's displayed GraphicsObject
	*/
	template< class C >
	void registerCollision( C* toReg )
	{
		CollideableManager<C>::registerCollideable( toReg );
	}
	
	/**
	\brief A function that is called to deregister a given GameEntity from the Scene when already registered for collision
	\ingroup COLLISION

	This function is protected in Collideable, so it is accessible by any GameEntity.

	The collision system holds a list of Collideable objects (which are really GameEntities in-game) to test collision for.
	W14's collision system is not smart enough to automatically detect Collideable's(GameEntities) that have either been
	deleted or is out of the Scenes scope; therefore, every GameEntity has to deregister collision if it has been registered
	sometime within its life.

	Within the template parameters, you put in the name of the Class that is calling the function because the function is deregistering
	collision for itself.

	\b Important: The deregistering cannot be done in the destructor because with the way the system process game and 
	GameEntity destruction, a deregistering call in the destructor causes a crash. Like with Inputable::deregisterKeyboardKey(),
	it is recommended to deregister within the GameEntity::terminationEvent() function.

	\b Example: This is an example of what the bullet does upon entering the destruction sequence of events after calling Terminateable::markForTermination()
		\code
		void Bullet::terminationEvent()
		{
			deregisterCollision<Bullet>(this);
		}
		\endcode
	
	\param	C		TEMPLATE PARAMETER: it is the Class that is calling this function
	\param toDereg	a pointer to a class deregistering (almost always 'this')
	*/
	template< class C >
	void deregisterCollision( C* toDereg )
	{
		CollideableManager<C>::deregisterCollideable( toDereg );
	}

	//LooseAABBstuff
	Vect& getLooseAABBMaxPt();
	Vect& getLooseAABBMinPt();

	BoundingSphere* getBoundingSphere(){return this->boundingSphere;};

	bool testAgainstCell( AxisAlignedBoundingBox* c );

private:
	Model* collidingModel;
	Matrix colWorldTransform;


	BoundingSphere*	boundingSphere;

	CollisionVolume*	colVolume;
	CollisionType		colType;

	void updateCollider();


	/**

	\brief THE function used for collision calculation
	\ingroup NOTFORUSER_COL
	
	This function is private inside Collideable meaning it should not ever be visible/usable for the user.
	However, it is also not called by any other Collidedable like the other private functions.

	This function is only called by the CollisionPairProcessor and CollisionSingleProcessor classes that 
	hold that actual list of Collideables that need to be tested. Therefore Collideable is friend classed
	with those two classes
	*/
	static bool testCollisionPair( Collideable* c1, Collideable* c2);
};


#endif //COLLIDEABLE_H