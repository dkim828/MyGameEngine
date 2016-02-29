#ifndef COLLISIONTYPE_H
#define COLLISIONTYPE_H

enum class CollisionType
{
	default_NONE	= -1,

	BoundingSphere  = 0,
	AABB			= 1,
	OBB				= 2
};

#endif //COLLISIONTYPE_H