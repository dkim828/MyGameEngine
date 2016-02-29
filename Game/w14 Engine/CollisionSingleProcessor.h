#ifndef COLLISIONSINGLEPROCESSOR_H
#define COLLISIONSINGLEPROCESSOR_H

#include "CollisionProcessorBase.h"
#include "CollideableManager.h"

template <class C> 
class CollisionSingleProcessor : public CollisionProcessorBase
{
public:
	CollisionSingleProcessor< C >()
	{
		testOne = &CollideableManager<C>::instance();
	};
	CollisionSingleProcessor< C >( const CollisionSingleProcessor<C>& ) {};
	~CollisionSingleProcessor< C >() {};

	virtual void CollisionTest()
	{
		bool result;

		for( CollideableManager<C>::CollideableStash::iterator it = testOne->collideableList.begin();
			 it != testOne->collideableList.end(); it++ )
		{
			for( CollideableManager<C>::CollideableStash::iterator it_other = next( it );
			     it_other != testOne->collideableList.end(); it_other++ )
			{
				result = Collideable::testCollisionPair( *it, *it_other );

				if (result)
				{
					(*it)->collided(*it_other);
					(*it_other)->collided(*it);
				}
			}
		}
	};

private:
	CollideableManager<C>* testOne;
};


#endif