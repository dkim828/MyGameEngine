#include "Bullet.h"
#include "Ship.h"


#include "../w14 Engine/ParticleEffectManager.h"

Bullet::Bullet( )
{
	bulletSpeed = 4.0f;
	setGraphicsObjectAndCollision( GraphicsObjectManager::makeGObj_NoTexture( AssetManager::getModel("UnitSphere"), Colors::Cyan ), CollisionType::BoundingSphere );
}

void Bullet::initialize( const Vect& dir, const Vect& Pos, int owner  )
{	
	position = Pos;
	heading = dir;
	heading *= bulletSpeed;


  	Rotation.set(ROT_XYZ, 0,0,0);
	Scale.set(SCALE, 1.0f, 1.0f, 1.0f);
	Translation.set(TRANS, position);
	Matrix tempWorld = Scale * Rotation * Translation;

	ownerID = owner;
	life = 50;

	registerCollision< Bullet > (this);	
	setGameEntityWorld( tempWorld );
}


Bullet::~Bullet()
{
	ErrorOut::debugOut( "=============Destructor Called:: Bullet" );
}

void Bullet::terminationEvent()
{
	ErrorOut::debugOut("======Termination Event Called:: Bullet");

	deregisterCollision<Bullet>(this);
}

void Bullet::collided( Collideable*  )
{
	markForTermination();
}
void Bullet::collided( Ship* other  )
{
	if( other->getID() != ownerID )
	{
		printf("Bullet Collided with EnemyShip\n");
		markForTermination();
	}
}
void Bullet::collidedTerrain()
{
	markForTermination();
}

void Bullet::update()
{
	if( life <= 0 )
		markForTermination();

	life--;

	position += heading;

	Translation.set(TRANS, position);
	Matrix temp = Scale * Rotation * Translation;
 	setGameEntityWorld( temp );
}
void Bullet::draw()
{
	renderGameEntity();

	//showCollisionArea();
}