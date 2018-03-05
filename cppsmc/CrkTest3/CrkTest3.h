// CrkTest3.h : main header file for the CRKTEST3 application
//

#if !defined(AFX_CRKTEST3_H__A8B4A368_3614_4703_97EE_6785F46CF3C0__INCLUDED_)
#define AFX_CRKTEST3_H__A8B4A368_3614_4703_97EE_6785F46CF3C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCrkTest3App:
// See CrkTest3.cpp for the implementation of this class
//

class CCrkTest3App : public CWinApp
{
public:
	CCrkTest3App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCrkTest3App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCrkTest3App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRKTEST3_H__A8B4A368_3614_4703_97EE_6785F46CF3C0__INCLUDED_)
