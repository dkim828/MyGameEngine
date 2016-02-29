#include "Ship.h"

#include "Bullet.h"
#include "BulletFactory.h"
#include "../w14 Engine/Tools/TestGlobals.h"

#include "../w14 Engine/Tools/ErrorOut.h"

#include "../w14 Engine/ParticleEffectManager.h"

Ship::Ship(float x, float y, float z, 
		   float xAn, float yAn, float zAn, int shipID )
{	
	ErrorOut::debugOut("=============Constructor Called:: Ship");
	position.set(x, y, z );
	impulse.set(0,0,0);
	rotationImpulse.set(ROT_XYZ, 0,0,0);

	Scale.set(SCALE,0.25f,0.25f,0.25f);
	Rotation.set(ROT_XYZ, xAn,yAn,zAn);
	Translation.set(TRANS, position);

	rotSpeed = 0.05f;
	moveSpeed = 1.5f;
	
	id = shipID;

	setGraphicsObjectAndCollision( GraphicsObjectManager::makeGObj( AssetManager::getModel("ship"), AssetManager::getTexture("t_ship") ), CollisionType::AABB );
	registerCollision< Ship >( this );
	
	Matrix temp = Scale * Rotation * Translation;
	setGameEntityWorld( temp );


	registerKeyboardKey( AZUL_KEY::KEY_W, InputFlags::KeyPressed_KeyReleased );
	registerKeyboardKey( AZUL_KEY::KEY_A, InputFlags::KeyPressed_KeyReleased );
	registerKeyboardKey( AZUL_KEY::KEY_S, InputFlags::KeyPressed_KeyReleased );
	registerKeyboardKey( AZUL_KEY::KEY_D, InputFlags::KeyPressed_KeyReleased );

	registerKeyboardKey( AZUL_KEY::KEY_Z, InputFlags::KeyPressed );
	registerKeyboardKey( AZUL_KEY::KEY_X, InputFlags::KeyPressed );
	registerKeyboardKey( AZUL_KEY::KEY_C, InputFlags::KeyPressed );
	registerKeyboardKey( AZUL_KEY::KEY_V, InputFlags::KeyPressed );

	registerKeyboardKey( AZUL_KEY::KEY_SPACE, InputFlags::KeyPressed );

	
	registerKeyboardKey( AZUL_KEY::KEY_B, InputFlags::KeyPressed );
	registerKeyboardKey( AZUL_KEY::KEY_N, InputFlags::KeyPressed );
	registerKeyboardKey( AZUL_KEY::KEY_M, InputFlags::KeyPressed );

	camID = CameraManager::makeFollowCam( 45, 100, 80, 25, this );
}
Ship::~Ship()
{
	ErrorOut::debugOut("=============Destructor Called:: Ship");
}

void Ship::terminationEvent()
{
	ErrorOut::debugOut("======Termination Event Called:: Ship");
	
	deregisterCollision< Ship >( this );

	deregisterKeyboardKey( AZUL_KEY::KEY_W, InputFlags::KeyPressed_KeyReleased );
	deregisterKeyboardKey( AZUL_KEY::KEY_A, InputFlags::KeyPressed_KeyReleased );
	deregisterKeyboardKey( AZUL_KEY::KEY_S, InputFlags::KeyPressed_KeyReleased );
	deregisterKeyboardKey( AZUL_KEY::KEY_D, InputFlags::KeyPressed_KeyReleased );

	deregisterKeyboardKey( AZUL_KEY::KEY_Z, InputFlags::KeyPressed );
	deregisterKeyboardKey( AZUL_KEY::KEY_X, InputFlags::KeyPressed );
	deregisterKeyboardKey( AZUL_KEY::KEY_C, InputFlags::KeyPressed );
	deregisterKeyboardKey( AZUL_KEY::KEY_V, InputFlags::KeyPressed );

	deregisterKeyboardKey( AZUL_KEY::KEY_SPACE, InputFlags::KeyPressed );

	deregisterKeyboardKey( AZUL_KEY::KEY_B, InputFlags::KeyPressed );
	deregisterKeyboardKey( AZUL_KEY::KEY_N, InputFlags::KeyPressed );
	deregisterKeyboardKey( AZUL_KEY::KEY_M, InputFlags::KeyPressed );

	deregisterKeyboardKey( AZUL_KEY::KEY_HOME, InputFlags::KeyPressed );

	cancelAllAlarms();
	
	CameraManager::deleteCam( camID );
}

