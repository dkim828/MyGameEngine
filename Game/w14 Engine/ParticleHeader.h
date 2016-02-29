#ifndef PARTICLEHEADER_H
#define PARTICLEHEADER_H

#include "Azul.h"

#include <assert.h>

//Tools
#include "Tools\MathTools.h"
#include "Tools\ErrorOut.h"


enum class P_BurstType
{
	ROUND				= 2,

	SPRAY				= 4,


	_IGNORE_FORCESIZE = 0x7FFFFFFF
};

enum class P_BoundaryType
{
	MIN_TO_MAX		= 0,

	RANDOM			= 1,


	NONE	= 900,


	_IGNORE_FORCESIZE = 0x7FFFFFFF
};


#endif