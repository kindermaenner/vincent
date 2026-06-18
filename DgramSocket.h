#if !defined(AFX_DGRAMSOCKET_H__8E5C8C53_5C86_11D4_B0A1_00609732212B__INCLUDED_)
#define AFX_DGRAMSOCKET_H__8E5C8C53_5C86_11D4_B0A1_00609732212B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DgramSocket.h : header file
//


class CVincentDlg;

/////////////////////////////////////////////////////////////////////////////
// CDgramSocket command target

class CDgramSocket : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CDgramSocket();
	CDgramSocket(CVincentDlg *pDlg) {m_pDlg = pDlg;};
	virtual ~CDgramSocket();

// Overrides
public:
	void OnError (void);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDgramSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CDgramSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	CVincentDlg *m_pDlg;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DGRAMSOCKET_H__8E5C8C53_5C86_11D4_B0A1_00609732212B__INCLUDED_)
