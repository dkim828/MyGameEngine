#include "BulletFactory.h"
#include "Bullet.h"

BulletFactory* BulletFactory::bulletFactInstance = NULL;

BulletFactory::~BulletFactory()
{
	while( !recycledStack.empty() )
	{
		delete recycledStack.top();
		recycledStack.pop();
	}	
	
	for( std::set< Bullet* >::iterator it = activeSet.begin();
		 it != activeSet.end(); it++ )
	{
		delete (*it);
	}
	activeSet.clear();

	bulletFactInstance = 0;
}

void BulletFactory::destroy()
{
	if( bulletFactInstance )
		delete bulletFactInstance;
}


void BulletFactory::CreateBullet(const Vect& dir,const Vect& Pos, int shooterID )
{
	Bullet* b;
	if( instance().recycledStack.empty() )
	{
		b = new Bullet( );
		b->setObjectOwner( &instance() );
	}
	else
	{
		b = instance().recycledStack.top();
		instance().recycledStack.pop();
		b->registerBasicFunctionality();
	}

	instance().activeSet.insert( b );
	b->initialize( dir, Pos, shooterID );
} 


void  BulletFactory::receiveTerminateable( Terminateable* t )
{
	activeSet.erase( (Bullet*) t );
	recycledStack.push( (Bullet*) t );

}


void BulletFactory::recallBullets()
{
	instance().internalRecallBullets();
}
void BulletFactory::internalRecallBullets()
{
	Bullet* b;

	for( std::set< Bullet* >::iterator it = activeSet.begin();
		it != activeSet.end(); it++ )
	{
		b = (*it);
		b->markForTermination();
	}
}

