// KeyNoteDlg.h : header file
//

#if !defined(AFX_KEYNOTEDLG_H__99DC420E_8A9F_40C0_BAA2_EDB5A96E0016__INCLUDED_)
#define AFX_KEYNOTEDLG_H__99DC420E_8A9F_40C0_BAA2_EDB5A96E0016__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CKeyNoteDlg dialog

class CKeyNoteDlg : public CDialog
{
// Construction
public:
	BOOL PreTranslateMessage(MSG *pMsg);
	CKeyNoteDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CKeyNoteDlg)
	enum { IDD = IDD_KEYNOTE_DIALOG };
	CString	m_String;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKeyNoteDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CKeyNoteDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KEYNOTEDLG_H__99DC420E_8A9F_40C0_BAA2_EDB5A96E0016__INCLUDED_)
