// VincentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Vincent.h"
#include "VincentDlg.h"
#include "dgramsocket.h"
#include "trayicon.h"
#include "ChangeUserNameDlg.h"
#include "logfile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define cPORT 5078
#define IDT_PING			42
#define IDT_PING_TIMEOUT	43
#define cPingTimeout		20000
#define cPingTime			10000
#define WM_TRAY_NOTIFICATION		WM_USER+1042

#define cSECTION_USERINFO		_T("Userinfo")
#define cENTRY_USERNAME			_T("Name")
#define cENTRY_USERNAME_DEF		_T("")
#define cSECTION_MISC			_T("Misc")
#define cENTRY_MSGSTACK			_T("MessageStackLength")
#define cENTRY_SHOWBOX			_T("ShowMessageBox")
#define cENTRY_BEEP				_T("BeepOnMessage")

#define cENTRY_MSGSTACK_DEF		10
#define cNET_SEC				_T("Network")
#define cPORT_ENTRY				_T("Port")
#define cENTRY_SERVER_ADR		_T("Server")
#define cENTRY_SERVER			_T("ServerToUse")
#define cENTRY_PING_TIMEOUT		_T("PingTimeout")
#define cENTRY_PING_TIME		_T("PingTime")

#define cSECTION_LOG			_T("Log")
#define cENTRY_FILENAME			_T("FileName")
#define cENTRY_MAXSIZE			_T("MaxFileSize")

#define cLOGIN_CHAR				_T("#")
#define cLOGOUT_CHAR			_T("-")
#define cMSG_CHAR				_T("*")
#define cQUITTUNG_CHAR			_T("~")
#define cROUTING_CHAR			_T(">")
#define cGOTMSG_CHAR			_T("@")
#define cROUTING_END_CHAR		_T("|")
#define cROUTING_NOTIFY_CHAR	_T("<")

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVincentDlg dialog

CVincentDlg::CVincentDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVincentDlg::IDD, pParent), m_sysIcon(ID_TRAY)
{
	//{{AFX_DATA_INIT(CVincentDlg)
	m_szText = _T("");
	m_szRcv = _T("");
	m_bTon = FALSE;
	m_bBox = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_crLink = AfxGetApp()->LoadIcon(IDC_HAND);
	m_hTray = AfxGetApp()->LoadIcon(ID_TRAY);
	m_hTray2 = AfxGetApp()->LoadIcon(ID_TRAY2);
	m_pServer = NULL;
	m_nPort = cPORT;
	m_nPingTime = cPingTime;
	m_nPingTimeOut = cPingTimeout;
}

void CVincentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVincentDlg)
	DDX_Control(pDX, IDC_USER, m_ctrlUser);
	DDX_Text(pDX, IDC_TEXT, m_szText);
	DDX_Text(pDX, IDC_RCV, m_szRcv);
	DDX_Check(pDX, IDC_TON, m_bTon);
	DDX_Check(pDX, IDC_BOX, m_bBox);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVincentDlg, CDialog)
	//{{AFX_MSG_MAP(CVincentDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_WM_TIMER()
	ON_COMMAND(IDM_CHANGE_NAME, OnTrayChangeName)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_BOX, OnBox)
	ON_BN_CLICKED(IDC_TON, OnTon)
	ON_MESSAGE(WM_TRAY_NOTIFICATION, OnTrayNotification)             
	ON_COMMAND(ID_SHOW, OnShowDlg)
	ON_COMMAND(ID_INFO, OnInfo)
	ON_WM_WINDOWPOSCHANGED()
	ON_NOTIFY(EN_LINK, IDC_RCV, OnRichEditExLink )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVincentDlg message handlers

