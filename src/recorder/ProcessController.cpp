#include"Processcontroller.h"
#include<tchar.h>
#include"../log.h"

BOOL ProcessController::FindProcess(const TCHAR * szExeFile, PROCESSENTRY32 *entry) {
    if (szExeFile == NULL)
        return FALSE;
    //log_info(_T("[FindProcess]start find process:%s"), szExeFile);
    HANDLE procSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(procSnap == INVALID_HANDLE_VALUE) {
      return FALSE;
    }

    PROCESSENTRY32 procEntry = { 0 };
    procEntry.dwSize = sizeof(PROCESSENTRY32);
    BOOL bRet = Process32First(procSnap, &procEntry);
    while(bRet) {
        //log_info(_T("[FindProcess]PID: %d (%s)"), procEntry.th32ProcessID, procEntry.szExeFile);
        if (_tcscmp(szExeFile, procEntry.szExeFile) == 0) {
	  log_info(_T("[FindProcess]process:%s has been found"),szExeFile);
	  memcpy(entry, &procEntry, sizeof(procEntry));
          return TRUE;
       }
      bRet = Process32Next(procSnap, &procEntry);
    }
    CloseHandle(procSnap);
    //log_info(_T("[FindProcess]process has not been found"));
    return FALSE;
}

BOOL ProcessController::FindProcessInList(vector<string> &list,	PROCESSENTRY32 *entry) {
    vector<string>::iterator it = list.begin();
    for(; it != list.end(); it++) {
	if (this->FindProcess(it->c_str(), entry)) {
		return TRUE;
	}
    }
    return FALSE;
}

BOOL ProcessController::StartProcess(TCHAR * szFilePath, SHELLEXECUTEINFO* info) {
     SHELLEXECUTEINFO ShellInfo;        
     memset(&ShellInfo, 0, sizeof(ShellInfo));
     ShellInfo.cbSize = sizeof(ShellInfo);
     ShellInfo.hwnd = NULL;
     ShellInfo.lpVerb = _T("open");
     ShellInfo.lpFile = szFilePath;
     ShellInfo.nShow = SW_SHOWNORMAL;
     ShellInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
     BOOL bResult = ShellExecuteEx(&ShellInfo);
     memcpy(info, &ShellInfo, sizeof(ShellInfo));
     return bResult;
}
