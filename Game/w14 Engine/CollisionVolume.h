#ifndef COLLISIONVOLUME_H
#define COLLISIONVOLUME_H

#include "Azul.h"

#include "GraphicsObjectManager.h"

class BoundingSphere;
class AxisAlignedBoundingBox;
class OrientedBoundingBox;
class BoundingBox;

class CollisionVolume
{
public:
	CollisionVolume(){};
	virtual ~CollisionVolume()
	{
		if( debug_collisionArea != 0 )
		{
			GraphicsObjectManager::removeGraphicsObject( debug_collisionArea );
		}
	}
	CollisionVolume( const CollisionVolume& ){};
	CollisionVolume& operator= ( const CollisionVolume& ){};


	virtual void updateData( Matrix& ) = 0;

	//Visitor Pattern Double Dispatch
	virtual bool collideWith( CollisionVolume* ) = 0; //Accept
	virtual bool testCollision( BoundingSphere* ) = 0; //Visit
	virtual bool testCollision( AxisAlignedBoundingBox* ) = 0;//Visit
	virtual bool testCollision( OrientedBoundingBox* ) = 0; //Visit
	

	//Debug Stuff
	virtual void showCollisionArea() = 0;
	bool						debug_isCollided;

protected:
	GraphicsObjectWireFrame*	debug_collisionArea;
	Matrix						debug_collisionAreaBase;

	//CollisionVolume holds collision model pointer, but does not OWN them
	//Collideable owns the model
	Model* collisionModel;

	Matrix		 worldTransform;
};


#endif //COLLISIONVOLUME_H