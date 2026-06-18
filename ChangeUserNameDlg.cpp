// ChangeUserNameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Vincent.h"
#include "ChangeUserNameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChangeUserNameDlg dialog


CChangeUserNameDlg::CChangeUserNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChangeUserNameDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChangeUserNameDlg)
	m_szName = _T("");
	//}}AFX_DATA_INIT
}


void CChangeUserNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChangeUserNameDlg)
	DDX_Text(pDX, IDC_NAME, m_szName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChangeUserNameDlg, CDialog)
	//{{AFX_MSG_MAP(CChangeUserNameDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChangeUserNameDlg message handlers
