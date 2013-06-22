// KeyNoteDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KeyNote.h"
#include "KeyNoteDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define NoteFile_PATH "../config/NoteFile.ini"
char Input[1000]={0};//存放编辑框输入的内容
int Time;//存放录制开始了多长时间，单位分钟

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
// CKeyNoteDlg dialog

CKeyNoteDlg::CKeyNoteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKeyNoteDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKeyNoteDlg)
	m_String = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKeyNoteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKeyNoteDlg)
	DDX_Text(pDX, IDC_EDIT1, m_String);
	DDV_MaxChars(pDX, m_String, 1000);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CKeyNoteDlg, CDialog)
	//{{AFX_MSG_MAP(CKeyNoteDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKeyNoteDlg message handlers

BOOL CKeyNoteDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	int tHour;
	int tMinute;
	char Temp[10];

	GetDlgItemText(IDC_EDIT1,Input,10);
	SYSTEMTIME st;
	::GetLocalTime(&st);//获取系统当前时间
	
	//sprintf(tHour,"%d",st.wHour);//格式化小时
	//sprintf(tMinute,"%d",st.wMinute);//格式化分钟
	::GetPrivateProfileString("动作","开始录制","False",Temp,10,NoteFile_PATH);//读取INI文件中开始录制的时间
	
	tHour=(Temp[0]-48)*10+(Temp[1]-48);
	tMinute=(Temp[3]-48)*10+(Temp[4]-48);
	Time=( (int)st.wHour-tHour )*60+( (int)st.wMinute-tMinute );//计算录制开始了多长时间,单位分钟

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

void CKeyNoteDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CKeyNoteDlg::OnPaint() 
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
		//CDialog::OnPaint();
		CPaintDC   dc(this);  

           CRect   rect;  

           GetClientRect(&rect);  

           CDC   dcMem;  

           dcMem.CreateCompatibleDC(&dc);  

           CBitmap   bmpBackground;  

           bmpBackground.LoadBitmap(IDB_BITMAP1);  

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
HCURSOR CKeyNoteDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CKeyNoteDlg::OnOK() 
{
	// TODO: Add extra validation here
	char StrTime[20]="";
	sprintf(StrTime,"开始录制%d分钟",Time);
	GetDlgItemText(IDC_EDIT1,Input,sizeof(Input));
	::WritePrivateProfileString(StrTime,"用户输入备注信息",Input,NoteFile_PATH);
	CDialog::OnOK();
}

BOOL CKeyNoteDlg::PreTranslateMessage(MSG *pMsg)
{
	//屏蔽ESC、Enter、F4键
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)    
        return TRUE; 
    if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)    
        return TRUE;
	if(pMsg->message==WM_SYSKEYDOWN&&pMsg->wParam==VK_F4)
		return TRUE;
    return CDialog::PreTranslateMessage(pMsg);
}
