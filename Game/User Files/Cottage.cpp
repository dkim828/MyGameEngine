#include "Cottage.h"

#include "SceneTerrain.h"

Cottage::Cottage(float x, float y, float z, float xAn, float yAn, float zAn, bool , CollisionType type )
{
	ErrorOut::debugOut("=============Constructor Called:: Cottage");
	Scale.set(SCALE,1.5f,1.5f,1.5f);
//	Rotation.set(ROT_XYZ, 0,0,0);
//	Translation.set(TRANS, 30.0f, 15.0f, 60.0f);
	Rotation.set(ROT_XYZ, xAn,yAn,zAn);
	position.set( x, y, z);
	Translation.set(TRANS, position);
	angularRot = 0.00f;
	
	

	setGraphicsObjectAndCollision( GraphicsObjectManager::makeGObj_DefaultTextures( AssetManager::getModel( "cottage" ) ), type );
	registerCollision< Cottage > ( this );

	Matrix temp = Scale * Rotation * Translation;
	setGameEntityWorld( temp );
}
Cottage::~Cottage()
{
	ErrorOut::debugOut("=============Destructor Called:: Cottage");
}

void Cottage::terminationEvent()
{	
	ErrorOut::debugOut("======Termination Event Called:: Cottage");
	deregisterCollision< Cottage >( this );
	

	ParticleEffectManager::SpawnEffect( "ExplosionOne", this->position, Vect(0,1,0) );
	ParticleEffectManager::SpawnEffect( "ExplosionTwo", this->position, Vect(0,1,0) );
}
	
void Cottage::collided( Collideable* )
{
}
void Cottage::collided( Ship* )
{
	SceneManager::setNextScene( new SceneTerrain );
}
void Cottage::collided( Bullet* )
{
	markForTermination();
}

void Cottage::draw()
{
	angularRot+= 0.05f;

	Rotation.set( ROT_XYZ, 0, angularRot, angularRot );
	Matrix temp = Scale * Rotation * Translation;
	setGameEntityWorld( temp );

	renderGameEntity();
	showCollisionArea();
}