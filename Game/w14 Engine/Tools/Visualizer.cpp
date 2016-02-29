#include "Visualizer.h"
#include "../AssetManager.h"
#include "../GraphicsObjectManager.h"

Visualizer* Visualizer::pInstance = 0;

Visualizer::Visualizer()
{
	this->boxVisual = GraphicsObjectManager::makeGObj_WireFrame( AssetManager::getModel("UnitBox") );
	this->sphereVisual = GraphicsObjectManager::makeGObj_WireFrame( AssetManager::getModel("UnitSphere") );

}
Visualizer::~Visualizer()
{
	pInstance = 0;
}
void Visualizer::destroy()
{
	if( pInstance != 0 )
		delete pInstance;
}


void Visualizer::showPoint( const Vect& pos, float colorR, float colorG, float colorB )
{
	VisualizerData data;
	data.rgb[x] = colorR;
	data.rgb[y] = colorG;
	data.rgb[z] = colorB;

	data.transform = Matrix(SCALE,0.5f,0.5f,0.5f) * Matrix(TRANS, pos );

	instance()->pointsToDraw.push( data );
}
void Visualizer::showPoint( const Vect& pos, const Vect& color )
{
	VisualizerData data;
	data.rgb = color;

	data.transform = Matrix(SCALE,0.5f,0.5f,0.5f) * Matrix(TRANS, pos );

	instance()->pointsToDraw.push( data );
}

void Visualizer::showSphere( const Matrix& transform, float colorR, float colorG, float colorB )
{
	VisualizerData data;
	data.rgb[x] = colorR;
	data.rgb[y] = colorG;
	data.rgb[z] = colorB;

	data.transform = transform;

	instance()->spheresToDraw.push( data );
}
void Visualizer::showSphere( const Matrix& transform, const Vect& color )
{
	VisualizerData data;
	data.rgb = color;

	data.transform = transform;

	instance()->spheresToDraw.push( data );
}

void Visualizer::showBox( const Matrix& transform, float colorR, float colorG, float colorB )
{
	VisualizerData data;
	data.rgb[x] = colorR;
	data.rgb[y] = colorG;
	data.rgb[z] = colorB;

	data.transform = transform;

	instance()->boxesToDraw.push( data );
}
void Visualizer::showBox( const Matrix& transform, const Vect& color )
{
	VisualizerData data;
	data.rgb = color;

	data.transform = transform;

	instance()->boxesToDraw.push( data );
}
void Visualizer::showBox(const Vect& minPt, const Vect&  maxPt, float colorR, float colorG, float colorB )
{
	VisualizerData data;
	data.rgb[x] = colorR;
	data.rgb[y] = colorG;
	data.rgb[z] = colorB;

	data.transform = Matrix( SCALE, maxPt - minPt )
					* Matrix( TRANS, ( 0.5 * ( maxPt + minPt ) ) );

	instance()->boxesToDraw.push( data );
}
void Visualizer::showBox(const Vect& minPt, const Vect&  maxPt, const Vect& color )
{
	VisualizerData data;
	data.rgb = color;

	data.transform = Matrix( SCALE, maxPt - minPt )
					* Matrix( TRANS, ( 0.5 * ( maxPt + minPt ) ) );

	instance()->boxesToDraw.push( data );
}


void Visualizer::drawAllVisuals()
{
	instance()->drawAll();
}
void Visualizer::drawAll()
{
	//Render all
	while( !this->pointsToDraw.empty() )
	{
		this->sphereVisual->color.set( this->pointsToDraw.top().rgb );
		this->sphereVisual->setWorld( this->pointsToDraw.top().transform );

		this->sphereVisual->Render();

		this->pointsToDraw.pop();
	}

	while( !this->spheresToDraw.empty() )
	{
		this->sphereVisual->color.set( this->spheresToDraw.top().rgb );
		this->sphereVisual->setWorld( this->spheresToDraw.top().transform );

		this->sphereVisual->Render();

		this->spheresToDraw.pop();
	}

	while( !this->boxesToDraw.empty() )
	{
		this->boxVisual->color.set( this->boxesToDraw.top().rgb );
		this->boxVisual->setWorld( this->boxesToDraw.top().transform );

		this->boxVisual->Render();

		this->boxesToDraw.pop();
	}
}