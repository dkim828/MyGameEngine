#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "CollisionVolume.h"

class BoundingBox : public CollisionVolume
{
	friend class CollisionFunctions;

public:
	BoundingBox()
	{
	};
	BoundingBox( Model* CollisionStructure )
	{
		collisionModel = CollisionStructure;

		//Fill corner array with all the corners of base model
		baseBoxCorners[ 0 ] = collisionModel->minPointAABB; 
		baseBoxCorners[ 7 ] = collisionModel->maxPointAABB; 

		baseBoxCorners[ 1 ] = Vect( baseBoxCorners[0][x], baseBoxCorners[0][y], baseBoxCorners[7][z] ); 
		baseBoxCorners[ 2 ] = Vect( baseBoxCorners[0][x], baseBoxCorners[7][y], baseBoxCorners[0][z] ); 
		baseBoxCorners[ 3 ] = Vect( baseBoxCorners[7][x], baseBoxCorners[0][y], baseBoxCorners[0][z] ); 

		baseBoxCorners[ 4 ] = Vect( baseBoxCorners[0][x], baseBoxCorners[7][y], baseBoxCorners[7][z] ); 
		baseBoxCorners[ 5 ] = Vect( baseBoxCorners[7][x], baseBoxCorners[7][y], baseBoxCorners[0][z] ); 
		baseBoxCorners[ 6 ] = Vect( baseBoxCorners[7][x], baseBoxCorners[0][y], baseBoxCorners[7][z] ); 
	}
	virtual ~BoundingBox()
	{
	}
	BoundingBox( const CollisionVolume& ){};
	BoundingBox& operator= ( const CollisionVolume& ){};


	virtual void updateData( Matrix& inWorldTransform )
	{
		for( int i = 0; i < BOX_CORNERS; i++ )
		{
			transformedBoxCorners[i] = baseBoxCorners[i] * inWorldTransform;
		}

		worldTransform = inWorldTransform;
	};
	

	Vect getXNormal()
	{
		Vect normX = Vect( 1, 0, 0, 0 ) * worldTransform;
		return normX;
	}
	Vect getYNormal()
	{
		Vect normY = Vect( 0, 1, 0, 0 ) * worldTransform;
		return normY;
	}
	Vect getZNormal()
	{
		Vect normZ = Vect( 0, 0, 1, 0 ) * worldTransform;
		return normZ;
	}


	//Visitor Pattern Double Dispatch
	virtual bool collideWith( CollisionVolume* ) = 0; //Accept
	virtual bool testCollision( BoundingSphere* ) = 0; //Visit
	virtual bool testCollision( AxisAlignedBoundingBox* ) = 0; //Visit
	virtual bool testCollision( OrientedBoundingBox* ) = 0; //Visit
	

	//Debug Stuff
	virtual void showCollisionArea() = 0;
	bool						debug_isCollided;

protected:
	static const int BOX_CORNERS = 8;

	/*
	* baseBoxCorners[0] is min
	* baseBoxCorners[7] is max
	**/
	Vect baseBoxCorners[ BOX_CORNERS ]; 	
	/*
	* transformedBoxCorners[0] is min
	* transformedBoxCorners[7] is max
	**/
	Vect transformedBoxCorners[ BOX_CORNERS ]; 

};


#endif //BOUNDINGBOX_H 