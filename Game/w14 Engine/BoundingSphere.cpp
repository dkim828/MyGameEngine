#include "BoundingSphere.h"

#include "AxisAlignedBoundingBox.h"

#include "AssetManager.h"
#include "GraphicsObjectManager.h"

#include "CollisionFunctions.h"


#include "Tools\Visualizer.h"


BoundingSphere::BoundingSphere( Model* CollisionStructure )
{
	//Position uses default constructor to set to 0,0,0,0;
	radius = 0.0f;

	collisionModel = CollisionStructure;

	//HACK FOR PRIMITIVES
	if( collisionModel == AssetManager::getModel("UnitSphere") ||
		collisionModel == AssetManager::getModel("UnitPyramid") ||
		collisionModel == AssetManager::getModel("UnitBox") )
	{
		//Scale is hardcoded to 1s because azul primitives don't have proper "radius"
		collisionModelBase = Matrix( SCALE, 1, 1, 1)
							* Matrix( TRANS,  collisionModel->center );
	}
	else
	{
		collisionModelBase = Matrix( SCALE, collisionModel->radius, collisionModel->radius, collisionModel->radius)
						   * Matrix( TRANS,  collisionModel->center );
	}


	//Setting debug collisionArea for Bounding Sphere
	debug_collisionAreaBase = collisionModelBase;
	debug_collisionArea = 0;

	debug_isCollided = false;
}
BoundingSphere::~BoundingSphere()
{
}


//==========================================================================================//
//UPDATE DATA																				//
//==========================================================================================//
void BoundingSphere::updateData( Matrix& inWorldTransform )
{
	worldTransform = inWorldTransform;
	Matrix transformedCollider = collisionModelBase * worldTransform;

	position = Vect(0,0,0) * transformedCollider;
	radius = ( position - ( Vect(1,0,0) * transformedCollider ) ).mag();

	//Set loose AABB values
	this->looseAABBMinPt = position;
	this->looseAABBMinPt[x] -= radius;
	this->looseAABBMinPt[y] -= radius;
	this->looseAABBMinPt[z] -= radius;

	this->looseAABBMaxPt = position;
	this->looseAABBMaxPt[x] += radius;
	this->looseAABBMaxPt[y] += radius;
	this->looseAABBMaxPt[z] += radius;
}



//==========================================================================================//
//VISITOR - ACCEPT Function																	//
//==========================================================================================//
bool BoundingSphere::collideWith( CollisionVolume* other )
{
	return other->testCollision( this );
}
//==========================================================================================//
//VISITOR - VISIT Functions																	//
//==========================================================================================//
bool BoundingSphere::testCollision( BoundingSphere* other )
{
	debug_isCollided = ( ( position - other->position ).mag() <= radius + other->radius ); 
	other->debug_isCollided = debug_isCollided;
	return debug_isCollided;
}
bool BoundingSphere::testCollision( AxisAlignedBoundingBox* other )
{
	debug_isCollided = CollisionFunctions::AABBtoSphere( other, this );
	other->debug_isCollided = debug_isCollided;

	return debug_isCollided;
}
bool BoundingSphere::testCollision( OrientedBoundingBox* other ) 
{
	debug_isCollided = CollisionFunctions::OBBtoSphere( other, this );
	other->debug_isCollided = debug_isCollided;

	return debug_isCollided;
}


//==========================================================================================//
//DEBUG - ShowCollisionArea																	//
//==========================================================================================//
void BoundingSphere::showCollisionArea()
{
	if( debug_isCollided )
	{
		Visualizer::showSphere( debug_collisionAreaBase * worldTransform, 1, 0, 0 );
	}
	else
	{
		Visualizer::showSphere( debug_collisionAreaBase * worldTransform, 0,0,1 );
	}

}