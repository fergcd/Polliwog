
// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "ChildView.h"

class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar        m_wndStatusBar;
	CChildView    m_wndView;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnStdcontainerVector();
	afx_msg void OnStdcontainerVectorReserve();
	afx_msg void OnStdcontainerMap();
	afx_msg void OnStdcontainerUnorderedMap();
	afx_msg void OnStdcontainerUnorderedMapReserve();
	afx_msg void OnStdcontainerSet();
	afx_msg void OnStdcontainerUnorderedSet();
	afx_msg void OnStdcontainerUnorderedSetReserve();
	afx_msg void OnStdcontainerList();	
	afx_msg void OnMfccollectionCarray();
	afx_msg void OnMfccollectionCarraySetsize();
	afx_msg void OnMfccollectionCmap();
	afx_msg void OnMfccollectionClist();
};