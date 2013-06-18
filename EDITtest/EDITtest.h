// EDITtest.h : main header file for the EDITTEST application
//

#if !defined(AFX_EDITTEST_H__A994C87F_B6EE_4944_87A5_BC1D0B27A47F__INCLUDED_)
#define AFX_EDITTEST_H__A994C87F_B6EE_4944_87A5_BC1D0B27A47F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEDITtestApp:
// See EDITtest.cpp for the implementation of this class
//

class CEDITtestApp : public CWinApp
{
public:
	CEDITtestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEDITtestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEDITtestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITTEST_H__A994C87F_B6EE_4944_87A5_BC1D0B27A47F__INCLUDED_)
