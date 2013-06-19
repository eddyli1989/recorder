// login.h : main header file for the LOGIN application
//

#if !defined(AFX_LOGIN_H__F5E97E95_B246_4589_9D52_4B5A36951C17__INCLUDED_)
#define AFX_LOGIN_H__F5E97E95_B246_4589_9D52_4B5A36951C17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLoginApp:
// See login.cpp for the implementation of this class
//

class CLoginApp : public CWinApp
{
public:
	CLoginApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLoginApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGIN_H__F5E97E95_B246_4589_9D52_4B5A36951C17__INCLUDED_)
