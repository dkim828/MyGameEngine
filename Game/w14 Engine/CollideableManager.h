#ifndef COLLIDEABLEMANAGER_H
#define COLLIDEABLEMANAGER_H

#include "Azul.h"
#include "CollideableManagerBase.h"
#include "Collideable.h"

#include "Tools\MathTools.h"
#include "CollisionFunctions.h"

#include <set>
#include "Tools\Visualizer.h"


struct GroupAABB
{
	void clear()
	{
		this->minValues.set(0,0,0);
		this->maxValues.set(0,0,0);
	}
	Vect minValues;
	Vect maxValues;
};

template <class C> 
class CollideableManager : public CollideableManagerBase
{
friend class CollisionManager;

template<class C1, class C2> friend class CollisionPairProcessor;
template<class C3> friend class CollisionSingleProcessor;
template<class C> friend class CollisionTerrainProcessor;

public:
	static void registerCollideable( C* toReg )
	{
		instance().collideableList.insert( toReg );
	}
	static void deregisterCollideable( C* toDereg )
	{
		instance().collideableList.erase( toDereg );
	}
	
	virtual void updateGroupAABB()
	{
		if( !instance().collideableList.empty() )
		{
			//Get First collideable within the group to start calculations on AABB
			auto it = instance().collideableList.begin();
			if( it != instance().collideableList.end() )
			{
				instance().groupAABB->minValues = (*it)->getLooseAABBMinPt();
				instance().groupAABB->maxValues = (*it)->getLooseAABBMaxPt();
				++it;
			}

		
			//Iterate through the rest whilst keeping track of minnest min and maxest max
			Vect min;
			Vect max;
			while( it != instance().collideableList.end() )
			{
				min =  (*it)->getLooseAABBMinPt();
				max =  (*it)->getLooseAABBMaxPt() ;

				instance().groupAABB->minValues = MathTools::getMinValuedVector( min, instance().groupAABB->minValues );
				instance().groupAABB->maxValues = MathTools::getMaxValuedVector( max, instance().groupAABB->maxValues );
			
				++it;
			}

			//DEBUG
			Visualizer::showBox( instance().groupAABB->minValues, instance().groupAABB->maxValues, Colors::Red );
		}
	}
	

	template <class D>
	bool testCollisionGroups( CollideableManager<D>* other )
	{											  
		return CollisionFunctions::AABBtoAABB( this->groupAABB->minValues, this->groupAABB->maxValues,
											  other->groupAABB->minValues,other->groupAABB->maxValues);
	}

	//Public so that different templated CollideableManagers can see each other's GroupAABB data
	GroupAABB* groupAABB;
private:
	//TYPEDEFS 
	typedef std::set< C* > CollideableStash;
	//END TYPEDEFS
	
	//MEMBERS
	CollideableStash collideableList;



	//Constructors/Destructor
	CollideableManager<C>() 
	{
		groupAABB = new GroupAABB;
	};
	CollideableManager<C>( const CollideableManager<C>& ) {};
	virtual ~CollideableManager<C>() 
	{ 
		collideableList.clear();
		delete groupAABB;

		colManInstance = 0; 
	};

	//Singleton Instance
	static CollideableManager<C>* colManInstance;
	//Singleton Access
	static CollideableManager<C>& instance()
	{
		if( !colManInstance )
			colManInstance = new CollideableManager<C>();

		return *colManInstance;
	}
};

//instantiating static variable
template <class C> 
CollideableManager<C>* CollideableManager<C>::colManInstance = NULL;

#endif //COLLIDEABLEMANAGER_H