#ifndef COLLISIONPAIRPROCESSOR_H
#define COLLISIONPAIRPROCESSOR_H

#include "CollisionProcessorBase.h"
#include "CollideableManager.h"

template <class C1, class C2>
class CollisionPairProcessor : public CollisionProcessorBase
{
public:
	CollisionPairProcessor< C1, C2 >()
	{
		testOne = &CollideableManager<C1>::instance();
		testTwo = &CollideableManager<C2>::instance();
	};
	CollisionPairProcessor< C1, C2  >( const CollisionPairProcessor<C1, C2 >& ) {};
	~CollisionPairProcessor< C1, C2  >() {};

	virtual void CollisionTest()
	{
		if( testOne->collideableList.empty() ||
			testTwo->collideableList.empty() )
			return;

		bool result;
		
		//Test Group vs Group
		if( testOne->testCollisionGroups( testTwo ) )
		{
			printf("Groups Colliding\n");
		
			for( CollideableManager<C1>::CollideableStash::iterator it = testOne->collideableList.begin();
				 it != testOne->collideableList.end(); it++ )
			{
				for( CollideableManager<C2>::CollideableStash::iterator it_other = testTwo->collideableList.begin();
					 it_other != testTwo->collideableList.end(); it_other++)
				{
					result = Collideable::testCollisionPair( *it, *it_other );

					if (result)
					{
						(*it)->collided(*it_other);
						(*it_other)->collided(*it);
					}
				}
			}
		}	
	};

private:
	CollideableManager<C1>* testOne;
	CollideableManager<C2>* testTwo;

};


#endif COLLISIONPAIRPROCESSOR_H