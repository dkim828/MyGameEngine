#ifndef TERMINATEABLEDUMPSTER_H
#define TERMINATEABLEDUMPSTER_H

#include <list>
#include "TerminateableReceiver.h"

class Terminateable;

class TerminateableDumpster : public TerminateableReceiver
{
public:
	TerminateableDumpster();
	~TerminateableDumpster();

	void registerTerminateable( Terminateable* t );
	void deregisterTerminateable( Terminateable* t );
	virtual void receiveTerminateable( Terminateable* t);

private:
	std::list< Terminateable* > terminateableList;
};



#endif TERMINATEABLEDUMPSTER_H