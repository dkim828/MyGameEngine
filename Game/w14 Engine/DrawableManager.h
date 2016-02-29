#ifndef DRAWABLEMANAGER_H
#define DRAWABLEMANAGER_H

#include <list>

class Drawable;

class DrawableManager
{
public:
	DrawableManager();
	DrawableManager( const DrawableManager& ) {};
	~DrawableManager();

	void registerDrawable( Drawable* toReg );
	void deregisterDrawable( Drawable* toDereg );

	void draw();

private:
	std::list<Drawable*> drawableList;

};

#endif DRAWABLEMANAGER_H