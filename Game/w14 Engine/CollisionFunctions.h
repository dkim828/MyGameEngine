#ifndef COLLISIONFUNCTIONS_H
#define COLLISIONFUNCTIONS_H

#include "AxisAlignedBoundingBox.h"
#include "OrientedBoundingBox.h"
#include "BoundingBox.h"
#include "BoundingSphere.h"

#include "Tools\MathTools.h"
#include "Tools\Visualizer.h"

class CollisionFunctions
{
public:

	static bool AABBtoSphere( AxisAlignedBoundingBox* aabb, BoundingSphere* sphere )
	{
		Vect sphereCenter = sphere->getCenter();
	
		//clamping center of sphere to AABB
		MathTools::clampVect( sphereCenter, aabb->minValues, aabb->maxValues );

		return (sphere->getCenter() - sphereCenter ).mag() < sphere->getRadius();
	}
	static bool AABBtoSphere( Vect& minValues, Vect& maxValues, BoundingSphere* sphere )
	{
		Vect sphereCenter = sphere->getCenter();
	
		//clamping center of sphere to AABB
		MathTools::clampVect( sphereCenter, minValues, maxValues );

		return (sphere->getCenter() - sphereCenter ).mag() < sphere->getRadius();
	}

	static bool OBBtoSphere( OrientedBoundingBox* obb, BoundingSphere* sphere )
	{
		Vect clampedCenter = sphere->getCenter() * obb->worldTransform.getInv();
	
		MathTools::clampVect( clampedCenter, obb->baseBoxCorners[0], obb->baseBoxCorners[7] );

		clampedCenter = clampedCenter * obb->worldTransform;

		return (sphere->getCenter() - clampedCenter ).mag() < sphere->getRadius();
	}

	static bool AABBtoAABB( Vect& oneMin, Vect& oneMax,
							Vect& twoMin, Vect& twoMax )
	{
		return MathTools::doIntervalsOverlap( oneMin[x], oneMax[x], twoMin[x], twoMax[x] ) &&
			   MathTools::doIntervalsOverlap( oneMin[y], oneMax[y], twoMin[y], twoMax[y] ) &&
			   MathTools::doIntervalsOverlap( oneMin[z], oneMax[z], twoMin[z], twoMax[z] );
	}

	static bool BBtoBB( BoundingBox* one, BoundingBox* other )
	{
		return  doSATonAxis( one, other, one->getXNormal() ) &&
				doSATonAxis( one, other, one->getYNormal() ) &&
				doSATonAxis( one, other, one->getZNormal() ) &&
				doSATonAxis( one, other, other->getXNormal() ) &&
				doSATonAxis( one, other, other->getYNormal() ) &&
				doSATonAxis( one, other, other->getZNormal() ) &&
				doSATonAxis( one, other, one->getXNormal().cross( other->getXNormal() ) ) &&
				doSATonAxis( one, other, one->getXNormal().cross( other->getYNormal() ) ) &&
				doSATonAxis( one, other, one->getXNormal().cross( other->getZNormal() ) ) &&
				doSATonAxis( one, other, one->getYNormal().cross( other->getXNormal() ) ) &&
				doSATonAxis( one, other, one->getYNormal().cross( other->getYNormal() ) ) &&
				doSATonAxis( one, other, one->getYNormal().cross( other->getZNormal() ) ) &&
				doSATonAxis( one, other, one->getZNormal().cross( other->getXNormal() ) ) &&
				doSATonAxis( one, other, one->getZNormal().cross( other->getYNormal() ) ) &&
				doSATonAxis( one, other, one->getZNormal().cross( other->getZNormal() ) );
	}


	static bool doSATonAxis( BoundingBox* one, BoundingBox* two, const Vect& axis )
	{
		float oneTest = axis.dot( one->transformedBoxCorners[0] );
		float oneMin = oneTest;
		float oneMax = oneTest;
		
		float twoTest = axis.dot( two->transformedBoxCorners[0] );
		float twoMin = twoTest;
		float twoMax = twoTest;

		for( int i = 1; i < OrientedBoundingBox::BOX_CORNERS; i++ )
		{
			oneTest = axis.dot( one->transformedBoxCorners[i] );

			if( oneTest < oneMin )
				oneMin = oneTest;
			else if( oneTest > oneMax )
				oneMax = oneTest;

			
			twoTest = axis.dot( two->transformedBoxCorners[i] );

			if( twoTest < twoMin )
				twoMin = twoTest;
			else if( twoTest > twoMax )
				twoMax = twoTest;
		}

		return MathTools::doIntervalsOverlap( oneMin, oneMax, twoMin, twoMax );
	}



};

#endif