// Vincent.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
// Link with version.lib for file version APIs used in GetVersion()
#pragma comment(lib, "version.lib")
#include "Vincent.h"
#include "VincentDlg.h"
#include <LMCONS.H>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVincentApp

BEGIN_MESSAGE_MAP(CVincentApp, CWinApp)
	//{{AFX_MSG_MAP(CVincentApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVincentApp construction

CVincentApp::CVincentApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CVincentApp object

CVincentApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CVincentApp initialization

BOOL CVincentApp::InitInstance()
{

	TCHAR pszExeFileName [_MAX_PATH], pszIniFileName [_MAX_PATH];
	TCHAR drive[_MAX_DRIVE];   
	TCHAR dir[_MAX_DIR];   
	TCHAR fname[_MAX_FNAME];
    TCHAR ext[_MAX_EXT];

	::GetModuleFileName (NULL, pszExeFileName, _MAX_PATH);
	_tsplitpath (pszExeFileName, drive, dir, fname, ext);
	_tmakepath (pszIniFileName, drive, dir, fname, _T("ini"));
	//First free the string allocated by MFC at CWinApp startup.
	//The string is allocated before InitInstance is called.
	free((void*)m_pszProfileName);
	//Change the name of the .INI file.
	//The CWinApp destructor will free the memory.
	m_pszProfileName = _tcsdup(pszIniFileName);

	if ((m_hInstRichEdit = LoadLibrary("RICHED20.DLL")) == NULL)
	{
		AfxMessageBox ("RichEdit init failed.");
		return FALSE;
	}
	

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	// Enable3dControls() is obsolete in modern MFC; removed.
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CVincentDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

CString CVincentApp::GetUserName()
{
	CString s;
	char *lpBuffer = s.GetBuffer(UNLEN+1);
	DWORD dwLen = UNLEN+1;
	::GetUserName ((char*)lpBuffer, &dwLen);
	s.ReleaseBuffer ();
	return s;
}

CString CVincentApp::GetVersion()
{
	CString szVersion;
	DWORD dwDummy;
	DWORD dwLen;
	UINT nVersionLen;
	LPVOID lpData, lpVersion;
	TCHAR szFileName[_MAX_PATH];

	::GetModuleFileName (NULL, szFileName, _MAX_PATH);
	dwLen = ::GetFileVersionInfoSize (szFileName, &dwDummy);
	lpData = (LPVOID)new BYTE[dwLen];
	::GetFileVersionInfo ((TCHAR*)(LPCTSTR)szFileName, dwDummy, dwLen, lpData);
	if (!::VerQueryValue (lpData, _T("\\StringFileInfo\\040704b0\\FileVersion"), &lpVersion, &nVersionLen))
	{
		szVersion = _T("00.00.00");
	}
	else
	{
		TCHAR *pBuffer = szVersion.GetBuffer (nVersionLen+1);
		memcpy (pBuffer, lpVersion, nVersionLen);
		szVersion.ReleaseBuffer (nVersionLen);
	}
	delete [] (BYTE*)lpData;
	return szVersion;
}


int CVincentApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	if (m_hInstRichEdit != NULL)
		FreeLibrary (m_hInstRichEdit);
	return CWinApp::ExitInstance();
}
