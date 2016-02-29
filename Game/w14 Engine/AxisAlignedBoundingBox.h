#ifndef AXISALIGNEDBOUNDINGBOX_H
#define AXISALIGNEDBOUNDINGBOX_H


#include "BoundingBox.h"

class BoundingSphere;

class AxisAlignedBoundingBox : public BoundingBox
{
friend class CollisionFunctions;

public:
	AxisAlignedBoundingBox() {};
	AxisAlignedBoundingBox( Model* CollisionStructure );

	//For Terrain
	void setMinMax( Vect& min, Vect& max );

	virtual ~AxisAlignedBoundingBox();

	AxisAlignedBoundingBox( const AxisAlignedBoundingBox& ){};
	AxisAlignedBoundingBox& operator= ( const AxisAlignedBoundingBox& ){};


	virtual void updateData( Matrix& inWorldTransform );

	//Visitor Pattern Double Dispatch
	virtual bool collideWith( CollisionVolume* other); //Accept
	virtual bool testCollision( BoundingSphere* other ); //Visit
	virtual bool testCollision( AxisAlignedBoundingBox* other ); //Visit
	virtual bool testCollision( OrientedBoundingBox* other ); //Visit

	//DEBUG
	virtual void showCollisionArea();

private:
	Vect*	vertexList;
	int		numVerts;

	Vect minValues;
	Vect maxValues;
	//DEBUG
	Matrix debugTransform;
};




#endif