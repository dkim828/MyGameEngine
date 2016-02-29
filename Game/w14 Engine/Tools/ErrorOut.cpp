#include "ErrorOut.h"
#include <Windows.h>

ErrorOut* ErrorOut::ErrorInstance = NULL;


ErrorOut::ErrorOut()
{
}
ErrorOut::~ErrorOut()
{
	ErrorInstance = 0;
}

void ErrorOut::debugOut( std::string errMsg )
{
	errMsg+= '\n';
	LPCSTR wsPtr = errMsg.c_str();
	OutputDebugString(wsPtr);
}

void ErrorOut::destroy()
{
	if( ErrorInstance != 0 )
		delete ErrorInstance;
}