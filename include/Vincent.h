// Vincent.h : main header file for the VINCENT application
//

#if !defined(AFX_VINCENT_H__0F1EDD08_58BC_11D4_B09F_00609732212B__INCLUDED_)
#define AFX_VINCENT_H__0F1EDD08_58BC_11D4_B09F_00609732212B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CVincentApp:
// See Vincent.cpp for the implementation of this class
//

class CVincentApp : public CWinApp
{
public:
	CString GetUserName (void);
	CVincentApp();
    CString GetVersion();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVincentApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVincentApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	HINSTANCE m_hInstRichEdit;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VINCENT_H__0F1EDD08_58BC_11D4_B09F_00609732212B__INCLUDED_)
