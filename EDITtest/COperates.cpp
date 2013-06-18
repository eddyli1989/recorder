//COperates���Դ�ļ�

#include "stdafx.h"
#include "EDITtest.h"
#include "EDITtestDlg.h"
#include "COperates.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

COperates::COperates()
{
}

void  COperates::DisableDesktop()
{
	//��ֹʹ������Ϳ�ʼ�˵�
	HWND hProgram=::FindWindow("Progman","Program Manager");
	HWND hChild=::FindWindowEx(hProgram,NULL,"SHELLDLL_DefView",NULL);
	::EnableWindow(hChild,false);//��ֹʹ������,���������򴰿ڻ���ʹ��
	::EnableWindow(::FindWindow("Shell_TrayWnd",NULL),false);//��ֹʹ��"��ʼ"�˵���
}

void  COperates::EnableDesktop()
{
	//����ʹ������Ϳ�ʼ�˵�
	HWND hProgram=::FindWindow("Progman","Program Manager");
	HWND hChild=::FindWindowEx(hProgram,NULL,"SHELLDLL_DefView",NULL);
	::EnableWindow(hChild,true);//����ʹ������,���������򴰿ڻ���ʹ��
	::EnableWindow(::FindWindow("Shell_TrayWnd",NULL),true);//����ʹ��"��ʼ"�˵���
}

void  COperates::DisableTaskMgr()
{
	//��ֹ���������
	char Subkey[]="Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System";
	DWORD Disable=1;
	HKEY hkResult;
	int ret=RegCreateKey(HKEY_CURRENT_USER,Subkey,&hkResult);
	ret=RegSetValueEx(hkResult,"DisableTaskMgr",0,REG_DWORD,(LPBYTE)&Disable,sizeof(Disable));
	RegCloseKey(hkResult);
}

void  COperates::EnableTaskMgr()
{
	//�������������
	char Subkey[]="Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System";
	DWORD Enable=0;
	HKEY hkResult;
	int ret=RegCreateKey(HKEY_CURRENT_USER,Subkey,&hkResult);
	ret=RegSetValueEx(hkResult,"DisableTaskMgr",0,REG_DWORD,(LPBYTE)&Enable,sizeof(Enable));
	RegCloseKey(hkResult);
}

void  COperates::AddAutoRun(LPSTR Pro)
{
	//��ӳ��򿪻��Զ�����
	char regname[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
//	LPSTR Pro="D:\\EDITtest.exe";
	HKEY hkResult;
	int ret=RegOpenKey(HKEY_LOCAL_MACHINE,regname,&hkResult);
	ret=RegSetValueEx(hkResult,"EDITtest"/* ע������*/,0,REG_EXPAND_SZ,(unsigned char *)Pro,20);
	RegCloseKey(hkResult);
}