BOOL CVincentDlg::OnInitDialog()
{
	//m_crLink = IDC_HAND

	m_nMaxMessages = AfxGetApp ()->GetProfileInt (cSECTION_MISC, cENTRY_MSGSTACK, cENTRY_MSGSTACK_DEF);
	m_bBox = AfxGetApp ()->GetProfileInt (cSECTION_MISC, cENTRY_SHOWBOX, TRUE);
	m_bTon = AfxGetApp ()->GetProfileInt (cSECTION_MISC, cENTRY_BEEP, TRUE);

	CLogFile::SetFileName (AfxGetApp ()->GetProfileString (cSECTION_LOG, cENTRY_FILENAME, "vincent.log"));
	CLogFile::SetMaxFileSize (AfxGetApp ()->GetProfileInt (cSECTION_LOG, cENTRY_MAXSIZE, 1024000L));

	CDialog::OnInitDialog();

	CRichEditCtrl *edt = (CRichEditCtrl *)GetDlgItem (IDC_RCV);

	edt->SetBackgroundColor (FALSE, RGB(192,192,192));

	edt->SetEventMask (edt->GetEventMask() | ENM_LINK); 
	::SendMessage (edt->GetSafeHwnd (), EM_AUTOURLDETECT, TRUE, 0);

	m_nPort = AfxGetApp ()->GetProfileInt (cNET_SEC, cPORT_ENTRY, cPORT);
	m_nServer = AfxGetApp ()->GetProfileInt (cNET_SEC, cENTRY_SERVER, 0);
	m_nPingTime = AfxGetApp ()->GetProfileInt (cNET_SEC, cENTRY_PING_TIME, cPingTime);
	m_nPingTimeOut = AfxGetApp ()->GetProfileInt (cNET_SEC, cENTRY_PING_TIMEOUT, cPingTimeout);

	for (int k = 1; k <= m_nServer; k++)
	{
		CString szEntry, s;
		szEntry.Format ("%s%d", cENTRY_SERVER_ADR, k);
		s = AfxGetApp ()->GetProfileString (cNET_SEC, szEntry, "255.255.255.255");
		m_szServer.Add(s);
	}

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	ASSERT((IDM_CHANGE_NAME & 0xFFF0) == IDM_CHANGE_NAME);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	ASSERT((IDM_EDIT_LOG & 0xFFF0) == IDM_EDIT_LOG);
	ASSERT(IDM_EDIT_LOG < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
		strAboutMenu.LoadString (IDS_CHANGE_NAME);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_STRING, IDM_CHANGE_NAME, strAboutMenu);
		}
		strAboutMenu.LoadString (IDS_EDIT_LOG);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_STRING, IDM_EDIT_LOG, strAboutMenu);
		}

	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	InitUserName ();

	m_lstMessages.RemoveAll ();

	if (m_pServer == NULL)
	{
		BOOL bTrue = TRUE;
		m_pServer = new CDgramSocket (this);
		if (!m_pServer->Create (m_nPort, SOCK_DGRAM, FD_READ))
		{
			m_pServer->OnError ();
			PostMessage (WM_CLOSE);
		}
		if (!m_pServer->SetSockOpt (SO_BROADCAST, &bTrue, sizeof(BOOL)))
		{
			m_pServer->OnError ();
			PostMessage (WM_CLOSE);
		}
	}
	if (m_pServer != NULL)
	{
		SendLogin ();
		SetTimer (IDT_PING, m_nPingTime, NULL);
	}
	   
	m_szTipText.Format ("Vincent (Port: %d)", m_nPort);
	m_sysIcon.SetNotificationWnd(this, WM_TRAY_NOTIFICATION);
	m_sysIcon.SetIcon (m_hTray, m_szTipText);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVincentDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		AppAbout ();
	}
	else if ((nID & 0xFFF0) == IDM_CHANGE_NAME)
	{
		OnChangeName ();
	}
	else if (nID == SC_MINIMIZE)
	{
		ShowWindow (SW_HIDE);
	}
	else if (nID == IDM_EDIT_LOG)
	{
		int nRet = (int)ShellExecute (GetSafeHwnd(), _T("open"), CLogFile::GetFileName(), NULL, NULL, SW_SHOWNORMAL);
		if (nRet <= 32)
		{
			switch (nRet)
			{
			case ERROR_FILE_NOT_FOUND :
				::MessageBox (::GetDesktopWindow (), "Datei nicht gefunden!", "Fehler!", MB_OK|MB_SETFOREGROUND|MB_ICONEXCLAMATION);
				break;
			case ERROR_PATH_NOT_FOUND :
				::MessageBox (::GetDesktopWindow (), "Der Pfad ist nicht korrekt!", "Fehler!", MB_OK|MB_SETFOREGROUND|MB_ICONEXCLAMATION);
				break;
			case SE_ERR_ACCESSDENIED : 
			case SE_ERR_SHARE :
				::MessageBox (::GetDesktopWindow (), "Zugriff verweigert!", "Fehler!", MB_OK|MB_SETFOREGROUND|MB_ICONEXCLAMATION);
				break;
			case SE_ERR_ASSOCINCOMPLETE :
			case SE_ERR_NOASSOC :
				::MessageBox (::GetDesktopWindow (), "Mit dem Dateityp ist keine Applikation verknüpft!", "Fehler!", MB_OK|MB_SETFOREGROUND|MB_ICONEXCLAMATION);
				break;
			case SE_ERR_OOM :
			case 0:
				::MessageBox (::GetDesktopWindow (), "Nicht genügend Speicher vorhanden!", "Fehler!", MB_OK|MB_SETFOREGROUND|MB_ICONEXCLAMATION);
				break;
			default:
				::MessageBox (::GetDesktopWindow (), "Unbekannter Fehler bei ShellExecute.", "Fehler!", MB_OK|MB_SETFOREGROUND|MB_ICONEXCLAMATION);
			}
		}
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CVincentDlg::OnDestroy()
{
	SendLogout ();
	m_sysIcon.SetIcon (0);
//	WinHelp(0L, HELP_QUIT);
	CDialog::OnDestroy();
	delete m_pServer;
	m_pServer = NULL;
	delete CLogFile::GetInstance();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVincentDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVincentDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CVincentDlg::OnSend() 
{
	// TODO: Add your control notification handler code here
	UpdateData (TRUE);
	CString s;
	CString szUserSent;

	s.Format ("*%s", m_szText);
	int nCount = m_ctrlUser.GetSelCount ();
	if (nCount == 0)
		return;
	int *pIdx = new int [nCount];
	m_ctrlUser.GetSelItems (nCount, pIdx);
	for (int i = 0; i < nCount; i++)
	{
		CString szUser;
		CString szAdr;
		m_ctrlUser.GetText (pIdx[i], szUser);
		m_mapUser.Lookup (szUser, szAdr);
		SendTo (s, s.GetLength ()+1, m_nPort, szAdr);
		if(!szUserSent.IsEmpty ())
			szUserSent += ", ";
		szUserSent += szUser.SpanExcluding ("(");
	}
	ReportMessage (m_szText, szUserSent, TRUE);
	delete [] pIdx;
    m_ctrlUser.SelItemRange(FALSE, 0, (m_ctrlUser.GetCount()-1));

}

void CVincentDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == IDT_PING)
	{
		// Reset all user to unknown:
		KillTimer (IDT_PING);
		for (int i = 0; i < m_ctrlUser.GetCount (); i++)
		{
			m_ctrlUser.SetItemData (i, FALSE);
		}
		SendLogin ();
		// SendExtraLogin()
		SetTimer (IDT_PING_TIMEOUT, m_nPingTimeOut, NULL);
	}
	else if (nIDEvent == IDT_PING_TIMEOUT)
	{
		KillTimer (IDT_PING_TIMEOUT);
		int nCnt = m_ctrlUser.GetCount ();
		int *pIdx = new int [nCnt];
		int nPos = 0;
		for (int i = 0; i < nCnt; i++)
		{
			if (!m_ctrlUser.GetItemData (i))
				pIdx[nPos++] = i;
		}

		for (i = nPos-1; i >= 0 ; i--)
		{
			CString user, adr;
			m_ctrlUser.GetText (pIdx[i], user);
			m_mapUser.Lookup (user, adr);
			m_mapUser.RemoveKey (user);
			m_mapAdr.RemoveKey (adr);
			m_ctrlUser.DeleteString (pIdx[i]);
		}
		delete [] pIdx;
		SetTimer (IDT_PING, m_nPingTime, NULL);
	}
	CDialog::OnTimer(nIDEvent);
}

