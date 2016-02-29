#ifndef TERMINATEABLEMANAGER_H
#define TERMINATEABLEMANAGER_H


#include <list>

class Terminateable;

class TerminateableManager
{
public:
	TerminateableManager(){};
	~TerminateableManager();

	void processTerminationEvents();
	
	void registerForTermination( Terminateable* t );


private:
	std::list<Terminateable*> terminationList;
};

#endif //TERMINATEABLEMANAGER_H