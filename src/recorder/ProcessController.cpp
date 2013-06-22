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

DWORD ProcessController::GetSpecifiedProcessId(const char *pszProcessName)
{
	DWORD id;

	//获得系统快照句柄 (通俗的讲, 就是得到当前的所有进程) 
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0) ; 
	PROCESSENTRY32 pInfo; //用于保存进程信息的一个数据结构 
	pInfo.dwSize = sizeof(pInfo); 
	//从快照中获取进程列表 
	Process32First(hSnapShot, &pInfo) ; //从第一个进程开始循环 
	do 
	{ 
	//这里的 pszProcessName 为你的进程名称 
		if(strcmp(pInfo.szExeFile, pszProcessName) == 0) 
		{
			id = pInfo.th32ProcessID ; 
			return id; 
		} 
	}while(Process32Next(hSnapShot, &pInfo) != FALSE); 
	return 0;
}

int ProcessController::KillTargetIcon(DWORD TargetPID)
{
	HWND hwnd,TargetHwnd;
	DWORD dwProcessID,num;
	HANDLE hTrayProcess;
	PCHAR pBuff;   //字符指针
	TBBUTTON tbBtn;//commctrl.h里的定义
	int btnCount=0,i;
	char szBuffer[255];
	
	hwnd = FindWindow("Shell_TrayWnd",0);
    hwnd = FindWindowEx(hwnd,0,"TrayNotifyWnd",0);
    hwnd = FindWindowEx(hwnd,0,"Syspager",0);
    hwnd = FindWindowEx(hwnd,0,"ToolbarWindow32",0);
	if(!hwnd)
		return 0;
	//由窗口id获取进程id
	GetWindowThreadProcessId(hwnd,&dwProcessID); 
   //获取进程句柄
	hTrayProcess=OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ|PROCESS_VM_WRITE, 
	0, dwProcessID);
	if(!hTrayProcess) //打开失败
	{
		return 0;
	}
	//为目标进程分配了一块物理内存
	pBuff =(PCHAR)VirtualAllocEx(hTrayProcess, 0, 1024, MEM_RESERVE| MEM_COMMIT, PAGE_READWRITE); //取得读写权限
	btnCount = SendMessage(hwnd,TB_BUTTONCOUNT,0,0);//取得托盘图标总数
	for(i=0;i<btnCount;i++) //遍历所有图标
	{
		ZeroMemory(&tbBtn,sizeof(tbBtn));
		if(!WriteProcessMemory(hTrayProcess,pBuff,&tbBtn,sizeof(tbBtn),&num))
		{
		//printf("WriteProcessMemory fail=%d\n",GetLastError());
		return 0;
		}
		if(!SendMessage(hwnd,TB_GETBUTTON,i,(LPARAM)pBuff))
		{
			//printf("GetButton Info fail\n");
		return 0;
		}
		if(!ReadProcessMemory(hTrayProcess,pBuff,&tbBtn,sizeof(tbBtn),&num))
		{
			//printf("ReadProcessMemory fail=%d\n",GetLastError());
		return 0;
		}
		if(!ReadProcessMemory(hTrayProcess,(void *)(tbBtn.dwData),&TargetHwnd,4,&num))
		{
			//printf("ReadProcessMemory fail=%d\n",GetLastError());
		return 0;
		}
		GetWindowThreadProcessId(TargetHwnd,&dwProcessID); //找出创建图标线程的id号
		if(dwProcessID==TargetPID)//图标的进程的ID与
		{
			//AfxMessageBox("Come");
		::SendMessage(hwnd,TB_DELETEBUTTON,i,0); //删图标
		return 1;
		}
	}
	::MessageBox(NULL,"没有相应图标",0,0);
	VirtualFreeEx(hTrayProcess, pBuff, 0, MEM_RELEASE);
	CloseHandle(hTrayProcess);
	return 1;
}
