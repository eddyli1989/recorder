; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CKeyNoteDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "KeyNote.h"

ClassCount=3
Class1=CKeyNoteApp
Class2=CKeyNoteDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_KEYNOTE_DIALOG

[CLS:CKeyNoteApp]
Type=0
HeaderFile=KeyNote.h
ImplementationFile=KeyNote.cpp
Filter=N

[CLS:CKeyNoteDlg]
Type=0
HeaderFile=KeyNoteDlg.h
ImplementationFile=KeyNoteDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EDIT1

[CLS:CAboutDlg]
Type=0
HeaderFile=KeyNoteDlg.h
ImplementationFile=KeyNoteDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_KEYNOTE_DIALOG]
Type=1
Class=CKeyNoteDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1352728580

