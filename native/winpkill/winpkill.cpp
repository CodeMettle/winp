// winpkill.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include "../winplib/killproc.h"

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 3)
	{
		_tprintf(L"Usage: %s <pid> <graceful stop timeout in ms>", argv[0]);
		return 1;
	}

	_TCHAR *parseStop;
	unsigned long pid = _tcstoul(argv[1], &parseStop, 10);
	
	if (*parseStop != 0)
	{
		_tprintf(L"Invalid pid: %s", argv[1]);
		return 1;
	}

	unsigned long timeout = _tcstoul(argv[2], &parseStop, 10);

	if (*parseStop != 0)
	{
		_tprintf(L"Invalid timeout: %s", argv[2]);
		return 1;
	}

	if (KillProcessEx(pid, FALSE, timeout))
		return 0;
	else
		return 1;
}

