#ifndef UPDATEABLE_H
#define UPDATEABLE_H

class Updateable
{
public:
	Updateable(){};
	virtual ~Updateable() {};

	virtual void update(){};
};

#endif UPDATEABLE_H