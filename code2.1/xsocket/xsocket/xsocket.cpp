// xsocket.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "xsocket.h"


// This is an example of an exported variable
XSOCKET_API int nxsocket=0;

// This is an example of an exported function.
XSOCKET_API int fnxsocket(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see xsocket.h for the class definition
Cxsocket::Cxsocket()
{
	return;
}
