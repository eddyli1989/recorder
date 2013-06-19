#include"Processcontroller.h"
#include<TlHelp32.h>

BOOL ProcessController::FindProcess(TCHAR * szExeFile) {
    if (szExeFile == NULL && iLength <= 0)
	return FALSE;
    
    HANDLE procSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(procSnap == INVALID_HANDLE_VALUE) {
	return False;
    } 

    PROCESSENTRY32 procEntry = { 0 };
    procEntry.dwSize = sizeof(PROCESSENTRY32);
    BOOL bRet = Process32First(procSnap, &procEntry);
    while(bRet) {
	printf(L"PID: %d (%s) ", procEntry.th32ProcessID, procEntry.szExeFile);
	if (strcmp(szExeFile, procEntry.szExeFile) == 0) {
	    printf("found!\n");
	    return True;
	}
	bRet = Process32Next(procSnap, &procEntry);
    }
    CloseHandle(procSnap);
    return False;
}
