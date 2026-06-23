// VincentDlg.h : header file
//

#if !defined(AFX_VINCENTDLG_H__0F1EDD0A_58BC_11D4_B09F_00609732212B__INCLUDED_)
#define AFX_VINCENTDLG_H__0F1EDD0A_58BC_11D4_B09F_00609732212B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "trayicon.h"

class CDgramSocket;
/////////////////////////////////////////////////////////////////////////////
// CVincentDlg dialog

class CVincentDlg : public CDialog
{
// Construction
public:
	void RenewTitleBar (void);
	void SendLogin (void);
	void SendLogout (LPCTSTR szName = NULL);
	void AskForUserName(void);
	void InitUserName (void);
	LPCTSTR GetUserName (void);
	void SetUserName(LPCTSTR szName);
	void OnInfo ();
	void OnShowDlg ();
	void OnChangeName();
	void OnReceive (CString szText, CString szAdr, UINT nPort);
	CVincentDlg(CWnd* pParent = NULL);	// standard constructor
	static void AppAbout (void);
// Dialog Data
	//{{AFX_DATA(CVincentDlg)
	enum { IDD = IDD_VINCENT_DIALOG };
	CListBox	m_ctrlUser;
	CString	m_szText;
	CString	m_szRcv;
	BOOL	m_bTon;
	BOOL	m_bBox;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVincentDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
	LRESULT  OnTrayNotification(WPARAM wp, LPARAM lp);
	afx_msg void OnWindowPosChanged( WINDOWPOS* lpwndpos );


// Implementation
protected:
	int m_nPingTimeOut;
	int m_nPingTime;
	void SendTo (CString s, int nLen, int nPort, LPCTSTR szAdr = NULL);
	void SendToServers (CString szText);
	CStringArray m_szServer;
	int m_nServer;
	HICON m_hTray2;
	HICON m_hTray;
	CString m_szTipText;
	HCURSOR m_crLink;
	void OnRichEditExLink(NMHDR* in_pNotifyHeader, LRESULT* out_pResult);
	CString GetTimeStamp (void);
	void ReportMessage (CString s, CString szUser, BOOL bSelf = FALSE);
	CStringList m_lstMessages;
	int m_nMaxMessages;
	int m_nPort;
	CString m_szUserName;
	CTrayIcon m_sysIcon;
	HICON m_hIcon;
	CDgramSocket *m_pServer;
	CMapStringToString m_mapUser, m_mapAdr;
	// Generated message map functions
	//{{AFX_MSG(CVincentDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSend();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnTrayChangeName();
	afx_msg void OnDelete();
	afx_msg void OnBox();
	afx_msg void OnTon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VINCENTDLG_H__0F1EDD0A_58BC_11D4_B09F_00609732212B__INCLUDED_)
