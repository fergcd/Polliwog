
// stdContainer_vs_MFCCollection.h : main header file for the stdContainer_vs_MFCCollection application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CstdContainer_vs_MFCCollectionApp:
// See stdContainer_vs_MFCCollection.cpp for the implementation of this class
//

class CstdContainer_vs_MFCCollectionApp : public CWinApp
{
public:
	CstdContainer_vs_MFCCollectionApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CstdContainer_vs_MFCCollectionApp theApp;
