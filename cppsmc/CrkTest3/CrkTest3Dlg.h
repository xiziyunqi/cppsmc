// CrkTest3Dlg.h : header file
//

#if !defined(AFX_CRKTEST3DLG_H__5ED37501_6905_4055_BBC4_BD9D73A0B5A4__INCLUDED_)
#define AFX_CRKTEST3DLG_H__5ED37501_6905_4055_BBC4_BD9D73A0B5A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCrkTest3Dlg dialog

class CCrkTest3Dlg : public CDialog
{
// Construction
public:
	CCrkTest3Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCrkTest3Dlg)
	enum { IDD = IDD_CRKTEST3_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCrkTest3Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCrkTest3Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnAbout();
	afx_msg void OnBtnCallfunc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRKTEST3DLG_H__5ED37501_6905_4055_BBC4_BD9D73A0B5A4__INCLUDED_)
