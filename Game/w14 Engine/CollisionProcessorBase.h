#ifndef COLLISIONPROCESSOR_H
#define COLLISIONPROCESSOR_H


class CollisionProcessorBase
{
public:
	CollisionProcessorBase(){};
	virtual ~CollisionProcessorBase(){};

	virtual void CollisionTest() = 0;
private:
};

#endif