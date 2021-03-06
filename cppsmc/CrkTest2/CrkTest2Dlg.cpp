// CrkTest2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "CrkTest2.h"
#include "CrkTest2Dlg.h"
#include "specfunc.h"
#include "ProtectFunc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment(linker, "/SECTION:.text,ERW")

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

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if(::GetKeyState(VK_LCONTROL) & 0x8000)
	{
		GetDlgItem(IDC_STC_ADDR)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STC_SIZE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_CODE_START)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_CODE_SIZE)->ShowWindow(SW_SHOW);

		//此处的代码只能工作在Release版本，Debug版本需要修正函数地址，具体请参考本文第二节给出的方法
		int nStartPos = FindCodeTag((void *)CalcRegCode,&slStartSignVar,0x5A5A5A5A,1000);
		if(nStartPos != -1)
		{
			nStartPos += nMovCodeLength;
			int nEndPos = FindCodeTag((void *)CalcRegCode,&slEndSignVar,0x61616161,1000);
			if(nEndPos != -1)
			{
				int nSize = nEndPos - nStartPos;
				char *pCodeStart = (char *)CalcRegCode;
				pCodeStart += nStartPos;
				
				int nFileOffset = VAtoFileOffset((void *)::GetModuleHandle(NULL),(void *)pCodeStart);
				TCHAR szCodeAddr[128];
				wsprintf(szCodeAddr,_T("CodeAddr = 0x%x , File Offset = %d"),(void *)pCodeStart,nFileOffset);
				SetDlgItemText(IDC_EDIT_CODE_START,szCodeAddr);

				SetDlgItemInt(IDC_EDIT_CODE_SIZE,nSize);
			}
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// CCrkTest2Dlg dialog

CCrkTest2Dlg::CCrkTest2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCrkTest2Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCrkTest2Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCrkTest2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCrkTest2Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCrkTest2Dlg, CDialog)
	//{{AFX_MSG_MAP(CCrkTest2Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ABOUT, OnBtnAbout)
	ON_BN_CLICKED(IDC_BTN_CALLFUNC, OnBtnCallfunc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCrkTest2Dlg message handlers

BOOL CCrkTest2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

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
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCrkTest2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCrkTest2Dlg::OnPaint() 
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
HCURSOR CCrkTest2Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCrkTest2Dlg::OnBtnAbout() 
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CCrkTest2Dlg::OnBtnCallfunc() 
{
	TCHAR szBuff[128];
	try
	{
		//此处的代码只能工作在Release版本，Debug版本需要修正函数地址，具体请参考本文第二节给出的方法
		int nStartPos = FindCodeTag((void *)CalcRegCode,&slStartSignVar,0x5A5A5A5A,1000);
		if(nStartPos != -1)
		{
			nStartPos += nMovCodeLength;
			int nEndPos = FindCodeTag((void *)CalcRegCode,&slEndSignVar,0x61616161,1000);
			if(nEndPos != -1)
			{
				int nSize = nEndPos - nStartPos;
				char *pCodeStart = (char *)CalcRegCode;
				pCodeStart += nStartPos;

				//注意，解密和加密函数也是重要的函数，这两个函数的调用最好放在距离CalcRegCode()函数调用
				//远一点的位置，避免被发现
				DecryptBlock(pCodeStart,nSize,0x5A);//首先解密代码段

				CalcRegCode("system",szBuff,128);//调用注册码计算函数
				
				EncryptBlock(pCodeStart,nSize,0x5A);//调用后加密代码段

				::MessageBox(NULL,szBuff,_T("OK"),MB_OK);
			}
		}
	}
	catch(const char *pszError)
	{
		//处理代码段查找异常
		::MessageBox(NULL,pszError,_T("Error"),MB_OK);
	}
	catch(...)
	{
		//处理其它异常，比如对代码修改或加密不正确造成的异常
		::MessageBox(NULL,_T("Unknown exception"),_T("Error"),MB_OK);
	}
	
	
}