void CVincentDlg::OnReceive(CString szTextGiven, CString szSrcAdr, UINT nPort)
{
	CString szData;
	CString szTheText = szTextGiven;
	CString szAdr = szSrcAdr;

	if (szTextGiven.Left (1) == cROUTING_CHAR)
	{
		// Routing

		// GetFrom Adress
		int nIdx = szTextGiven.Find (cROUTING_END_CHAR, 1);
		if (nIdx == -1)
			return;

		// GetText
		CString szHelp = szTextGiven.Mid (nIdx+1);

		// First broadcast it...
		CString szReroute;
		szReroute.Format ("%s%s%s%s", cROUTING_NOTIFY_CHAR, szAdr, cROUTING_END_CHAR, szHelp);
		SendTo (szReroute, szReroute.GetLength ()+1, m_nPort);
		// Do normal processing...
		szTheText.Empty ();
		szTheText = szHelp;
	}
	else if (szTextGiven.Left (1) == cROUTING_NOTIFY_CHAR)
	{
		// Routing

		// GetFrom Adress
		int nIdx = szTextGiven.Find (cROUTING_END_CHAR, 1);
		if (nIdx == -1)
			return;

		szAdr.Empty ();
		szAdr = szTextGiven.Mid (1, nIdx-1);
		
		// GetText
		CString szHelp = szTextGiven.Mid (nIdx+1);

		// Do normal processing...
		szTheText.Empty ();
		szTheText = szHelp;
	}
	if (szTheText.Left (1) == cLOGIN_CHAR) // Broadcast: Bist du online(login)
	{
		UpdateData (TRUE);
		m_mapUser.SetAt (szTheText.Mid (1), szAdr);
		m_mapAdr.SetAt (szAdr, szTheText.Mid(1));
		int nIdx = m_ctrlUser.FindStringExact (-1, szTheText.Mid(1));
		if (nIdx == LB_ERR)
		{
			m_ctrlUser.AddString (szTheText.Mid(1));
		}
		else
		{
			m_ctrlUser.SetItemData (nIdx, TRUE);
		}
		CString s;
		CVincentApp *pApp = (CVincentApp*)AfxGetApp ();
		s.Format ("%s%s (%s)", cQUITTUNG_CHAR, pApp->GetUserName (), GetUserName ());
		SendTo (s, s.GetLength ()+1, nPort, szAdr); // Antworten...
	}
	else if (szTheText.Left (1) == cLOGOUT_CHAR) // Logout
	{
		UpdateData (TRUE);
		int nIdx = m_ctrlUser.FindStringExact (-1, szTheText.Mid(1));
		if (nIdx != LB_ERR)
		{
			m_ctrlUser.DeleteString (nIdx);
		}
		CString user = szTheText.Mid(1), adr;
		if (m_mapUser.Lookup (user, adr))
		{
			m_mapUser.RemoveKey (user);
			m_mapAdr.RemoveKey  (adr);
		}
		UpdateData (FALSE);
	}
	else if (szTheText.Left (1) == cMSG_CHAR) // Message
	{
		CString s, s2;
		UpdateData (TRUE);
		SendTo (cGOTMSG_CHAR, 2, nPort, szAdr); // Antworten...	
		CString szUser;
		m_mapAdr.Lookup (szAdr, szUser);
		s = GetTimeStamp ();
		s += szUser + ": \r\n";
		s2 = szTheText.Mid (1);
		s += s2;
		ReportMessage (s, szUser);
	}
	else if (szTheText.Left (1) == cQUITTUNG_CHAR) // Quittung "bin online"
	{
		UpdateData (TRUE);
		int nIdx = m_ctrlUser.FindStringExact (-1, szTheText.Mid(1));
		if (nIdx == LB_ERR)
		{
			nIdx = m_ctrlUser.AddString (szTheText.Mid(1));
			m_ctrlUser.SetItemData (nIdx, TRUE);
			m_mapUser.SetAt (szTheText.Mid (1), szAdr);
			m_mapAdr.SetAt (szAdr, szTheText.Mid(1));
		}
		else
		{
			m_ctrlUser.SetItemData (nIdx, TRUE);
		}
	}
	else if (szTheText.Left (1) == cGOTMSG_CHAR) // Quittung "Nachricht erhalten"
	{
		CString msg, szUser;
		m_mapAdr.Lookup (szAdr, szUser);
		msg.Empty ();
		msg.Format ("Nachricht wurde erfolgreich an %s gesendet", szUser);
		AfxMessageBox (msg);
	}
	else
	{
		// nix
	}
}


