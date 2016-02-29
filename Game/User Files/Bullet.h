#ifndef BULLET_H
#define BULLET_H

#include "..\w14 Engine\W14Common.h"

class Ship;

class Bullet : public GameEntity
{
public:
	Bullet(  );
	Bullet( const Bullet& ){};
	~Bullet();
	
	//Initialize function made for recycling purposes
	void initialize( const Vect& dir, const Vect& Pos, int owner );

		//FROM Terminateable
	virtual void terminationEvent();
	
	//FROM Collideable
	virtual void collided( Collideable* other );
	virtual void collided( Ship* other );
	virtual void collidedTerrain();
	
	//FROM Updateable
	virtual void update() override;

	//FROM Drawable
	virtual void draw() override;

	int getOwnerID(){ return ownerID; };

private:
	Vect position;
	Vect heading;

	Matrix Scale;
	Matrix Rotation;
	Matrix Translation;

	float bulletSpeed;

	int life;
	int ownerID;
};


#endif