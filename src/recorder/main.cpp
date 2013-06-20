#define   _WIN32_WINNT   0x0500
#include<windows.h>
#include<stdio.h>
#include<vector>
#include<string>
#include<sstream>
#include<tchar.h>
#include"../log.h"
#include"ProcessController.h"
using namespace std;

#define VC_EXTRALEAN 
#define MAX_PROCESS_LENGTH 1024
#define RECORDER_PATH "..\\deps\\Screen2Exe\\Screen2Exe.exe"    //录制程序的相对路径
#define SLEEPTIME 10   //每次睡眠的时间
#define SAVEFILE "Recoder.exe"  //保存的文件名,默认保存到当前路径下
#define PROCESSCONFIG "../config/process.ini"
#define RETRY_TIMES 1000

HHOOK LowLevelKeyboardHook = NULL;
LPCTSTR m_strTitle1 = "Screen2Exe v1.2";//第一个窗口的标题
LPCTSTR m_strTitle2 = "Screen2Exe";//第二个窗口的标题
LPCTSTR m_strTitle3 = "Screen2Exe";//第三个窗口的标题
BOOL m_bRecording = FALSE;    //是否已经开始录制

LRESULT CALLBACK WinKongZhiProc(
  HWND hwnd,      // handle to window
  UINT uMsg,      // message identifier
  WPARAM wParam,  // first message parameter
  LPARAM lParam   // second message parameter
);

LRESULT CALLBACK LowLevelKeyboardProc(
  int nCode,     // hook code
  WPARAM wParam, // message identifier
  LPARAM lParam  // message data
);


int ReadProcessConfig(vector<string> &list) {
   char Temp[MAX_PROCESS_LENGTH] = { 0 };
   int ret = ::GetPrivateProfileString("process", "watch", "False", Temp, MAX_PROCESS_LENGTH, PROCESSCONFIG);//读取INI文件中的密码
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
        ::GetWindowThreadProcessId(hwnd,NULL),  //自己的线程ID
        TRUE);
    HWND hedit1 = FindWindowEx(hwnd, NULL, "Edit", NULL);
    HWND hedit2 = FindWindowEx(hwnd, hedit1, "Edit", NULL);
    HWND hedit3 = FindWindowEx(hwnd, hedit2, "Edit", NULL);
    SetFocus(hedit3);
    UINT len = strlen(keys);
    for (UINT i = 0; i < len; i++) {
        ::SendMessage(hedit3, WM_CHAR, keys[i], 0);
    }
    log_info(_T("[SaveFile]saving file done"));
}


void StopAndSave() {
  //按下F10
  log_info(_T("[StopAndSave]stop recording and saving..."));
  UnhookWindowsHookEx(LowLevelKeyboardHook);
  keybd_event(VK_F10, 0, 0, 0);
  keybd_event(VK_F10, 0, KEYEVENTF_KEYUP, 0);
  Sleep(SLEEPTIME);
  HWND hWnd = FindWindowAndSleep(m_strTitle2);
  if (hWnd != NULL) {
      SaveFile(hWnd, SAVEFILE);
      Sleep(SLEEPTIME);
      //点击完成
      ::PostMessage(hWnd, WM_COMMAND, 0x1,0x7103C2);
      log_info(_T("[StopAndSave]stop recording and saving done")); 
  } else {
      log_error(_T("Find Window Failed"));
  }
  
}

HANDLE StartRecord(ProcessController& controller) {
    LowLevelKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, 
                LowLevelKeyboardProc,
                GetModuleHandle(NULL),
                0);
    log_info(_T("launch recorder to record"));
    SHELLEXECUTEINFO ShellInfo;        
    BOOL ret = controller.StartProcess(RECORDER_PATH, &ShellInfo);
    if (!ret) {
        log_error(_T("open recorder faied"));
        PostQuitMessage(0);
        return 0;
    }

    HWND hWnd1 = FindWindowAndSleep(m_strTitle1);
    //点击next
    ::PostMessage( hWnd1 , WM_COMMAND , 0x1 , 0x38068A);
    HWND hWnd2 = FindWindowAndSleep(m_strTitle2);
    //选择good
    ::PostMessage( hWnd2 , WM_COMMAND , 0x3EB, 0xA043E);
    Sleep(SLEEPTIME);
    //点击next
    ::PostMessage( hWnd2 , WM_COMMAND , 0x1 , 0xB04E2);
    Sleep(SLEEPTIME);
    HWND hWnd3 = NULL;
    //这里必须判断是否和hwnd2相等，因为两个窗口的标题是一样的
    int retry = 0;
    while(hWnd3 == NULL || hWnd3 == hWnd2 && retry < RETRY_TIMES) {
        hWnd3 = ::FindWindow(NULL,m_strTitle3);//获取第一个窗口的句柄
        Sleep(SLEEPTIME);
        retry += 1;
    }
    if (hWnd1 == NULL || hWnd2 == NULL || hWnd3 == NULL)
        return NULL;
    //开始录制
    ::PostMessage( hWnd3 , WM_COMMAND , 0x1 , 0x1B05F0);
    Sleep(SLEEPTIME);
    return ShellInfo.hProcess;
}


int StartWatchProcess() {
    log_info(_T("start watch process"));
    ProcessController controller;
    vector<string> list;
    ReadProcessConfig(list); 
    PROCESSENTRY32 entry;
    memset(&entry, 0 , sizeof(entry));
    while (TRUE) {
        if ( controller.FindProcessInList(list, &entry) ) {
            HANDLE processHandle = ::OpenProcess(SYNCHRONIZE, FALSE, entry.th32ProcessID);
            if (processHandle != NULL) {
                StartRecord(controller); 
                DWORD ret =  WaitForSingleObject(processHandle, INFINITE);
                if (ret == WAIT_OBJECT_0) {
                    StopAndSave(); 
                } else {
                    log_error(_T("wait error:%d"),::GetLastError());
               }
            }
        }
        //每隔3秒扫描一次
        Sleep(SLEEPTIME * 300);
    }
}

int WINAPI WinMain(
  HINSTANCE hInstance,      // handle to current instance
  HINSTANCE hPrevInstance,  // handle to previous instance
  LPSTR lpCmdLine,          // command line
  int nCmdShow              // show state
) {
   StartWatchProcess();
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
        }
        return CallNextHookEx(LowLevelKeyboardHook,nCode,wParam,lParam); //传递钩子信息  
}
