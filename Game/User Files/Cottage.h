#ifndef COTTAGE_H
#define COTTAGE_H

#include "../w14 Engine/W14Common.h"

class Ship;
class Bullet;

class Cottage : public GameEntity
{
public:
	Cottage(float x, float y, float z, float xAn, float yAn, float zAn, bool controlled, CollisionType type);
	Cottage( const Cottage&  ){};
	~Cottage();

	//FROM Terminateable
	virtual void terminationEvent();
	
	//FROM Collideable
	virtual void collided( Collideable* other );
	virtual void collided( Ship* other );
	virtual void collided( Bullet* other );

	//FROM Drawable
	virtual void draw();
private:
	Matrix Scale;
	Matrix Rotation;
	Matrix Translation;

	float angularRot;
	Vect	position;
};

#endif