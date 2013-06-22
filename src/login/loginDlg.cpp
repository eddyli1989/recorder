// EDITtestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "login.h"
#include "loginDlg.h"
#include "COperates.h"
#include "Shlwapi.h"

#define CONFIG "../config/user.ini"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define NoteFile_PATH "../config/NoteFile.ini"
#define Login_PATH "../deps/Login.exe"
char Name[10]={0};			//存放登陆用户名
char PassWord[10]={0};		//存放登陆用户密码
HHOOK LowLevelKeyboardHook=NULL;//钩子句柄，用来屏蔽WIN键
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

LRESULT CALLBACK LowLevelKeyboardProc(//低级钩子回调函数声明
  int nCode,     // hook code
  WPARAM wParam, // message identifier
  LPARAM lParam  // message data
);

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CLoginDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_KILLFOCUS(IDC_EDIT1, OnKillfocusEdit1)
	ON_EN_KILLFOCUS(IDC_EDIT2, OnKillfocusEdit2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg message handlers

BOOL CLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.
	//安装低级钩子
	LowLevelKeyboardHook=SetWindowsHookEx(WH_KEYBOARD_LL,
		LowLevelKeyboardProc,GetModuleHandle(NULL),0);

	//屏蔽桌面消息和开始按钮消息
	COperates::DisableDesktop();

	//添加程序开机自动启动
	COperates::AddAutoRun(Login_PATH);

	//禁止任务管理器
	COperates::DisableTaskMgr();

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLoginDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLoginDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
	//	CDialog::OnPaint();
		 CPaintDC   dc(this);  

           CRect   rect;  

           GetClientRect(&rect);  

           CDC   dcMem;  

           dcMem.CreateCompatibleDC(&dc);  

           CBitmap   bmpBackground;  

           bmpBackground.LoadBitmap(IDB_BITMAP2);  

                   //IDB_BITMAP是你自己的图对应的ID  

           BITMAP   bitmap;  

           bmpBackground.GetBitmap(&bitmap);  

           CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground);  

           dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,  

         bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);  
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLoginDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CLoginDlg::OnKillfocusEdit1() 
{
	// TODO: Add your control notification handler code here
	GetDlgItemText(IDC_EDIT1,Name,10); //编辑框失去焦点时记录编辑框的文字	
}

void CLoginDlg::OnKillfocusEdit2() 
{
	// TODO: Add your control notification handler code here
	GetDlgItemText(IDC_EDIT2,PassWord,10); //编辑框失去焦点时记录编辑框的文字		
}

BOOL CLoginDlg::PreTranslateMessage(MSG *pMsg)
{
	//屏蔽ESC、Enter、Alt键
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)    
        return TRUE; 
    if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)    
        return TRUE;
	if(pMsg->message==WM_SYSKEYDOWN&&pMsg->wParam==VK_F4)
		return TRUE;
    return CDialog::PreTranslateMessage(pMsg);
}

void CLoginDlg::OnOK() 
{
	// TODO: Add extra validation here
	char Temp[10]={0};			
	::GetPrivateProfileString(Name,"password","False",Temp,10, CONFIG);//读取INI文件中的密码	
	if(0!=StrCmp(Temp,PassWord)||Temp=="False")//密码比较，输入段名错误测返回False，即用户名错误
	{
		::MessageBox(NULL,"用户名或密码错误！",NULL,NULL);
	}
	else
	{
		//卸载低级钩子
		UnhookWindowsHookEx(LowLevelKeyboardHook);

		//允许使用桌面和开始菜单
		COperates::EnableDesktop();

		//允许任务管理器
		COperates::EnableTaskMgr();//暂时设置在此就允许任务管理器，以后等录制结束再允许
		
		//打开录制控制程序
		COperates::OpenRecorderControl();

		//创建以日期为名的ini文件，记录登录人员信息和录制过程中的信息
		SYSTEMTIME st;
		GetLocalTime(&st);//获取系统当前时间
		char Time[20]="0";		
		sprintf(Time,"%d:%d",st.wHour,st.wMinute);//格式化系统时间作为段名 
		::WritePrivateProfileString(Time,"登录人员",Name,NoteFile_PATH);
	
		CDialog::OnOK();
	}
}

//低级钩子回调函数屏蔽WIN键
LRESULT CALLBACK LowLevelKeyboardProc(int nCode,WPARAM wParam, LPARAM lParam)
{ 
	if (nCode<0 ) return CallNextHookEx(LowLevelKeyboardHook,nCode,wParam,lParam);
 
	if (wParam==WM_KEYDOWN)
	{
		int KeyCode=((KBDLLHOOKSTRUCT*)lParam)->vkCode;
		if (KeyCode==91)
			return 1;
	}
	return CallNextHookEx(LowLevelKeyboardHook,nCode,wParam,lParam); //传递钩子信息
}
