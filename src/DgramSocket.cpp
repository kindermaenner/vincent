// DgramSocket.cpp : implementation file
//

#include "pch.h"
#include "Vincent.h"
#include "DgramSocket.h"
#include "vincentdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDgramSocket

CDgramSocket::CDgramSocket()
{
}

CDgramSocket::~CDgramSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CDgramSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CDgramSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CDgramSocket member functions

void CDgramSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (nErrorCode != 0)
		OnError ();
	DWORD dwLen;
	if (!IOCtl (FIONREAD, &dwLen))
		OnError ();
	CString s;
	char *pszText = s.GetBuffer (dwLen+1);
	CString rAdr;
	UINT rPort = 0;
	ReceiveFrom (pszText, dwLen+1, rAdr, rPort);
	s.ReleaseBuffer ();
	m_pDlg->OnReceive (s, rAdr, rPort);
	CAsyncSocket::OnReceive(nErrorCode);
}

void CDgramSocket::OnError()
{
	CString s;
	s.Format ("Fehler %d", GetLastError());
	AfxMessageBox (s);
}
