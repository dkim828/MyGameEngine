#ifndef GROUNDPLANE_H
#define GROUNDPLANE_H

#include "..\w14 Engine\W14Common.h"


class GroundPlane : public GameEntity
{
public:
	GroundPlane( float scale );
	GroundPlane( const GroundPlane& ){};
	~GroundPlane();
	
	//FROM Collideable
	virtual void collided( Collideable* ) {};
	
	//FROM Updateable
	virtual void update() override;

	//FROM Drawable
	virtual void draw() override;
	
private:
};

#endif //GROUNDPLANE_H