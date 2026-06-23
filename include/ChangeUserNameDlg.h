#if !defined(AFX_CHANGEUSERNAMEDLG_H__69E63461_7F40_11D4_B0AF_00609732212B__INCLUDED_)
#define AFX_CHANGEUSERNAMEDLG_H__69E63461_7F40_11D4_B0AF_00609732212B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChangeUserNameDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChangeUserNameDlg dialog

class CChangeUserNameDlg : public CDialog
{
// Construction
public:
	CChangeUserNameDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChangeUserNameDlg)
	enum { IDD = IDD_CHANGE_USERNAME };
	CString	m_szName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChangeUserNameDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChangeUserNameDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANGEUSERNAMEDLG_H__69E63461_7F40_11D4_B0AF_00609732212B__INCLUDED_)
