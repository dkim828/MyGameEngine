#ifndef COLLIDEABLEMANAGERBASE_H
#define COLLIDEABLEMANAGERBASE_H


class CollideableManagerBase
{
public:
	CollideableManagerBase(){};
	virtual ~CollideableManagerBase(){};

	virtual void updateGroupAABB(){};
};


#endif //COLLIDEABLEMANAGERBASE_H