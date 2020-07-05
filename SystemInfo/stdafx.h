// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
#pragma warning(disable : 4995)
#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#ifndef UNICODE
#define UNICODE
#endif

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <wchar.h>
#include <string.h>
#include <Strsafe.h>
#include <queue>
#include <vector>
#include <iostream>

#include <VersionHelpers.h> //get Win OS Version
#include "intrin.h" // for CPU name
#include "winsock2.h" // for socket (IP) info 
#include "ws2tcpip.h"
#include "Lmwksta.h" //for computer domain name
#include <Msi.h> // for installed program
#include "psapi.h" // for Process ID

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

//ATL/WTL
#define _ATL_NO_MSIMG // Omits static linking of MSImg32.dll which is not fully supported in Windows NT
#include <atlbase.h>
#include <atlstr.h>
#include <atlapp.h>
#include <atlwin.h>
#include <atldlgs.h>
#include <atlscrl.h>
#include <atlctrls.h>
#include <atlctrlw.h>
#include <atlddx.h>