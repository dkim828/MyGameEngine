
#ifndef CELL_H
#define CELL_H

#include "Azul.h"

class Cell
{
public:
	Cell(): topLeft(0), topRight(0), botLeft(0), botRight(0) {};
	~Cell(){};
	
	/**
		Returns Max altitude+topLeftmost Vector
		RETURNS A REFERENCE
	*/
	Vect& getMax() { return this->max; };
	
	/**
		Returns Max altitude+topLeftmost Vector
		RETURNS A REFERENCE
	*/
	Vect& getMin() { return this->min; };


	int& getTopLeft(){ return this->topLeft; };
	int& getTopRight(){ return this->topRight; };
	int& getBotLeft(){ return this->botLeft; };
	int& getBotRight(){ return this->botRight; };
private:
	Vect min;
	Vect max;

	//Indices to box corners on VertList
	int topLeft;
	int topRight;
	int botLeft;
	int botRight;
};


#endif