void Ship::collided( Collideable* )
{
}
void Ship::collided( Ship* )
{
	printf("\nShip Colliding with Ship\n");
}
void Ship::collided( Bullet* other)
{
	if( other->getOwnerID() != id)
		printf("\nShip hit by Bullet\n");
}
void Ship::collided( Cottage*  )
{
	printf("\nShip Colliding with Cottage\n");
}
void Ship::collidedTerrain()
{
	printf("\nShip Colliding with Terrain\n");
}

void Ship::keyPressed( AZUL_KEY k, bool , bool , bool  )
{
	//Ship Movement
	if( k == AZUL_KEY::KEY_W )
	{
		impulse = Vect(0,0,1)  * moveSpeed;
	}
	if( k == AZUL_KEY::KEY_S )
	{
		impulse = Vect(0,0,1)  * -moveSpeed;	
	}

	if( k == AZUL_KEY::KEY_A )
	{
		rotationImpulse = Matrix( ROT_Y, rotSpeed );
	}
	if( k == AZUL_KEY::KEY_D )
	{
		rotationImpulse = Matrix( ROT_Y, -rotSpeed );
	}

	if( k == AZUL_KEY::KEY_SPACE)
	{
		shootBullet();
		
		Vect heading(0,0,1);
		heading *= Rotation;
		heading.norm();
	}

	//Alarm Inputs
	if( k == AZUL_KEY::KEY_Z )
	{
	  ParticleEffectManager::SpawnEffect( "Confetti", this->position, Vect(0,0,1) * Rotation );
	}
	if( k == AZUL_KEY::KEY_X )
	{
	  ParticleEffectManager::SpawnEffect( "WaterSpout", this->position, Vect(0,0,1) * Rotation );
	}
	if( k == AZUL_KEY::KEY_C )
	{
	  ParticleEffectManager::SpawnEffect( "Round1000", this->position, Vect(0,0,1) * Rotation );
	}
	if( k == AZUL_KEY::KEY_V )
	{
	  ParticleEffectManager::SpawnEffect( "ExplosionTwo", this->position, Vect(0,0,1) * Rotation );
	}

	if( k == AZUL_KEY::KEY_B )
	{
		setCollisionType( CollisionType::BoundingSphere );
	}
	if( k == AZUL_KEY::KEY_N )
	{
		setCollisionType( CollisionType::AABB );
	}
	if( k == AZUL_KEY::KEY_M )
	{
		setCollisionType( CollisionType::OBB );
	}	

}
void Ship::keyReleased(  AZUL_KEY k, bool , bool , bool  )
{	
	if( k == AZUL_KEY::KEY_W || k == AZUL_KEY::KEY_S )
	{
		impulse.set(0,0,0);
	}
	if( k == AZUL_KEY::KEY_A  || k == AZUL_KEY::KEY_D)
	{
		rotationImpulse.set(ROT_Y, 0);
	}
}
void Ship::shootBullet()
{
	Vect heading(0,0,1);
	heading *= Rotation;
	heading.norm();

	Vect shootPos = position - Vect(0, 1.8f,0);

	BulletFactory::CreateBullet( heading, shootPos, id );
}

void Ship::update()
{
	Rotation *= rotationImpulse;
	position += ( impulse * Rotation );	

	Translation.set(TRANS, position);
	/*

	effect1Rot.set( Vect(0,0,-1) * Rotation );
	effect1Pos.set( this->position + ( Vect(0,-1.0f,-7.0f) * this->Rotation ) );
	effectHandle1->setPos( effect1Pos);
	effectHandle1->setRot( effect1Rot.getNorm() );

	wingLRot.set( Vect(0,0,-1) * Rotation );
	wingLPos.set( this->position + ( Vect( -7.75f, -1.0f, -6.75f ) * this->Rotation ) );
	wingTrailL->setPos( wingLPos );
	wingTrailL->setRot( wingLRot );
	
	wingRRot.set( Vect(0,0,-1) * Rotation );
	wingRPos.set( this->position + ( Vect( 7.75f, -1.0f, -6.75f ) * this->Rotation ) );
	wingTrailR->setPos( wingRPos );
	wingTrailR->setRot( wingRRot );
	
	*/


	Matrix temp = Scale * Rotation * Translation;
	setGameEntityWorld( temp );
}

void Ship::draw()
{
	renderGameEntity();
	showCollisionArea();
}

void Ship::alarm0()
{
	 printf("ALARM_0 from Ship\n"); 
}
void Ship::alarm1()
{
	 printf("ALARM_1 from Ship\n"); 
}
void Ship::alarm2()
{
	 printf("ALARM_2 from Ship\n"); 
}