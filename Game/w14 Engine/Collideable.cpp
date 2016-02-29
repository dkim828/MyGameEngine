#include "Collideable.h"
#include "AssetManager.h"

#include "BoundingSphere.h"
#include "AxisAlignedBoundingBox.h"
#include "OrientedBoundingBox.h"

#include <cassert>

Collideable::Collideable()
{
	collidingModel = 0;
	colVolume = 0;
	colType = CollisionType::default_NONE;

	boundingSphere = 0;

	colWorldTransform = Matrix();
}
Collideable::~Collideable()
{
	delete boundingSphere;

	if( this->colType != CollisionType::BoundingSphere )
		delete colVolume;
}

void Collideable::showCollisionArea()
{ 
	colVolume->showCollisionArea(); 
}

Vect& Collideable::getLooseAABBMaxPt(){ return this->boundingSphere->getLooseAABBMaxPt(); };
Vect& Collideable::getLooseAABBMinPt(){ return this->boundingSphere->getLooseAABBMinPt(); };

void Collideable::setCollisionType( CollisionType type )
{
	if( colType != type )
	{
		//if ColVolume had not been set before
		if( colVolume == 0 )
			boundingSphere = new BoundingSphere( collidingModel );
		//if colVolume had been set
		else
		{
			if( colType != CollisionType::BoundingSphere  )
				delete colVolume;
		}

	
		switch( type )
		{
		case CollisionType::BoundingSphere:
			colType = CollisionType::BoundingSphere;
			colVolume = boundingSphere;
			break;
		case CollisionType::AABB:
			colType = CollisionType::AABB;
			colVolume = new AxisAlignedBoundingBox( collidingModel );
			break;
		case CollisionType::OBB:
			colType = CollisionType::OBB;
			colVolume = new OrientedBoundingBox( collidingModel );
			break;
		default:
			assert( 0 && "CollisionType set to unknown Type" );
		}
	}
}

void Collideable::updateCollider()
{
	boundingSphere->updateData( colWorldTransform );

	if( this->colType != CollisionType::BoundingSphere )
		colVolume->updateData( colWorldTransform );
}

bool Collideable::testCollisionPair( Collideable* c1, Collideable* c2)
{
	return c1->getCollisionVolume()->collideWith( c2->getCollisionVolume() );
}

bool Collideable::testAgainstCell( AxisAlignedBoundingBox* c )
{
	return c->collideWith( this->getCollisionVolume() );
}