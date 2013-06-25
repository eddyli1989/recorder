#define   _WIN32_WINNT   0x0500
#include<windows.h>
#include<process.h>
#include<stdio.h>
#include<vector>
#include<string>
#include<sstream>
#include<tchar.h>
#include"../log.h"
#include"CNoteFile.h"
#include"ProcessController.h"
using namespace std;

#define VC_EXTRALEAN
#define MAX_PROCESS_LENGTH 1024
#define RECORDER_PATH "../deps/Screen2Exe/Screen2Exe.exe"    //¼�Ƴ�������·��
#define SLEEPTIME 10   //ÿ��˯�ߵ�ʱ��
#define SAVEFILE "../config/Recoder.exe"  //������ļ���,Ĭ�ϱ��浽��ǰ·����
#define PROCESSCONFIG "../config/process.ini"
#define RETRY_TIMES 1000


HHOOK LowLevelKeyboardHook = NULL;
LPCTSTR m_strTitle1 = "Screen2Exe v1.2";//��һ�����ڵı���
LPCTSTR m_strTitle2 = "Screen2Exe";//�ڶ������ڵı���
LPCTSTR m_strTitle3 = "Screen2Exe";//���������ڵı���
BOOL m_bRecording = FALSE;    //�Ƿ��Ѿ���ʼ¼��

LRESULT CALLBACK LowLevelKeyboardProc(
  int nCode,     // hook code
  WPARAM wParam, // message identifier
  LPARAM lParam  // message data
);


int ReadProcessConfig(vector<string> &list) {
   char Temp[MAX_PROCESS_LENGTH] = { 0 };
   int ret = ::GetPrivateProfileString("process", "watch", "False", Temp, MAX_PROCESS_LENGTH, PROCESSCONFIG);//��ȡINI�ļ��е�����
   Temp[MAX_PROCESS_LENGTH -1] = '\0';
   if (ret > 0) {
        string str(Temp);
        string buf; // Have a buffer string
        stringstream ss(str); // Insert the string into a stream
        while (ss >> buf)
            list.push_back(buf);
        return 0;
   }
   return -1;
}

HWND FindWindowAndSleep(LPCTSTR title) {
  HWND hwnd = NULL;
  int retry = 0;
  while (hwnd == NULL && retry < RETRY_TIMES) {
      hwnd = ::FindWindow(NULL,title);
      retry+=1;
      Sleep(SLEEPTIME);
  }
  return hwnd;
}

void SaveFile(HWND hwnd, LPCSTR keys) {
    log_info(_T("[SaveFile]saving file..."));
    AttachThreadInput(::GetCurrentThreadId(),
        ::GetWindowThreadProcessId(hwnd,NULL),  //�Լ����߳�ID
        TRUE);
    HWND hedit1 = FindWindowEx(hwnd, NULL, "Edit", NULL);
    HWND hedit2 = FindWindowEx(hwnd, hedit1, "Edit", NULL);
    HWND hedit3 = FindWindowEx(hwnd, hedit2, "Edit", NULL);
    SetFocus(hedit3);
    UINT len = strlen(keys);
    for (UINT i = 0; i < len; i++) {
        ::SendMessage(hedit3, WM_CHAR, keys[i], 0);
    }
	CNoteFile::WriteOperationToNote("����¼��");
	CNoteFile::OpenEndNote();
    log_info(_T("[SaveFile]saving file done"));
}


void StopAndSave() {
	//����F10
	log_info(_T("[StopAndSave]stop recording and saving..."));
	UnhookWindowsHookEx(LowLevelKeyboardHook);
	keybd_event(VK_F10, 0, 0, 0);
	keybd_event(VK_F10, 0, KEYEVENTF_KEYUP, 0);
	Sleep(SLEEPTIME);
	HWND hWnd = FindWindowAndSleep(m_strTitle2);
	if (hWnd != NULL) {
		SaveFile(hWnd, SAVEFILE);
		Sleep(SLEEPTIME);
		//������
		::PostMessage(hWnd, WM_COMMAND, 0x1,0x7103C2);
		
		log_info(_T("[StopAndSave]stop recording and saving done"));
	} else {
		log_error(_T("Find Window Failed"));
	}
}

