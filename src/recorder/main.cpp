
#define   _WIN32_WINNT   0x0500
#include <windows.h>
#include <stdio.h>

#define VC_EXTRALEAN 

#define RECORDER_PATH "..\\deps\\Screen2Exe\\Screen2Exe.exe"	//录制程序的相对路径
#define SLEEPTIME 10   //每次睡眠的时间
#define SAVEFILE "Recoder.exe"  //保存的文件名,默认保存到当前路径下

HHOOK LowLevelKeyboardHook=NULL;
LPCTSTR m_strTitle1="Screen2Exe v1.2";//第一个窗口的标题
LPCTSTR m_strTitle2="Screen2Exe";//第二个窗口的标题
LPCTSTR m_strTitle3="Screen2Exe";//第三个窗口的标题
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


int WINAPI WinMain(
  HINSTANCE hInstance,      // handle to current instance
  HINSTANCE hPrevInstance,  // handle to previous instance
  LPSTR lpCmdLine,          // command line
  int nCmdShow              // show state
)
{
    //TODO:删除这个窗口，让程序以一个无任何界面的方式运行
    //在配置文件中配置要监控的程序，如果发现该程序已经运行
    //则启动录制程序，然后监听该程序，如果发现该程序已经关闭，则停止录制
    //并把数据插入到远程DB
    WNDCLASS wndcls;
    wndcls.cbClsExtra=0;
    wndcls.cbWndExtra=0;
    wndcls.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
    wndcls.hCursor=LoadCursor(NULL,IDC_ARROW);
    wndcls.hIcon=LoadIcon(NULL,IDI_INFORMATION);
    wndcls.hInstance=hInstance;
    wndcls.lpfnWndProc=WinKongZhiProc;
    wndcls.lpszClassName="ceshi";
    wndcls.lpszMenuName=NULL;
    wndcls.style=CS_HREDRAW | CS_VREDRAW;
    RegisterClass(&wndcls);

    HWND hwnd;
    hwnd=CreateWindow("ceshi","测试程序",WS_OVERLAPPEDWINDOW,
      0,0,600,400,NULL,NULL,hInstance,NULL);

    ShowWindow(hwnd,SW_SHOWNORMAL);
    UpdateWindow(hwnd);
	
	LowLevelKeyboardHook=SetWindowsHookEx(WH_KEYBOARD_LL,LowLevelKeyboardProc,GetModuleHandle(NULL),0);

    MSG msg;
    while(GetMessage(&msg,NULL,0,0))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    return 0;
}

HWND FindWindowAndSleep(LPCTSTR title) {
  HWND hwnd = NULL;
  while (hwnd == NULL) {
      hwnd = ::FindWindow(NULL,title);
      Sleep(SLEEPTIME);
  }
  return hwnd;
}

void SaveFile(HWND hwnd, LPCSTR keys)
{
    AttachThreadInput(::GetCurrentThreadId(),
        ::GetWindowThreadProcessId(hwnd,NULL),  //自己的线程ID
        TRUE);
    HWND hedit1 = FindWindowEx(hwnd, NULL, "Edit", NULL);
    HWND hedit2 = FindWindowEx(hwnd, hedit1, "Edit", NULL);
    HWND hedit3 = FindWindowEx(hwnd, hedit2, "Edit", NULL);
    SetFocus(hedit3);
    UINT len = strlen(keys);
    for (UINT i = 0; i < len; i++)
    {
        ::SendMessage(hedit3, WM_CHAR, keys[i], 0);
    }
}

void StopAndSave()
{
  //按下F10
  keybd_event(VK_F10, 0, 0, 0);
  keybd_event(VK_F10, 0, KEYEVENTF_KEYUP, 0);
  Sleep(SLEEPTIME);
  HWND hWnd = FindWindowAndSleep(m_strTitle2);
  SaveFile(hWnd, SAVEFILE);
  Sleep(SLEEPTIME);
  //点击完成
  ::PostMessage(hWnd, WM_COMMAND, 0x1,0x7103C2);
}

int StartRecord(HWND hwnd)
{
    HDC hdc;
    hdc = GetDC(hwnd);
    TextOut(hdc,0,0,"调用录制软件开始录制",strlen("调用录制软件开始录制"));
    ReleaseDC(hwnd,hdc);

    HINSTANCE hRet = 0;
    hRet = ShellExecute(NULL, "open", RECORDER_PATH, NULL, NULL, SW_SHOW);
    if((int)hRet <= 32)
    {
      MessageBox(NULL,"打开程序失败",NULL,MB_OK);
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
    while(hWnd3 == NULL || hWnd3 == hWnd2) {
        hWnd3 = ::FindWindow(NULL,m_strTitle3);//获取第一个窗口的句柄
        Sleep(SLEEPTIME);
    }
    //开始录制
    ::PostMessage( hWnd3 , WM_COMMAND , 0x1 , 0x1B05F0);
    Sleep(SLEEPTIME);
    return 1;
}

LRESULT CALLBACK WinKongZhiProc(
  HWND hwnd,      // handle to window
  UINT uMsg,      // message identifier
  WPARAM wParam,  // first message parameter
  LPARAM lParam   // second message parameter
)
{
  switch(uMsg)
  {
  case WM_LBUTTONDOWN:
    {
      if (!m_bRecording)
      {
        StartRecord(hwnd);
        m_bRecording = TRUE;
      }
      else
      {
		UnhookWindowsHookEx(LowLevelKeyboardHook);
        StopAndSave();
        PostQuitMessage(0);
      }
      break;
    }
  case WM_SYSKEYDOWN:
		MessageBox(hwnd,"没有屏蔽F10",NULL,MB_YESNO);
	  break;
  case WM_CLOSE:
    if(IDYES==MessageBox(hwnd,"是否真的结束？",NULL,MB_YESNO))
    {
      DestroyWindow(hwnd);
    }
    break;
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  default:
    return DefWindowProc(hwnd,uMsg,wParam,lParam);
  }
  return 0;
}

LRESULT CALLBACK LowLevelKeyboardProc(
  int nCode,     // hook code
  WPARAM wParam, // message identifier
  LPARAM lParam  // message data
)
{
	if (nCode<0 ) return CallNextHookEx(LowLevelKeyboardHook,nCode,wParam,lParam);
 
	if (wParam==WM_KEYDOWN)
	{
		int KeyCode=((KBDLLHOOKSTRUCT*)lParam)->vkCode;
		

		if ( KeyCode == 121  )
		{
			
			return 1;
		}
	}

	return CallNextHookEx(LowLevelKeyboardHook,nCode,wParam,lParam); //传递钩子信息  
}