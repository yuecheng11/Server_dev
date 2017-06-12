// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the XSOCKET_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// XSOCKET_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef XSOCKET_EXPORTS
#define XSOCKET_API __declspec(dllexport)
#else
#define XSOCKET_API __declspec(dllimport)
#endif

// This class is exported from the xsocket.dll
class XSOCKET_API Cxsocket {
public:
	Cxsocket(void);
	// TODO: add your methods here.
};

extern XSOCKET_API int nxsocket;

XSOCKET_API int fnxsocket(void);
