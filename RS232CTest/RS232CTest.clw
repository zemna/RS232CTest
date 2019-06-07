; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSettingDlg
LastTemplate=CStatic
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "rs232ctest.h"
LastPage=0
CDK=Y

ClassCount=13
Class1=CCheckSK
Class2=CRoundButton
Class3=CRS232CTestApp
Class4=CRS232CTestDlg
Class5=CSettingDlg
Class6=CXListBox

ResourceCount=4
Resource1=IDD_DIALOG_COLOR
Resource2=IDD_DIALOG_SETTING (English (U.S.))
Class7=CMyHexEdit
Class8=CMyDataEdit
Class9=CMyRepeatEdit
Class10=CColorPickerButton
Resource3=IDD_RS232CTEST_DIALOG (English (U.S.))
Class11=CColorSelectDlg
Class12=CMyColorButton
Class13=CMyStatic
Resource4=IDR_XLISTBOX (English (U.S.))

[CLS:CCheckSK]
Type=0
BaseClass=CButton
HeaderFile=CCheckSK.h
ImplementationFile=CCheckSK.cpp

[CLS:CRoundButton]
Type=0
BaseClass=CButton
HeaderFile=RoundButton.h
ImplementationFile=RoundButton.cpp
LastObject=CRoundButton

[CLS:CRS232CTestApp]
Type=0
BaseClass=CWinApp
HeaderFile=RS232CTest.h
ImplementationFile=RS232CTest.cpp
LastObject=CRS232CTestApp

[CLS:CRS232CTestDlg]
Type=0
BaseClass=CDialog
HeaderFile=RS232CTestDlg.h
ImplementationFile=RS232CTestDlg.cpp
LastObject=CRS232CTestDlg
Filter=W
VirtualFilter=dWC

[CLS:CSettingDlg]
Type=0
BaseClass=CDialog
HeaderFile=SettingDlg.h
ImplementationFile=SettingDlg.cpp
LastObject=CSettingDlg
Filter=D
VirtualFilter=dWC

[CLS:CXListBox]
Type=0
BaseClass=CListBox
HeaderFile=XListBox.h
ImplementationFile=XListBox.cpp
LastObject=CXListBox
Filter=W
VirtualFilter=bWC

[DLG:IDD_RS232CTEST_DIALOG]
Type=1
Class=CRS232CTestDlg

[DLG:IDD_DIALOG_SETTING]
Type=1
Class=CSettingDlg

[DLG:IDD_DIALOG_SETTING (English (U.S.))]
Type=1
Class=?
ControlCount=26
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308866
Control4=IDC_COMBO_PORT,combobox,1344339970
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,static,1342308866
Control7=IDC_COMBO_BAUDRATE,combobox,1344339970
Control8=IDC_STATIC,static,1342308866
Control9=IDC_COMBO_DATABIT,combobox,1344339970
Control10=IDC_STATIC,static,1342308866
Control11=IDC_COMBO_STOPBIT,combobox,1344339970
Control12=IDC_STATIC,static,1342308866
Control13=IDC_COMBO_PARITY,combobox,1344339970
Control14=IDC_STATIC,static,1342308866
Control15=IDC_COMBO_FLOW,combobox,1344339970
Control16=IDC_EDIT_LIMIT,edit,1484849281
Control17=IDC_STATIC,static,1342308866
Control18=IDC_STATIC,button,1342177287
Control19=IDC_EDIT_ETX,edit,1350631553
Control20=IDC_STATIC,static,1342308866
Control21=IDC_STATIC,static,1342308866
Control22=IDC_EDIT_COUNT,edit,1484849281
Control23=IDC_STATIC,static,1342308866
Control24=IDC_RADIO_ETX,button,1342308361
Control25=IDC_RADIO_TIME,button,1342177289
Control26=IDC_RADIO_COUNT,button,1342177289

