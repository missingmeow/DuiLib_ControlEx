#pragma once

#define WIN32_LEAN_AND_MEAN	
#define _CRT_SECURE_NO_DEPRECATE

#include <windows.h>
#include <objbase.h>

#include "..\DuiLib\UIlib.h"
#include "..\DuiLib\Utils\WinImplBase.h"

using namespace DuiLib;

#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, "..\\lib\\DuiLib_ud.lib")
#   else
#       pragma comment(lib, "..\\lib\\DuiLib_d.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, "..\\lib\\DuiLib_u.lib")
#   else
#       pragma comment(lib, "..\\lib\\DuiLib.lib")
#   endif
#endif
