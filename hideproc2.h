// hideproc2.h : main header file for the HIDEPROC2 application
//

#if !defined(AFX_HIDEPROC2_H__EE26027F_5A6B_4E14_818B_90FD1DDF6B27__INCLUDED_)
#define AFX_HIDEPROC2_H__EE26027F_5A6B_4E14_818B_90FD1DDF6B27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHideproc2App:
// See hideproc2.cpp for the implementation of this class
//

class CHideproc2App : public CWinApp
{
public:
	CHideproc2App();
    virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHideproc2App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HIDEPROC2_H__EE26027F_5A6B_4E14_818B_90FD1DDF6B27__INCLUDED_)
