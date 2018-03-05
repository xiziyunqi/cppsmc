// CrkTest2Dlg.h : header file
//

#if !defined(AFX_CRKTEST2DLG_H__65E42E6C_E9CF_4EF1_9694_91F385659B90__INCLUDED_)
#define AFX_CRKTEST2DLG_H__65E42E6C_E9CF_4EF1_9694_91F385659B90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCrkTest2Dlg dialog

class CCrkTest2Dlg : public CDialog
{
// Construction
public:
	CCrkTest2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCrkTest2Dlg)
	enum { IDD = IDD_CRKTEST2_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCrkTest2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCrkTest2Dlg)
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

#endif // !defined(AFX_CRKTEST2DLG_H__65E42E6C_E9CF_4EF1_9694_91F385659B90__INCLUDED_)
