#ifndef INPUTGLOBALS_H
#define INPUTGLOBALS_H

/**
\ingroup INPUT

<summary> Each of these flags are associated with what kind of input the user may want
to register a key for through Inputable::registerKeyboardKey() or deregister through
Inputable::deregisterKeyboardKey() </summary>
*/
namespace InputFlags
{
	enum KeyFlag
	{
		KeyPressed ,
		KeyReleased	,
		KeyPressed_KeyReleased
	};
};
#endif INPUTGLOBALS_H