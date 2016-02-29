#include "TerminateableDumpster.h"

#include "Terminateable.h"

#include "Tools/ErrorOut.h"
TerminateableDumpster::TerminateableDumpster()
{
}
TerminateableDumpster::~TerminateableDumpster()
{
	ErrorOut::debugOut("Dumping Dumpster- dumpster destructor Called*^*^*^*^*^*^*^*^**^*^*^*^");

	for( std::list< Terminateable* >::iterator it = terminateableList.begin();
		it != terminateableList.end(); it++ )
	{
		delete (*it);
	}

	terminateableList.clear();
}

void TerminateableDumpster::registerTerminateable( Terminateable* t )
{
	for( std::list< Terminateable* >::iterator it = terminateableList.begin();
		it != terminateableList.end(); it++ )
	{
		//Entity is already Registered
		if( (*it) == t )
		{
			printf("Terminateable Entity already Registered to Dumpster");
			return;
		}
	}
	//pushback entity to register
	terminateableList.push_back( t );
}
void TerminateableDumpster::deregisterTerminateable( Terminateable* t )
{
	for( std::list< Terminateable* >::iterator it = terminateableList.begin();
		it != terminateableList.end(); it++ )
	{
		if( (*it) == t )
		{
			terminateableList.erase( it );

			return;
		}
	}
}


void TerminateableDumpster::receiveTerminateable( Terminateable* t )    
{
	for( std::list< Terminateable* >::iterator it = terminateableList.begin();
		it != terminateableList.end(); it++ )
	{
		if( (*it) == t )
		{
			delete (*it);

			terminateableList.erase( it );

			return;
		}
	}
}