// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <Windows.h>
#include <tchar.h>
#include <tlhelp32.h>
#include <psapi.h>
#pragma comment(lib, "psapi.lib")
// if you don't have ntdll.lib, download Windows DDK
// 32bit version should be from lib/wxp/i386 (Windows XP)
// 64bit version should be from lib/wnet/amd64 (Windows 2003 Server)
#pragma comment(lib, "ntdll.lib")

#define _ASSERTE(x)		;