#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
}
CollisionManager::~CollisionManager()
{
	for( CollideableManStash::iterator it = collideableManList.begin();
		it != collideableManList.end(); it++ )
	{
		delete (*it);
	}
	
	for( ProcessorStash::iterator it = processorList.begin();
		it != processorList.end(); it++ )
	{
		delete (*it);
	}
}

void CollisionManager::processCollisions()
{
	for( CollideableManStash::iterator it = collideableManList.begin();
		it != collideableManList.end(); it++ )
	{
		(*it)->updateGroupAABB();
	}
	
	for( ProcessorStash::iterator it = processorList.begin();
		it != processorList.end(); it++ )
	{
		(*it)->CollisionTest();
	}
}