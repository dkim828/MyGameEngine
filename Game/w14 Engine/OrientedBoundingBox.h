#ifndef ORIENTEDBOUNDINGBOX_H
#define ORIENTEDBOUNDINGBOX_H

#include "BoundingBox.h"

class OrientedBoundingBox: public BoundingBox
{
friend class CollisionFunctions;

public:
	OrientedBoundingBox();
	OrientedBoundingBox( Model* CollisionStructure );
	virtual ~OrientedBoundingBox();

	OrientedBoundingBox( const AxisAlignedBoundingBox& ){};
	OrientedBoundingBox& operator= ( const AxisAlignedBoundingBox& ){};


	virtual void updateData( Matrix& inWorldTransform );

	//Visitor Pattern Double Dispatch
	virtual bool collideWith( CollisionVolume* other ); //Accept
	virtual bool testCollision( BoundingSphere* other ); //Visit
	virtual bool testCollision( AxisAlignedBoundingBox* other); //Visit
	virtual bool testCollision( OrientedBoundingBox* other); //Visit

	//DEBUG
	virtual void showCollisionArea();

private:
	//DEBUG Helper
	Matrix baseWorldTransform;
	Matrix debugTransform;
};


#endif //ORIENTEDBOUNDINGBOX_H