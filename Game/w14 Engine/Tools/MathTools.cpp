#include "../TimeManager.h"
#include "MathTools.h"

MathTools::MathTools()
{
	srand( (unsigned int )TimeManager::getTotalTime() );
}