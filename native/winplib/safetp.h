#pragma once
#include "stdafx.h"

BOOL SafeTerminateProcess(DWORD dwProcessId, HANDLE hProcess, UINT uExitCode, DWORD dwTerminateWaitMs);
