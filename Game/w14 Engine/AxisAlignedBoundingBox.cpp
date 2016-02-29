#include "AxisAlignedBoundingBox.h"

#include "BoundingSphere.h"

#include "GraphicsObjectManager.h"
#include "AssetManager.h"

#include "Tools\MathTools.h"
#include "CollisionFunctions.h"

#include "Tools\Visualizer.h"


AxisAlignedBoundingBox::AxisAlignedBoundingBox( Model* CollisionStructure ) : BoundingBox( CollisionStructure )
{
	//Getting the list of Vertexes from Collision Model;
	vertexList = collisionModel->getVectList();
	numVerts = collisionModel->numVerts;

	//Setting debug collisionArea for Bounding Sphere
	debug_collisionArea = 0;

	debug_isCollided = false;
}
void AxisAlignedBoundingBox::setMinMax( Vect& min, Vect& max )
{
	this->minValues = min;
	this->maxValues = max;
	
	//Fill corner array with all the corners in case of OBB collision checking
	transformedBoxCorners[ 0 ] = minValues;
	transformedBoxCorners[ 7 ] = maxValues;

	transformedBoxCorners[ 1 ].set( transformedBoxCorners[0][x], transformedBoxCorners[0][y], transformedBoxCorners[7][z] ); 
	transformedBoxCorners[ 2 ].set( transformedBoxCorners[0][x], transformedBoxCorners[7][y], transformedBoxCorners[0][z] ); 
	transformedBoxCorners[ 3 ].set( transformedBoxCorners[7][x], transformedBoxCorners[0][y], transformedBoxCorners[0][z] ); 

	transformedBoxCorners[ 4 ].set( transformedBoxCorners[0][x], transformedBoxCorners[7][y], transformedBoxCorners[7][z] ); 
	transformedBoxCorners[ 5 ].set( transformedBoxCorners[7][x], transformedBoxCorners[7][y], transformedBoxCorners[0][z] ); 
	transformedBoxCorners[ 6 ].set( transformedBoxCorners[7][x], transformedBoxCorners[0][y], transformedBoxCorners[7][z] ); 
}


AxisAlignedBoundingBox::~AxisAlignedBoundingBox()
{
}

//==========================================================================================//
//UPDATE DATA																				//
//==========================================================================================//
void AxisAlignedBoundingBox::updateData( Matrix& inWorldTransform )
{
	BoundingBox::updateData( inWorldTransform );

	//Starting Vertex check with 0th Vertex on VertexList of Model
	minValues = vertexList[0] * inWorldTransform;
	maxValues = minValues;

	Vect temp;

	//Getting minimum and maximum Vertex values
	for( int i = 1; i < numVerts; i++ )
	{
		temp = vertexList[i] * inWorldTransform;

		minValues = MathTools::getMinValuedVector( minValues, temp );
		maxValues = MathTools::getMaxValuedVector( maxValues, temp );
	}

	debugTransform = Matrix( SCALE, maxValues - minValues )
					* Matrix( TRANS, ( 0.5 * ( maxValues + minValues ) ) );
}


//==========================================================================================//
//VISITOR - ACCEPT Function																	//
//==========================================================================================//
bool AxisAlignedBoundingBox::collideWith( CollisionVolume* other )
{
	return other->testCollision( this );
}
//==========================================================================================//
//VISITOR - VISIT Functions																	//
//==========================================================================================//
bool AxisAlignedBoundingBox::testCollision( BoundingSphere* other )
{
	debug_isCollided = CollisionFunctions::AABBtoSphere( this, other );
	other->debug_isCollided = debug_isCollided;

	return debug_isCollided;
}
bool AxisAlignedBoundingBox::testCollision( OrientedBoundingBox* other )
{
	debug_isCollided = CollisionFunctions::BBtoBB( this, other );
	other->debug_isCollided = debug_isCollided;

	return debug_isCollided;
}
bool AxisAlignedBoundingBox::testCollision( AxisAlignedBoundingBox* other )
{	
	debug_isCollided = CollisionFunctions::AABBtoAABB( minValues, maxValues, other->minValues, other->maxValues );
	other->debug_isCollided = debug_isCollided;

	return debug_isCollided;
}




//==========================================================================================//
//DEBUG - ShowCollisionArea																	//
//==========================================================================================//

void AxisAlignedBoundingBox::showCollisionArea()
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