void CVincentDlg::OnDelete() 
{
   m_szText.Empty();
   UpdateData(FALSE);
   CWnd *pWnd = GetDlgItem (IDC_TEXT);
   pWnd->SetFocus ();
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen
	CString s;
	CVincentApp *pApp = (CVincentApp*)AfxGetApp ();
    s.Format ("Vincent Version %s", pApp->GetVersion());
    SetDlgItemText (IDC_VERSION, s);
	if (AfxGetApp ()->GetProfileInt ("Misc", "FakeCopyright", 0) == 0)
		s.LoadString (IDS_COPYRIGHT1);
	else
		s.LoadString (IDS_COPYRIGHT2);
	SetDlgItemText (IDC_COPYRIGHT, s);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CVincentDlg::AppAbout (void)
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

LRESULT  CVincentDlg::OnTrayNotification(WPARAM wp, LPARAM lp)
{
	return m_sysIcon.OnTrayNotification (wp,lp);
}

void CVincentDlg::OnShowDlg()
{
	ShowWindow (SW_SHOW);
	SetForegroundWindow();
	m_sysIcon.SetIcon (m_hTray, m_szTipText);
}

void CVincentDlg::OnInfo()
{
	AppAbout ();
}

void CVincentDlg::SetUserName(LPCTSTR szName)
{
	m_szUserName.Empty ();
	m_szUserName = szName;
}

LPCTSTR CVincentDlg::GetUserName()
{
	return m_szUserName;
}

void CVincentDlg::InitUserName()
{
	CWinApp* pApp = AfxGetApp ();
	m_szUserName = pApp->GetProfileString (cSECTION_USERINFO, cENTRY_USERNAME, cENTRY_USERNAME_DEF);
	if (m_szUserName.IsEmpty ())
	{
		AskForUserName ();
	}
	if (!m_szUserName.IsEmpty ())
	{
		AfxGetApp()->WriteProfileString (cSECTION_USERINFO, cENTRY_USERNAME, m_szUserName);
		RenewTitleBar ();
	}
	else
	{
		PostMessage (WM_CLOSE);
	}
}

void CVincentDlg::AskForUserName()
{
	CChangeUserNameDlg dlg;
	dlg.m_szName = m_szUserName;
	if (dlg.DoModal () == IDOK)
		SetUserName (dlg.m_szName);

}

void CVincentDlg::OnChangeName() 
{
	// TODO: Add your control notification handler code here
	CString szOldName = GetUserName ();
	AskForUserName ();
	SendLogout (szOldName);
	SendLogin ();
	RenewTitleBar ();
	CVincentApp *pApp = (CVincentApp*)AfxGetApp ();
	pApp->WriteProfileString (cSECTION_USERINFO, cENTRY_USERNAME, m_szUserName);
}

void CVincentDlg::SendLogout(LPCTSTR szName)
{
	CVincentApp *pApp = (CVincentApp*)AfxGetApp ();
	CString s;
	if (szName == NULL)
		s.Format ("%s%s (%s)", cLOGOUT_CHAR, pApp->GetUserName (), GetUserName ());
	else
		s.Format ("%s%s (%s)", cLOGOUT_CHAR, pApp->GetUserName (), szName);
	SendTo (s, s.GetLength ()+1, m_nPort);
	SendToServers (s);
}

void CVincentDlg::SendLogin()
{
	CVincentApp *pApp = (CVincentApp*)AfxGetApp ();
	CString s;
	s.Format ("%s%s (%s)", cLOGIN_CHAR, pApp->GetUserName (), GetUserName ());
	SendTo (s, s.GetLength ()+1, m_nPort);
	SendToServers (s);
}

void CVincentDlg::RenewTitleBar()
{
	CString s;
	s.Format ("Vincent - %s", m_szUserName);
	SetWindowText (s);
}


void CVincentDlg::OnTrayChangeName() 
{
	// TODO: Add your command handler code here
	OnChangeName ();	
}


void CVincentDlg::OnBox() 
{
	// TODO: Add your control notification handler code here
	UpdateData (TRUE);	
	CVincentApp *pApp = (CVincentApp*)AfxGetApp ();
	pApp->WriteProfileInt (cSECTION_MISC, cENTRY_SHOWBOX, m_bBox);
}

void CVincentDlg::OnTon() 
{
	// TODO: Add your control notification handler code here
	UpdateData (TRUE);		
	CVincentApp *pApp = (CVincentApp*)AfxGetApp ();
	pApp->WriteProfileInt (cSECTION_MISC, cENTRY_BEEP, m_bTon);
}

void CVincentDlg::OnWindowPosChanged( WINDOWPOS* lpwndpos )
{
	m_sysIcon.SetIcon (m_hTray, m_szTipText);
}

void CVincentDlg::ReportMessage(CString s, CString szUser, BOOL bSelf)
{
	CString szText;

	if (bSelf)
	{
		CString s2 = GetTimeStamp ();
		szText.Format ("%s-> %s: \r\n%s ", s2, szUser, s);
	}
	else
	{
		szText = s;
	}
	if (szText.Right (2) != "\r\n")
		szText += "\r\n";
	m_szRcv.Empty ();
	m_lstMessages.AddHead (szText);
	CLogFile::GetInstance ()->LogString (szText);
	if (m_lstMessages.GetCount () > m_nMaxMessages)
		m_lstMessages.RemoveTail ();
	POSITION pos = m_lstMessages.GetHeadPosition ();
	while (pos != NULL)
	{
		m_szRcv += m_lstMessages.GetNext (pos);
	}
	UpdateData (FALSE);
	if (!bSelf)
	{
		m_sysIcon.SetIcon (m_hTray2, m_szTipText);
		if (m_bTon)
			::MessageBeep(0xFFFFFFFF);
		if (m_bBox)
		{
			::MessageBox (::GetDesktopWindow (), szText, szUser, MB_OK|MB_SETFOREGROUND|MB_ICONEXCLAMATION);
			m_sysIcon.SetIcon (m_hTray, m_szTipText);
		}
	}
}

CString CVincentDlg::GetTimeStamp()
{
	CString s;
	CTime t = CTime::GetCurrentTime();
	s.Format ("[%02d:%02d:%02d] ", t.GetHour (), t.GetMinute (), t.GetSecond ());
	return s;
}


void CVincentDlg::OnRichEditExLink(NMHDR *in_pNotifyHeader, LRESULT *out_pResult)
{
	ENLINK* l_pENLink = ( ENLINK* )in_pNotifyHeader ;

	*out_pResult = 0 ;
	CRichEditCtrl *edt = (CRichEditCtrl *)GetDlgItem (IDC_RCV);

	switch (l_pENLink->msg)
	{
		default:
		{
		}
		break ;

		case WM_SETCURSOR:
		{
			if (m_crLink != NULL)
			{
			    ::SetCursor (m_crLink);

				*out_pResult = 1 ;
			}
		}
		break ;

		case WM_LBUTTONDOWN:
		{
			CString l_URL ;
			CHARRANGE l_CharRange;

			edt->GetSel (l_CharRange);
			edt->SetSel (l_pENLink->chrg);
			l_URL = edt->GetSelText();
			edt->SetSel (l_CharRange);

			CWaitCursor l_WaitCursor ;

			ShellExecute (GetSafeHwnd(), _T("open"), l_URL, NULL, NULL, SW_SHOWNORMAL);

			*out_pResult = 1 ;
		}
		break ;

		case WM_LBUTTONUP:
		{
			*out_pResult = 1 ;
		}
		break ;
	}
}

void CVincentDlg::SendToServers(CString szText)
{
	CString s;
	
	s.Format ("%s%s%s%s", cROUTING_CHAR, _T("0.0.0.0"), cROUTING_END_CHAR, szText);
	for (int i = 0; i < m_nServer; i++)
	{
		SendTo (s, s.GetLength ()+1, m_nPort, m_szServer[i]);
	}
}

void CVincentDlg::SendTo(CString s, int nLen, int nPort, LPCTSTR szAdr)
{
	CString str;
	str.Format ("Snd (%s:%d): %s\r\n",szAdr, nPort, s);
	OutputDebugString (str);
	m_pServer->SendTo (s, nLen, nPort, szAdr);
}
