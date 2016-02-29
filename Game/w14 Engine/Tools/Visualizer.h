#ifndef VISUALIZER_H
#define VISUALIZER_H

#include "Azul.h"
#include <stack>


struct VisualizerData
{
	Matrix transform;
	Vect rgb;
};

namespace Colors
{
	static const Vect Black(0.0f, 0.0f,0.0f);
	static const Vect White(1.0f,1.0f,1.0f);

	static const Vect Red(1.0f, 0.0f, 0.0f);
	static const Vect Blue(0.0f, 0.0f, 1.0f);
	static const Vect Green(0.0f, 1.0f, 0.0f);

	static const Vect Yellow(1.0f,1.0f,0.0f);
	static const Vect Magenta(1.0f,0.0f,1.0f);
	static const Vect Cyan(0.0f,1.0f,1.0f);

	static const Vect Orange(1.0f, 0.5f, 0.0f);
	static const Vect Purple(0.3f, 0.5f, 0.5f);
};

class Visualizer
{
public:
	static void destroy();

	//Interface for using Visualizer
	static void showPoint( const Vect& pos, float colorR, float colorG, float colorB );
	static void showPoint( const Vect& pos, const Vect& color );

	static void showSphere( const Matrix& transform, float colorR, float colorG, float colorB );
	static void showSphere( const Matrix& transform,  const Vect& color );

	static void showBox( const Matrix& transform, float colorR, float colorG, float colorB );
	static void showBox( const Matrix& transform,  const Vect& color  );
	static void showBox( const Vect& minPt, const Vect& maxPt, float colorR, float colorG, float colorB  );
	static void showBox( const Vect& minPt, const Vect& maxPt,  const Vect& color   );

	static void drawAllVisuals();
private:
	GraphicsObjectWireFrame*	boxVisual;
	GraphicsObjectWireFrame*	sphereVisual;

	std::stack< VisualizerData > boxesToDraw;
	std::stack< VisualizerData > spheresToDraw;
	std::stack< VisualizerData > pointsToDraw;

	//internal functions
	void drawAll();


	//===========================================================================//
	//SINGLETON STUFF
	//===========================================================================//
	Visualizer();
	Visualizer( const Visualizer& ) {};
	Visualizer& operator=( const Visualizer& ) {};
	~Visualizer();
	
	static Visualizer* pInstance;

	static Visualizer* instance()
	{
		if( pInstance == 0 )
			pInstance = new Visualizer();

		return pInstance;
	}

};


#endif //VISUALIZER_H