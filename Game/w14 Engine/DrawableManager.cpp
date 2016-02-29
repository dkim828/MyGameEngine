#include "DrawableManager.h"
#include "Drawable.h"


#include "Tools/ErrorOut.h"



DrawableManager::DrawableManager()
{
}
DrawableManager::~DrawableManager()
{
	//clear drawable list
	//actual delete is on Terminable
	drawableList.clear();
}

void DrawableManager::draw()
{
	for( std::list< Drawable* >::iterator it = drawableList.begin();
		it != drawableList.end(); it++ )
	{
		(*it)->draw();
	}
}

void DrawableManager::registerDrawable( Drawable* toReg )
{
	for( std::list< Drawable* >::iterator it = drawableList.begin();
		it != drawableList.end(); it++ )
	{
		//Entity is already Registered
		if( (*it) == toReg )
		{
			ErrorOut::debugOut("Drawable Entity already Registered");
			return;
		}
	}
	//pushback entity to register
	drawableList.push_back( toReg );
}
void DrawableManager::deregisterDrawable( Drawable* toDereg )
{
	std::list< Drawable* >::iterator it;
	for( it = drawableList.begin();
		 it != drawableList.end() ; it++ )
	{
		//Entity is found
		if( (*it) == toDereg )
		{
			break;
		}
	}

	//Drawable Entity to Deregister was not found
	if( it == drawableList.end() )
	{
		ErrorOut::debugOut("Drawable Entity to DeRegister is not registered");
	}
	//Drawable Entity to Deregister was Found
	else
	{
		drawableList.erase(it);
		printf("Drawable deregistered\n\n");
	}
}