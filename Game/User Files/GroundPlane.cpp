#include "GroundPlane.h"

#include "../w14 Engine/Tools/Visualizer.h"
GroundPlane::GroundPlane( float scale )
{
	ErrorOut::debugOut("=============Constructor Called:: GroundPlane");
	setGraphicsObject( GraphicsObjectManager::makeGObj( AssetManager::getModel( "ground" ), AssetManager::getTexture( "t_ground" ) ) );

	Matrix world = Matrix(SCALE, scale,scale,scale);
	setGameEntityWorld( world );
}
GroundPlane::~GroundPlane()
{
	ErrorOut::debugOut("=============Destructor Called:: GroundPlane");
}
	

void GroundPlane::update()
{
	Visualizer::showPoint( Vect( 0,0,0 ), Colors::Red );

	Visualizer::showPoint( Vect( 10,0,10 ), Colors::Green );

	Visualizer::showPoint( Vect( 10,0,-10 ), Colors::Yellow );
	Visualizer::showPoint( Vect( -10,0,10 ), Colors::Blue );

	Visualizer::showPoint( Vect( -10,0,-10 ), Colors::Magenta );
	


	Visualizer::showPoint( Vect( 0,0,20 ), Colors::Green );
	Visualizer::showPoint( Vect( 0,0,-20 ), Colors::Red );

	Visualizer::showPoint( Vect( 20,0,0 ), Colors::Blue );
	Visualizer::showPoint( Vect( -20,0,0 ), Colors::Orange );


}
void GroundPlane::draw()
{
	renderGameEntity();
}