HANDLE StartRecord(ProcessController& controller) {

    log_info(_T("launch recorder to record"));
	CNoteFile::WriteOperationToNote("��ʼ¼��");
	CNoteFile::OpenStartNote();
    SHELLEXECUTEINFO ShellInfo;
    BOOL ret = controller.StartProcess(RECORDER_PATH, &ShellInfo);
    if (!ret) {
        log_error(_T("open recorder faied"));
        PostQuitMessage(0);
        return 0;
    }

    HWND hWnd1 = FindWindowAndSleep(m_strTitle1);
    //���next
    ::PostMessage( hWnd1 , WM_COMMAND , 0x1 , 0x38068A);
    HWND hWnd2 = FindWindowAndSleep(m_strTitle2);
    //ѡ��good
    ::PostMessage( hWnd2 , WM_COMMAND , 0x3EB, 0xA043E);
    Sleep(SLEEPTIME);
    //���next
    ::PostMessage( hWnd2 , WM_COMMAND , 0x1 , 0xB04E2);
    Sleep(SLEEPTIME);
    HWND hWnd3 = NULL;
    //��������ж��Ƿ��hwnd2��ȣ���Ϊ�������ڵı�����һ����
    int retry = 0;
    while(hWnd3 == NULL || hWnd3 == hWnd2 && retry < RETRY_TIMES) {
        hWnd3 = ::FindWindow(NULL,m_strTitle3);//��ȡ��һ�����ڵľ��
        Sleep(SLEEPTIME);
        retry += 1;
    }
    if (hWnd1 == NULL || hWnd2 == NULL || hWnd3 == NULL)
        return NULL;
    //��ʼ¼��
    ::PostMessage( hWnd3 , WM_COMMAND , 0x1 , 0x1B05F0);
    Sleep(SLEEPTIME);
    return ShellInfo.hProcess;
}


unsigned int __stdcall Hook(void * arg)
{


	LowLevelKeyboardHook = SetWindowsHookEx(
								WH_KEYBOARD_LL,
								LowLevelKeyboardProc,
								GetModuleHandle(NULL),
								0);

    MSG msg;
    while(GetMessage(&msg,NULL,0,0))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    return 0;

} 

int WINAPI WinMain
(
HINSTANCE hInstance,
HINSTANCE hPrevInstance,
LPSTR lpCmdLine,
int nCmdShow
){
    log_info(_T("start watch process"));
    ProcessController controller;
    vector<string> list;
    ReadProcessConfig(list);
    PROCESSENTRY32 entry;
	DWORD PID=0;
	BOOL RecorderFlag=false;
	HANDLE hThread;
    memset(&entry, 0 , sizeof(entry));
    while (TRUE) {
        if ( controller.FindProcessInList(list, &entry) ) {
            HANDLE processHandle = ::OpenProcess(SYNCHRONIZE, FALSE, entry.th32ProcessID);
            if ( (processHandle != NULL)&&(!RecorderFlag) ) {
                StartRecord(controller);
				RecorderFlag=true;
				hThread=(HANDLE)_beginthreadex(NULL,0,Hook,NULL,0,NULL);
				int retry=0;
				do
				{
					PID=controller.GetSpecifiedProcessId("Screen2Exe.exe");
					retry+=1;
				}while(!PID && retry < RETRY_TIMES);
				Sleep(1000);
				controller.KillTargetIcon(PID);

				while(RecorderFlag) {
					DWORD ret =  WaitForSingleObject(processHandle, INFINITE);
					if ( !controller.FindProcessInList(list, &entry) ) {
						if ( (ret == WAIT_OBJECT_0)&&(RecorderFlag)) {
							StopAndSave();
							RecorderFlag=false;
							CloseHandle(hThread);
						} else {
							log_error(_T("wait error:%d"),::GetLastError());
						}
					} else {
						HANDLE processHandle = ::OpenProcess(SYNCHRONIZE, FALSE, entry.th32ProcessID);
						DWORD ret =  WaitForSingleObject(processHandle, INFINITE);
					}

				}
            }
        }
        //ÿ��3��ɨ��һ��
        Sleep(SLEEPTIME * 200);
    }
}

LRESULT CALLBACK LowLevelKeyboardProc(
  int nCode,     // hook code
  WPARAM wParam, // message identifier
  LPARAM lParam  // message data
)   {
        if (nCode<0 ) return CallNextHookEx(LowLevelKeyboardHook,nCode,wParam,lParam);

        if (wParam==WM_KEYDOWN) {
                int KeyCode=((KBDLLHOOKSTRUCT*)lParam)->vkCode;
                if ( KeyCode == 121 ){
                    return 1;
                }
				if ( KeyCode == 123 ){
					CNoteFile::OpenKeyNote();
					return 1;
				}
        }
        return CallNextHookEx(LowLevelKeyboardHook,nCode,wParam,lParam); //���ݹ�����Ϣ
}
