#ifndef BOUNDINGSPHERE_H
#define BOUNDINGSPHERE_H

#include "CollisionVolume.h"

class AxisAlignedBoundingBox;

class BoundingSphere : public CollisionVolume
{
friend class CollisionFunctions;

public:
	BoundingSphere() {};
	BoundingSphere( Model* CollisionStructure );
	virtual ~BoundingSphere();

	BoundingSphere( const BoundingSphere& ){};
	BoundingSphere& operator= ( const BoundingSphere& ){};

	
	virtual void updateData( Matrix& inWorldTransform );

	//Visitor Pattern Double Dispatch
	virtual bool collideWith( CollisionVolume* other); //Accept
	virtual bool testCollision( BoundingSphere* other ); //Visit
	virtual bool testCollision( AxisAlignedBoundingBox* other ); //Visit
	virtual bool testCollision( OrientedBoundingBox* other ); //Visit


	//Accessors for Non-BoundingSphere colliders
	Vect getCenter(){ return position; };
	float getRadius(){ return radius; };

	//LooseAABB stuff
	Vect& getLooseAABBMaxPt(){ return this->looseAABBMaxPt; };
	Vect& getLooseAABBMinPt(){ return this->looseAABBMinPt; };

	//DEBUG
	virtual void showCollisionArea();

private:
	Vect position;
	float radius;

	Matrix		 collisionModelBase;
	Vect	looseAABBMaxPt;
	Vect	looseAABBMinPt;
};


#endif //BOUNDINGSPHERE_H