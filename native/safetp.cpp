#include "stdafx.h"
#include "safetp.h"

BOOL CALLBACK TerminateAppEnum(HWND hwnd, LPARAM lParam)
{
	DWORD dwID;

	GetWindowThreadProcessId(hwnd, &dwID);

	if (dwID == (DWORD)lParam)
	{
		PostMessage(hwnd, WM_CLOSE, 0, 0);
	}

	return TRUE;
}

BOOL HardKill(HANDLE hProcess, UINT uExitCode)
{
	return TerminateProcess(hProcess, uExitCode);
}

BOOL WaitOrHardKill(HANDLE hProcess, UINT uExitCode, DWORD dwTerminateWaitMs)
{
	if (WaitForSingleObject(hProcess, dwTerminateWaitMs) == WAIT_OBJECT_0)
		return TRUE;
	else
		return HardKill(hProcess, uExitCode);
}

BOOL SafeTerminateProcess(DWORD dwProcessId, HANDLE hProcess, UINT uExitCode, DWORD dwTerminateWaitMs)
{
	BOOL bRet;

	FreeConsole();

	if (!AttachConsole(dwProcessId))
	{
		if (GetLastError() == ERROR_INVALID_HANDLE) // no console, prolly has windows, so search for windows to send WM_CLOSE to
		{
			// TerminateAppEnum() posts WM_CLOSE to all windows whose PID
			// matches your process's.
			EnumWindows((WNDENUMPROC)TerminateAppEnum, (LPARAM)dwProcessId);

			bRet = WaitOrHardKill(hProcess, uExitCode, dwTerminateWaitMs);
		}
		else
		{
			bRet = FALSE;
		}
	}
	else
	{
		SetConsoleCtrlHandler(NULL, TRUE);
		GenerateConsoleCtrlEvent(CTRL_C_EVENT, 0);

		bRet = WaitOrHardKill(hProcess, uExitCode, dwTerminateWaitMs);

		FreeConsole();

		SetConsoleCtrlHandler(NULL, FALSE);
	}

	return bRet;
}
