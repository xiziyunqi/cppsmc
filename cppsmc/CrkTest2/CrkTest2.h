// CrkTest2.h : main header file for the CRKTEST2 application
//

#if !defined(AFX_CRKTEST2_H__A639487B_5B28_4984_9982_D49CD8E4FEE9__INCLUDED_)
#define AFX_CRKTEST2_H__A639487B_5B28_4984_9982_D49CD8E4FEE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCrkTest2App:
// See CrkTest2.cpp for the implementation of this class
//

class CCrkTest2App : public CWinApp
{
public:
	CCrkTest2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCrkTest2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCrkTest2App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRKTEST2_H__A639487B_5B28_4984_9982_D49CD8E4FEE9__INCLUDED_)
