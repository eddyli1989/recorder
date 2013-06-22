// EndNote.h : main header file for the ENDNOTE application
//

#if !defined(AFX_ENDNOTE_H__794B58E1_D2D2_4D24_9240_1A3F6AA0FA82__INCLUDED_)
#define AFX_ENDNOTE_H__794B58E1_D2D2_4D24_9240_1A3F6AA0FA82__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEndNoteApp:
// See EndNote.cpp for the implementation of this class
//

class CEndNoteApp : public CWinApp
{
public:
	CEndNoteApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEndNoteApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEndNoteApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENDNOTE_H__794B58E1_D2D2_4D24_9240_1A3F6AA0FA82__INCLUDED_)
