#ifndef ERROROUT_H
#define ERROROUT_H

#include <string>

class ErrorOut
{
private:
	ErrorOut();
	ErrorOut( const ErrorOut& ){};
	~ErrorOut();

	static ErrorOut* ErrorInstance;

	static ErrorOut& instance()
	{
		if( !ErrorInstance )
			ErrorInstance = new ErrorOut();

		return *ErrorInstance;
	};

public:

	static void debugOut( std::string errMsg );

	static void destroy();
};

#endif ERROROUT_H