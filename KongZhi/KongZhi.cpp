/*�������ֻ�Ǹ������Ĳ��Գ������ó�������һ�����ڣ��ڴ����е�һ�������������������¼��������¼�ơ�
�м�������Sleep�������׾�����ô���¡�
������Ҫ��ɵģ�
1.��¼���������һ��F10������Ϣ����¼�����ֹͣ¼�ƣ�Ȼ���¼���ļ����棬�����ʱ����¼�����ʱ��ϵͳʱ��Ϊ���֡�
2.�����������Կ����Զ����У�Ȼ����һ����½�򣬲���½�Ͳ��ܶԵ��Խ��в���������û��õ����ǵ�½��Ϳ�ʼ¼�ƻ��ǵ��ض�������к�
  ��¼�ơ�
���ڴ�ŵ�˼·�����ˣ���˧���㿴������д�в��У���MFC���ǿ��Ĳ�̫���ף���MFC�ǲ��ǻ��ܼ�Щ��*/

#include <windows.h>
#include <stdio.h>

#define SLEEPTIME 10
LPCTSTR m_strTitle1="Screen2Exe v1.2";//��һ�����ڵı���
LPCTSTR m_strTitle2="Screen2Exe";//�ڶ������ڵı���
LPCTSTR m_strTitle3="Screen2Exe";//���������ڵı���

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

void StopAndSave()
{
	//����F10
	keybd_event(VK_F10,0,0,0);
	HWND hWnd = NULL;
    while(hWnd == NULL) {
       hWnd = ::FindWindow(NULL,m_strTitle2);
       Sleep(SLEEPTIME);
    }

    //������Ϊ��ť
	::PostMessage(hWnd, WM_COMMAND, 0x3F4, 0x5A0496);


	keybd_event('1',0,0,0);
	keybd_event('.',0,0,0);
	keybd_event('e',0,0,0);
	keybd_event('x',0,0,0);
	keybd_event('e',0,0,0);

	HWND hWnd1 = NULL;
    while(hWnd1 == NULL) {
       hWnd1 = ::FindWindow(NULL,"���Ϊ");
       Sleep(SLEEPTIME);
    }
	::PostMessage(hWnd1, WM_COMMAND, 0x1, 0x2F0112);
	Sleep(SLEEPTIME);
	hWnd = NULL;
	while(hWnd == NULL) {
       hWnd = ::FindWindow(NULL,m_strTitle2);
       Sleep(SLEEPTIME);
    }
    //������
    ::PostMessage(hWnd, WM_COMMAND, 0x1,0x7103C2);
}

int StartRecord(HWND hwnd)
{
    HDC hdc;
    hdc = GetDC(hwnd);
    TextOut(hdc,0,0,"����¼�������ʼ¼��",strlen("����¼�������ʼ¼��"));
    ReleaseDC(hwnd,hdc);

    HINSTANCE hRet=0;
    hRet = ShellExecute(NULL, "open", "..\\Screen2Exe\\Screen2Exe.exe",NULL, NULL, SW_SHOW);
    if((int)hRet <= 32)
    {
      MessageBox(NULL,"�򿪳���ʧ��",NULL,MB_OK);
      PostQuitMessage(0);
      return 0;
    }


	HWND hWnd1 = NULL;
	//���û���ҵ����ھ�һֱѭ��,��֤��Ϣ�ܹ����ͳɹ�
	while (hWnd1 == NULL) {
		hWnd1 = ::FindWindow(NULL,m_strTitle1);//��ȡ��һ�����ڵľ��
		Sleep(SLEEPTIME);
	}
    ::PostMessage( hWnd1 , WM_COMMAND , 0x1 , 0x38068A);//����һ�����ڷ���Ϣ��ģ����NEXT��ť

    HWND hWnd2 = NULL;
    while(hWnd2 == NULL) {
       hWnd2 = ::FindWindow(NULL,m_strTitle2);//��ȡ�ڶ������ڵľ��
       Sleep(SLEEPTIME);
    }

    ::PostMessage( hWnd2 , WM_COMMAND , 0x3EB, 0xA043E);
    Sleep(10);//���ڶ������ڷ���Ϣ��ģ��ѡ����GOOD¼��
    ::PostMessage( hWnd2 , WM_COMMAND , 0x1 , 0xB04E2);
    Sleep(10);//���ڶ������ڷ���Ϣ��ģ����NEXT��ť
    HWND hWnd3 = NULL;
    while(hWnd3 == NULL || hWnd3 == hWnd2) {
        hWnd3 = ::FindWindow(NULL,m_strTitle3);//��ȡ��һ�����ڵľ��
    }

    ::PostMessage( hWnd3 , WM_COMMAND , 0x1 , 0x1B05F0);Sleep(10);//�����������ڷ���Ϣ��ģ������ʼ¼�ư�ť
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
    if(IDYES==MessageBox(hwnd,"�Ƿ���Ľ�����",NULL,MB_YESNO))
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
