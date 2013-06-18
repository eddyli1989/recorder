//COperates类的源文件

#include "stdafx.h"
#include "EDITtest.h"
#include "EDITtestDlg.h"
#include "COperates.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define RECORDER_CONTROL_PATH "..\\bin\\recorder.exe"	//录制控制程序的相对路径

COperates::COperates()
{
}

void  COperates::DisableDesktop()
{
	//禁止使用桌面和开始菜单
	HWND hProgram=::FindWindow("Progman","Program Manager");
	HWND hChild=::FindWindowEx(hProgram,NULL,"SHELLDLL_DefView",NULL);
	::EnableWindow(hChild,false);//禁止使用桌面,但其它程序窗口还能使用
	::EnableWindow(::FindWindow("Shell_TrayWnd",NULL),false);//禁止使用"开始"菜单栏
}

void  COperates::EnableDesktop()
{
	//允许使用桌面和开始菜单
	HWND hProgram=::FindWindow("Progman","Program Manager");
	HWND hChild=::FindWindowEx(hProgram,NULL,"SHELLDLL_DefView",NULL);
	::EnableWindow(hChild,true);//允许使用桌面,但其它程序窗口还能使用
	::EnableWindow(::FindWindow("Shell_TrayWnd",NULL),true);//允许使用"开始"菜单栏
}

void  COperates::DisableTaskMgr()
{
	//禁止任务管理器
	char Subkey[]="Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System";
	DWORD Disable=1;
	HKEY hkResult;
	int ret=RegCreateKey(HKEY_CURRENT_USER,Subkey,&hkResult);
	ret=RegSetValueEx(hkResult,"DisableTaskMgr",0,REG_DWORD,(LPBYTE)&Disable,sizeof(Disable));
	RegCloseKey(hkResult);
}

void  COperates::EnableTaskMgr()
{
	//允许任务管理器
	char Subkey[]="Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System";
	DWORD Enable=0;
	HKEY hkResult;
	int ret=RegCreateKey(HKEY_CURRENT_USER,Subkey,&hkResult);
	ret=RegSetValueEx(hkResult,"DisableTaskMgr",0,REG_DWORD,(LPBYTE)&Enable,sizeof(Enable));
	RegCloseKey(hkResult);
}

void  COperates::AddAutoRun(LPSTR Pro)
{
	//添加程序开机自动启动
	char regname[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
//	LPSTR Pro="D:\\EDITtest.exe";
	HKEY hkResult;
	int ret=RegOpenKey(HKEY_LOCAL_MACHINE,regname,&hkResult);
	ret=RegSetValueEx(hkResult,"EDITtest"/* 注册表键名*/,0,REG_EXPAND_SZ,(unsigned char *)Pro,20);
	RegCloseKey(hkResult);
}



void COperates::OpenRecorderControl()
{
	//打开录制程序
	HINSTANCE hRet = 0;
    hRet = ShellExecute(NULL, "open", RECORDER_CONTROL_PATH, NULL, NULL, SW_SHOW);
    if((int)hRet <= 32)
    {
      MessageBox(NULL,"打开程序失败",NULL,MB_OK);
      PostQuitMessage(0);
    }
}




