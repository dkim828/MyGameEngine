#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H


#include "CollideableManager.h"
#include "CollisionProcessorBase.h"
#include "CollisionSingleProcessor.h"
#include "CollisionPairProcessor.h"
#include "CollisionTerrainProcessor.h"

#include <set>
#include <list>

class CollisionManager
{
public:
	CollisionManager();
	CollisionManager( const CollisionManager& ){};
	~CollisionManager();

	void processCollisions();

	//TEMPLATE FUNCTIONS==============================================================================//
	template <class C1, class C2>
	void setCollisionPair()
	{
		CollideableManagerBase* ptrColMan1 = &CollideableManager< C1 >::instance();
		CollideableManagerBase* ptrColMan2 = &CollideableManager< C2 >::instance();

		collideableManList.insert( ptrColMan1 );
		collideableManList.insert( ptrColMan2 );
		processorList.push_back( new CollisionPairProcessor< C1, C2 >() );

		processorList.size();
	}
	template <class C>
	void setCollisionSelf()
	{
		CollideableManagerBase* ptrColMan1 = &CollideableManager< C >::instance();

		collideableManList.insert( ptrColMan1 );
		processorList.push_back( new CollisionSingleProcessor< C >() );
	}

	template <class C>
	void setCollisionWithTerrain()
	{
		CollideableManagerBase* ptrColMan1 = &CollideableManager< C >::instance();

		//This part would be conflicting if I was not using std::set
		collideableManList.insert( ptrColMan1 );

		processorList.push_back( new CollisionTerrainProcessor< C >( ) );
	}
	//END TEMPLATE FUNCTIONS==========================================================================//

private:
	//TYPEDEF
	typedef std::set< CollideableManagerBase* > CollideableManStash;
	typedef std::list< CollisionProcessorBase* > ProcessorStash;
	//END TYPEDEF


	CollideableManStash collideableManList;
	ProcessorStash processorList;
};


#endif COLLISIONMANAGER_H