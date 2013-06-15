/*现在这个只是个初步的测试程序，我用程序生成一个窗口，在窗口中点一下鼠标左键，程序就启动录制软件完成录制。
中间有两个Sleep不是明白具体怎么回事。
下来还要完成的：
1.给录制软件发送一个F10按键消息，让录制软件停止录制，然后把录制文件保存，保存的时候以录制完成时的系统时间为名字。
2.让这个软件可以开机自动运行，然后做一个登陆框，不登陆就不能对电脑进行操作。现在没想好到底是登陆后就开始录制还是等特定软件运行后
  再录制。
现在大概的思路都有了，狗帅，你看看这样写行不行，我MFC还是看的不太明白，用MFC是不是还能简单些。*/

#include <windows.h>
#include <stdio.h>

#define SLEEPTIME 10
LPCTSTR m_strTitle1="Screen2Exe v1.2";//第一个窗口的标题
LPCTSTR m_strTitle2="Screen2Exe";//第二个窗口的标题
LPCTSTR m_strTitle3="Screen2Exe";//第三个窗口的标题

BOOL m_bRecording = FALSE;

LRESULT CALLBACK WinKongZhiProc(
  HWND hwnd,      // handle to window
  UINT uMsg,      // message identifier
  WPARAM wParam,  // first message parameter
  LPARAM lParam   // second message parameter
);

int WINAPI WinMain(
  HINSTANCE hInstance,      // handle to current instance
  HINSTANCE hPrevInstance,  // handle to previous instance
  LPSTR lpCmdLine,          // command line
  int nCmdShow              // show state
)
{
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

    MSG msg;
    while(GetMessage(&msg,NULL,0,0))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    return 0;
}

void StopAndSave()
{
	//按下F10
	keybd_event(VK_F10,0,0,0);
	HWND hWnd = NULL;
    while(hWnd == NULL) {
       hWnd = ::FindWindow(NULL,m_strTitle2);
       Sleep(SLEEPTIME);
    }

    //点击另存为按钮
	::PostMessage(hWnd, WM_COMMAND, 0x3F4, 0x5A0496);


	keybd_event('1',0,0,0);
	keybd_event('.',0,0,0);
	keybd_event('e',0,0,0);
	keybd_event('x',0,0,0);
	keybd_event('e',0,0,0);

	HWND hWnd1 = NULL;
    while(hWnd1 == NULL) {
       hWnd1 = ::FindWindow(NULL,"另存为");
       Sleep(SLEEPTIME);
    }
	::PostMessage(hWnd1, WM_COMMAND, 0x1, 0x2F0112);
	Sleep(SLEEPTIME);
	hWnd = NULL;
	while(hWnd == NULL) {
       hWnd = ::FindWindow(NULL,m_strTitle2);
       Sleep(SLEEPTIME);
    }
    //点击完成
    ::PostMessage(hWnd, WM_COMMAND, 0x1,0x7103C2);
}

int StartRecord(HWND hwnd)
{
    HDC hdc;
    hdc = GetDC(hwnd);
    TextOut(hdc,0,0,"调用录制软件开始录制",strlen("调用录制软件开始录制"));
    ReleaseDC(hwnd,hdc);

    HINSTANCE hRet=0;
    hRet = ShellExecute(NULL, "open", "..\\Screen2Exe\\Screen2Exe.exe",NULL, NULL, SW_SHOW);
    if((int)hRet <= 32)
    {
      MessageBox(NULL,"打开程序失败",NULL,MB_OK);
      PostQuitMessage(0);
      return 0;
    }


	HWND hWnd1 = NULL;
	//如果没有找到窗口就一直循环,保证消息能够发送成功
	while (hWnd1 == NULL) {
		hWnd1 = ::FindWindow(NULL,m_strTitle1);//获取第一个窗口的句柄
		Sleep(SLEEPTIME);
	}
    ::PostMessage( hWnd1 , WM_COMMAND , 0x1 , 0x38068A);//给第一个窗口发消息，模拟点击NEXT按钮

    HWND hWnd2 = NULL;
    while(hWnd2 == NULL) {
       hWnd2 = ::FindWindow(NULL,m_strTitle2);//获取第二个窗口的句柄
       Sleep(SLEEPTIME);
    }

    ::PostMessage( hWnd2 , WM_COMMAND , 0x3EB, 0xA043E);
    Sleep(10);//给第二个窗口发消息，模拟选择了GOOD录制
    ::PostMessage( hWnd2 , WM_COMMAND , 0x1 , 0xB04E2);
    Sleep(10);//给第二个窗口发消息，模拟点击NEXT按钮
    HWND hWnd3 = NULL;
    while(hWnd3 == NULL || hWnd3 == hWnd2) {
        hWnd3 = ::FindWindow(NULL,m_strTitle3);//获取第一个窗口的句柄
    }

    ::PostMessage( hWnd3 , WM_COMMAND , 0x1 , 0x1B05F0);Sleep(10);//给第三个窗口发消息，模拟点击开始录制按钮
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
        StopAndSave();
		PostQuitMessage(0);
      }
      break;
    }
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
