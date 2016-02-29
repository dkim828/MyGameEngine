#ifndef UPDATEABLEMANAGER_H
#define UPDATEABLEMANAGER_H


#include <list>


class Updateable;

class UpdateableManager
{
public:
	UpdateableManager();
	UpdateableManager( const UpdateableManager& ){};
	~UpdateableManager();

	void update();

	void registerUpdateable( Updateable* toReg );
	void deregisterUpdateable( Updateable* toDereg );

private:
	std::list<Updateable*> updateableList;
};


#endif UPDATEABLEMANAGER_H