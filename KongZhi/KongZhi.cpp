/*TODO
1.�����Զ����У�Ȼ����һ����½�򣬲���½�Ͳ��ܶԵ��Խ��в�����
*/
#include <windows.h>
#include <stdio.h>

#define SLEEPTIME 10   //ÿ��˯�ߵ�ʱ��
#define SAVEFILE "a.exe"  //�������ļ���,Ĭ�ϱ��浽��ǰ·����,�ļ������Թ̶����������ڽ��и���

LPCTSTR m_strTitle1="Screen2Exe v1.2";//��һ�����ڵı���
LPCTSTR m_strTitle2="Screen2Exe";//�ڶ������ڵı���
LPCTSTR m_strTitle3="Screen2Exe";//���������ڵı���
BOOL m_bRecording = FALSE;    //�Ƿ��Ѿ���ʼ¼��

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
    //TODO:ɾ���������ڣ��ó�����һ�����κν����ķ�ʽ����
    //�������ļ�������Ҫ���صĳ������������ָó����Ѿ�����
    //������¼�Ƴ�����Ȼ�������ó������������ָó����Ѿ��رգ���ֹͣ¼��
    //�������ݲ��뵽Զ��DB
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
    hwnd=CreateWindow("ceshi","���Գ���",WS_OVERLAPPEDWINDOW,
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
        ::GetWindowThreadProcessId(hwnd,NULL),  //�Լ����߳�ID
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
  //����F10
  keybd_event(VK_F10, 0, 0, 0);
  keybd_event(VK_F10, 0, KEYEVENTF_KEYUP, 0);
  Sleep(SLEEPTIME);
  HWND hWnd = FindWindowAndSleep(m_strTitle2);
  SaveFile(hWnd, SAVEFILE);
  Sleep(SLEEPTIME);
  //��������
  ::PostMessage(hWnd, WM_COMMAND, 0x1,0x7103C2);
}

int StartRecord(HWND hwnd)
{
    HDC hdc;
    hdc = GetDC(hwnd);
    TextOut(hdc,0,0,"����¼��������ʼ¼��",strlen("����¼��������ʼ¼��"));
    ReleaseDC(hwnd,hdc);

    HINSTANCE hRet = 0;
    hRet = ShellExecute(NULL, "open", "..\\Screen2Exe\\Screen2Exe.exe",NULL, NULL, SW_SHOW);
    if((int)hRet <= 32)
    {
      MessageBox(NULL,"�򿪳���ʧ��",NULL,MB_OK);
      PostQuitMessage(0);
      return 0;
    }

    HWND hWnd1 = FindWindowAndSleep(m_strTitle1);
    //����next
    ::PostMessage( hWnd1 , WM_COMMAND , 0x1 , 0x38068A);
    HWND hWnd2 = FindWindowAndSleep(m_strTitle2);
    //ѡ��good
    ::PostMessage( hWnd2 , WM_COMMAND , 0x3EB, 0xA043E);
    Sleep(SLEEPTIME);
    //����next
    ::PostMessage( hWnd2 , WM_COMMAND , 0x1 , 0xB04E2);
    Sleep(SLEEPTIME);
    HWND hWnd3 = NULL;
    //���������ж��Ƿ���hwnd2���ȣ���Ϊ�������ڵı�����һ����
    while(hWnd3 == NULL || hWnd3 == hWnd2) {
        hWnd3 = ::FindWindow(NULL,m_strTitle3);//��ȡ��һ�����ڵľ���
        Sleep(SLEEPTIME);
    }
    //��ʼ¼��
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
        StopAndSave();
        PostQuitMessage(0);
      }
      break;
    }
  case WM_CLOSE:
    if(IDYES==MessageBox(hwnd,"�Ƿ����Ľ�����",NULL,MB_YESNO))
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