[DLG:IDD_RS232CTEST_DIALOG (English (U.S.))]
Type=1
Class=?
ControlCount=22
Control1=IDC_EDIT_STARTCODE,edit,1350631553
Control2=IDC_EDIT_DATA,edit,1350631552
Control3=IDC_EDIT_ENDCODE,edit,1350631553
Control4=IDC_BUTTON_SEND,button,1342242817
Control5=IDC_EDIT_REPEAT,edit,1350631553
Control6=IDC_CHECK_REPEAT,button,1342246915
Control7=IDC_BUTTON_RECONNECT,button,1342242816
Control8=IDC_BUTTON_SAVE,button,1342242816
Control9=IDC_BUTTON_CLEAR,button,1342242816
Control10=IDC_LIST_SHOW,listbox,1353779537
Control11=IDC_FRAME_DATA,button,1342177543
Control12=IDC_FRAME_SEND,button,1342177287
Control13=IDC_STATIC_STX,static,1342308352
Control14=IDC_STATIC_DATA,static,1342308352
Control15=IDC_STATIC_ETX,static,1342308352
Control16=IDC_STATIC_REPEATPER,static,1342308866
Control17=IDC_STATIC_MSEC,static,1342308864
Control18=IDC_CHECK_HEXRECEIVE,button,1342242819
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_BUTTON_RECV_COLOR,button,1342279435
Control22=IDC_BUTTON_SEND_COLOR,button,1342279435

[MNU:IDR_XLISTBOX (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_SELECT_ALL
Command2=ID_EDIT_COPY
Command3=ID_EDIT_CLEAR
CommandCount=3

[CLS:CMyHexEdit]
Type=0
HeaderFile=MyHexEdit.h
ImplementationFile=MyHexEdit.cpp
BaseClass=CEdit
Filter=W
VirtualFilter=WC

[CLS:CMyDataEdit]
Type=0
HeaderFile=MyDataEdit.h
ImplementationFile=MyDataEdit.cpp
BaseClass=CEdit
Filter=W
VirtualFilter=WC

[CLS:CMyRepeatEdit]
Type=0
HeaderFile=MyRepeatEdit.h
ImplementationFile=MyRepeatEdit.cpp
BaseClass=CEdit
Filter=W
VirtualFilter=WC

[CLS:CColorPickerButton]
Type=0
HeaderFile=ColorPickerButton.h
ImplementationFile=ColorPickerButton.cpp
BaseClass=CButton
Filter=W
LastObject=CColorPickerButton
VirtualFilter=BWC

[DLG:IDD_DIALOG_COLOR]
Type=1
Class=CColorSelectDlg
ControlCount=36
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDOK,button,1342242816
Control4=IDCANCEL,button,1342242816
Control5=IDC_RADIO16,button,1342345225
Control6=IDC_RADIO17,button,1342214153
Control7=IDC_RADIO18,button,1342214153
Control8=IDC_RADIO19,button,1342214153
Control9=IDC_RADIO20,button,1342214153
Control10=IDC_RADIO21,button,1342214153
Control11=IDC_RADIO22,button,1342214153
Control12=IDC_RADIO23,button,1342214153
Control13=IDC_RADIO24,button,1342214153
Control14=IDC_RADIO25,button,1342214153
Control15=IDC_RADIO26,button,1342214153
Control16=IDC_RADIO27,button,1342214153
Control17=IDC_RADIO28,button,1342214153
Control18=IDC_RADIO29,button,1342214153
Control19=IDC_RADIO30,button,1342214153
Control20=IDC_BUTTON1,button,1342275595
Control21=IDC_BUTTON2,button,1342275584
Control22=IDC_BUTTON3,button,1342275584
Control23=IDC_BUTTON4,button,1342275584
Control24=IDC_BUTTON5,button,1342275584
Control25=IDC_BUTTON6,button,1342275584
Control26=IDC_BUTTON7,button,1342275584
Control27=IDC_BUTTON8,button,1342275584
Control28=IDC_BUTTON9,button,1342275584
Control29=IDC_BUTTON10,button,1342275584
Control30=IDC_BUTTON11,button,1342275584
Control31=IDC_BUTTON12,button,1342275584
Control32=IDC_BUTTON13,button,1342275584
Control33=IDC_BUTTON14,button,1342275584
Control34=IDC_BUTTON15,button,1342275584
Control35=IDC_STATIC_DEMO,static,1342308865
Control36=IDC_STATIC,static,1342308352

[CLS:CColorSelectDlg]
Type=0
HeaderFile=ColorSelectDlg.h
ImplementationFile=ColorSelectDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CColorSelectDlg

[CLS:CMyColorButton]
Type=0
HeaderFile=MyColorButton.h
ImplementationFile=MyColorButton.cpp
BaseClass=CButton
Filter=W
VirtualFilter=BWC

[CLS:CMyStatic]
Type=0
HeaderFile=MyStatic.h
ImplementationFile=MyStatic.cpp
BaseClass=CStatic
Filter=W
LastObject=CMyStatic
VirtualFilter=WC

