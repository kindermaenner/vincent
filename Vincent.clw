; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Vincent.h"

ClassCount=5
Class1=CVincentApp
Class2=CVincentDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_VINCENT_DIALOG
Resource2=IDR_MAINFRAME
Class4=CDgramSocket
Resource3=IDD_CHANGE_USERNAME
Resource4=ID_TRAY
Class5=CChangeUserNameDlg
Resource5=IDD_ABOUTBOX

[CLS:CVincentApp]
Type=0
HeaderFile=Vincent.h
ImplementationFile=Vincent.cpp
Filter=N
LastObject=CVincentApp
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CVincentDlg]
Type=0
HeaderFile=VincentDlg.h
ImplementationFile=VincentDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CVincentDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=VincentDlg.h
ImplementationFile=VincentDlg.cpp
Filter=D
LastObject=CAboutDlg
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_VERSION,static,1342308480
Control3=IDC_COPYRIGHT,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_VINCENT_DIALOG]
Type=1
Class=CVincentDlg
ControlCount=12
Control1=IDC_TEXT,edit,1352732740
Control2=IDC_USER,listbox,1352730883
Control3=IDC_SEND,button,1342242816
Control4=IDC_DELETE,button,1342242817
Control5=IDCANCEL,button,1342242816
Control6=IDC_RCV,RICHEDIT20A,1352742980
Control7=IDC_BOX,button,1342177283
Control8=IDC_TON,button,1342177283
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,button,1342177287

[CLS:CDgramSocket]
Type=0
HeaderFile=DgramSocket.h
ImplementationFile=DgramSocket.cpp
BaseClass=CAsyncSocket
Filter=N
VirtualFilter=q
LastObject=CDgramSocket

[MNU:ID_TRAY]
Type=1
Class=?
Command1=ID_SHOW
Command2=ID_INFO
Command3=IDM_CHANGE_NAME
CommandCount=3

[DLG:IDD_CHANGE_USERNAME]
Type=1
Class=CChangeUserNameDlg
ControlCount=3
Control1=IDC_NAME,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816

[CLS:CChangeUserNameDlg]
Type=0
HeaderFile=ChangeUserNameDlg.h
ImplementationFile=ChangeUserNameDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CChangeUserNameDlg

