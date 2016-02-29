#include "Terminateable.h"

#include "SceneManager.h"
#include "Scene.h"
#include "TerminateableManager.h"

#include "TerminateableDumpster.h"
#include "TerminateableReceiver.h"



#include "Tools\ErrorOut.h"

Terminateable::Terminateable()
{
	SceneManager::getCurrentScene()->getDumpster()->registerTerminateable( this );
	setObjectOwner( SceneManager::getCurrentScene()->getDumpster() ); 

	markedForTermination = false;
}


void Terminateable::markForTermination()
{
	if( markedForTermination == false )
	{
		markedForTermination = true;

		ErrorOut::debugOut("++++++++markForTermination Called ---- item now registered for next termination process");
		SceneManager::getCurrentScene()->getTerminateableMan()->registerForTermination( this );
	}
}

void Terminateable::sendToOwner()
{
	//setting markedForTermination in the case of recycling
	markedForTermination = false;

	terminateableOwner->receiveTerminateable( this );
}

void Terminateable::setObjectOwner( TerminateableReceiver* r )
{
	terminateableOwner = r;
	
	//If new owner is NOT the dumpster, Deregister from dumpster
	if( r != SceneManager::getCurrentScene()->getDumpster() )
	{
		SceneManager::getCurrentScene()->getDumpster()->deregisterTerminateable( this );
	}
}
