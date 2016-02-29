#ifndef PARTICLE_H
#define PARTICLE_H

#include "ParticleHeader.h"

class Particle
{
public:
	Particle(){};
	~Particle(){};

	Vect pos;
	Vect vel;
	Vect acc;
};


#endif