// taken from http://www.alexfedotov.com/articles/killproc.asp
//

#include "stdafx.h"
#include "winp.h"
#include "java-interface.h"
#include "winplib\auto_handle.h"
#include "winplib\killproc.h"

JNIEXPORT jboolean JNICALL Java_org_jvnet_winp_Native_isCriticalProcess(JNIEnv* pEnv, jclass clazz, jint dwProcessId) {
	// first try to obtain handle to the process without the use of any
	// additional privileges
	auto_handle hProcess = OpenProcess(PROCESS_TERMINATE|PROCESS_QUERY_INFORMATION, FALSE, dwProcessId);
	if (!hProcess)
		return FALSE;

	// make sure this is not a critical process
	ULONG isCritical = 0;
	ZwQueryInformationProcess(hProcess, ProcessBreakOnTermination, &isCritical, sizeof(isCritical), NULL);

	return isCritical!=0;
}