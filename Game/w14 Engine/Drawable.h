#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Azul.h"

class Drawable
{
public:
	Drawable(){ gObject = 0; };
	virtual ~Drawable() {};

	virtual void draw() {};
	
	
	//For Particles
	void registerDrawable();
	void deregisterDrawable();
protected:
	GraphicsObject* gObject;

};

#endif DRAWABLE_H