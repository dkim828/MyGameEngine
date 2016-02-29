#ifndef BULLETFACTORY_H
#define BULLETFACTORY_H

#include "..\w14 Engine\W14Common.h"

#include <stack>
#include <set>
#include <string>

class Bullet;
class Terminateable;

class BulletFactory : public TerminateableReceiver
{
private:
	static BulletFactory* bulletFactInstance; //the singleton

	BulletFactory() {};
	BulletFactory( const BulletFactory& ) {};
	~BulletFactory();

	static BulletFactory& instance()
	{
		if( !bulletFactInstance )
			bulletFactInstance = new BulletFactory();
		
		return *bulletFactInstance;
	};

	
	std::set<Bullet*> activeSet;
	std::stack<Bullet*> recycledStack;


	virtual void receiveTerminateable( Terminateable* t);

	void internalRecallBullets();
	
public:
	static void destroy();

	static void CreateBullet(const Vect& dir,const Vect& Pos, int shooterID );
	static void recallBullets();
};

#endif BULLETFACTORY_H