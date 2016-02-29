#include "Drawable.h"

#include "SceneManager.h"
#include "Scene.h"
#include "DrawableManager.h"

void Drawable::registerDrawable()
{
	SceneManager::getCurrentScene()->getDrawableMan()->registerDrawable( this );
}

void Drawable::deregisterDrawable()
{
	SceneManager::getCurrentScene()->getDrawableMan()->deregisterDrawable( this );
}