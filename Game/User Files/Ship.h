#ifndef SHIP_H
#define SHIP_H

#include "../w14 Engine/W14Common.h"

class Bullet;
class Cottage;
class P_EmitterHandle;

class Ship : public GameEntity
{
public:
	Ship( float x, float y, float z, 
		  float xAn, float yAn, float zAn, int shipID );
	~Ship();

	//FROM Terminateable
	virtual void terminationEvent();
	
	//FROM Collideable
	virtual void collided( Collideable* other );
	virtual void collided( Ship* other );
	virtual void collided( Cottage* other );
	virtual void collidedTerrain();

	void Ship::collided( Bullet* other);

	//FROM Inputable
	virtual void keyPressed( AZUL_KEY k, bool Ctrl, bool Shift, bool Alt );
	virtual void keyReleased(  AZUL_KEY k, bool Ctrl, bool Shift, bool Alt );
	
	//FROM Updateable
	virtual void update();

	//FROM Drawable
	virtual void draw();

	//FROM Alarmable
	virtual void alarm0();
	virtual void alarm1();
	virtual void alarm2();

	int getID(){return id;};
	
private:
	Vect position;
	Vect impulse;
	Matrix rotationImpulse;

	float rotSpeed;
	float moveSpeed;

	int id;
	void shootBullet();
};


#endif