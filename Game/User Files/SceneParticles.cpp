#include "SceneParticles.h"

#include "Ship.h"
#include "Cottage.h"

#include "Bullet.h"
#include "BulletFactory.h"

void SceneParticles::initScene()
{
	new Ship(0, 25, -30, 0,0,0,0);

	new Cottage( 40, 15, 100, 0,0,0, false, CollisionType::AABB);
	new Cottage( 0, 15, 130, 0,0,0, false, CollisionType::OBB);
	new Cottage( -40, 15, 100, 0,0,0, false, CollisionType::BoundingSphere);

	setCollisionPair< Cottage, Ship >();
	setCollisionPair< Cottage, Bullet >();

	CameraManager::useCam( CameraManager::makeStaticCam(45,  Vect(0, 15, 130), Vect( 200, 150, -150), false ) );
}

void SceneParticles::endScene()
{
	BulletFactory::recallBullets();
}
