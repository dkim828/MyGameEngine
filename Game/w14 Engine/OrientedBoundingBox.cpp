#include "OrientedBoundingBox.h"


#include "Tools\MathTools.h"
#include "CollisionFunctions.h"

#include <cassert>

//FOR DEBUG OUTPUT
#include "AssetManager.h"
#include "Tools\Visualizer.h"

OrientedBoundingBox::OrientedBoundingBox()
{
	assert( 0 && "OrientedBoundingBox:: default constructor should not be called" );
}
OrientedBoundingBox::OrientedBoundingBox( Model* CollisionStructure ) : BoundingBox( CollisionStructure )
{
	//Pre-compute base world transform
	baseWorldTransform = Matrix( SCALE, baseBoxCorners[7] - baseBoxCorners[0] )
						* Matrix( TRANS, ( 0.5 * ( baseBoxCorners[7] + baseBoxCorners[0] ) ) );
	debugTransform = baseWorldTransform;


	//Setting debug collisionArea for Bounding Sphere
	debug_collisionArea = 0;

	debug_isCollided = false;
}
OrientedBoundingBox::~OrientedBoundingBox()
{
}


//==========================================================================================//
//UPDATE DATA																				//
//==========================================================================================//
void OrientedBoundingBox::updateData( Matrix& inWorldTransform )
{
	BoundingBox::updateData( inWorldTransform );
	
	debugTransform = baseWorldTransform * inWorldTransform;
}


//==========================================================================================//
//VISITOR - ACCEPT Function																	//
//==========================================================================================//
bool OrientedBoundingBox::collideWith( CollisionVolume* other )
{
	return other->testCollision( this );
}
//==========================================================================================//
//VISITOR - VISIT Functions																	//
//==========================================================================================//
bool OrientedBoundingBox::testCollision( BoundingSphere* other )
{
	this->debug_isCollided = CollisionFunctions::OBBtoSphere( this, other );
	other->debug_isCollided = this->debug_isCollided;

	return this->debug_isCollided;
}
bool OrientedBoundingBox::testCollision( AxisAlignedBoundingBox* other)
{
	this->debug_isCollided =  CollisionFunctions::BBtoBB( this, other );
	other->debug_isCollided = this->debug_isCollided;

	return this->debug_isCollided;
}
bool OrientedBoundingBox::testCollision( OrientedBoundingBox* other)
{
	this->debug_isCollided =  CollisionFunctions::BBtoBB( this, other );
	other->debug_isCollided = this->debug_isCollided;

	return this->debug_isCollided;
}


//==========================================================================================//
//DEBUG - ShowCollisionArea																	//
//==========================================================================================//
void OrientedBoundingBox::showCollisionArea()
{
	if( debug_isCollided )
	{
		Visualizer::showBox( debugTransform, 1, 0, 0 );
	}
	else
	{
		Visualizer::showBox( debugTransform, 0,0,1 );
	}
}