#ifndef COLLISIONTERRAINPROCESSOR_H
#define COLLISIONTERRAINPROCESSOR_H

#include "CollisionProcessorBase.h"
#include "CollideableManager.h"

#include "TerrainObject.h"
#include "Tools\TerrainTools.h"
#include "CollisionFunctions.h"

#include "AxisAlignedBoundingBox.h"

#include "SceneManager.h"
#include "Scene.h"
#include "TerrainManager.h"


template <class C> 
class CollisionTerrainProcessor : public CollisionProcessorBase
{
public:
	CollisionTerrainProcessor< C >( )
	{
		collideableGroup = &CollideableManager<C>::instance();

		this->currentTerrain = SceneManager::getCurrentScene()->getTerrainMan()->getCurrentTerrain();
	}
	CollisionTerrainProcessor< C >( const CollisionTerrainProcessor<C>& ) {};
	~CollisionTerrainProcessor< C >() {};

	virtual void CollisionTest()
	{
		Vect collideableMaxPt;
		Vect collideableMinPt;
		AxisAlignedBoundingBox cellAABB;

		for( auto it = collideableGroup->collideableList.begin();
			 it != collideableGroup->collideableList.end(); ++it )
		{
			collideableMinPt = (*it)->getLooseAABBMinPt();
			collideableMaxPt = (*it)->getLooseAABBMaxPt();
			
			TerrainObject::CellIterator cellIt;
			TerrainObject::CellIterator cellItEnd;
			this->currentTerrain->getTerrainSegmentIterator( collideableMaxPt, collideableMinPt, cellIt, cellItEnd );	
			
			while( cellIt != cellItEnd )
			{
				//Test against big AABB
				if( CollisionFunctions::AABBtoAABB( (*cellIt)->getMin(), (*cellIt)->getMax(),
													collideableMinPt, collideableMaxPt ) )
				{
					//Test against sphere
					if( CollisionFunctions::AABBtoSphere( (*cellIt)->getMin(), (*cellIt)->getMax(), (*it)->getBoundingSphere() ) )
					{
						//At this point make pseudo AABB collision Volume for Collideable to do visitor with
						cellAABB.setMinMax( (*cellIt)->getMin(), (*cellIt)->getMax() );

						//Test against collisionVolume
						if( (*it)->testAgainstCell( &cellAABB ) )
						{
							(*it)->collidedTerrain();
							Visualizer::showBox( (*cellIt)->getMin(), (*cellIt)->getMax(), Colors::Magenta );
						}
						else
							Visualizer::showBox( (*cellIt)->getMin(), (*cellIt)->getMax(), Colors::Blue );
					}
					else
						Visualizer::showBox( (*cellIt)->getMin(), (*cellIt)->getMax(), Colors::Cyan );
				}
				else
					Visualizer::showBox( (*cellIt)->getMin(), (*cellIt)->getMax(), Colors::Green );
				
				++cellIt;
			}
		}
	}

private:
	CollideableManager<C>* collideableGroup;
	TerrainObject* currentTerrain;
};


#endif