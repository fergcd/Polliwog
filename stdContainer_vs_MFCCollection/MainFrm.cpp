
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "stdContainer_vs_MFCCollection.h"

#include "MainFrm.h"

#include <chrono>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <list>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_STDCONTAINER_VECTOR, &CMainFrame::OnStdcontainerVector)
	ON_COMMAND(ID_STDCONTAINER_VECTOR_RESERVE, &CMainFrame::OnStdcontainerVectorReserve)
	ON_COMMAND(ID_STDCONTAINER_MAP, &CMainFrame::OnStdcontainerMap)
	ON_COMMAND(ID_STDCONTAINER_LIST, &CMainFrame::OnStdcontainerList)
	ON_COMMAND(ID_MFCCOLLECTION_CARRAY, &CMainFrame::OnMfccollectionCarray)
	ON_COMMAND(ID_MFCCOLLECTION_CARRAY_SETSIZE, &CMainFrame::OnMfccollectionCarraySetsize)
	ON_COMMAND(ID_MFCCOLLECTION_CMAP, &CMainFrame::OnMfccollectionCmap)
	ON_COMMAND(ID_MFCCOLLECTION_CLIST, &CMainFrame::OnMfccollectionClist)
	ON_COMMAND(ID_STDCONTAINER_UNORDERED_MAP, &CMainFrame::OnStdcontainerUnorderedMap)
	ON_COMMAND(ID_STDCONTAINER_SET, &CMainFrame::OnStdcontainerSet)
	ON_COMMAND(ID_STDCONTAINER_UNORDERED_SET, &CMainFrame::OnStdcontainerUnorderedSet)
	ON_COMMAND(ID_STDCONTAINER_UNORDERED_MAP_RESERVE, &CMainFrame::OnStdcontainerUnorderedMapReserve)
	ON_COMMAND(ID_STDCONTAINER_UNORDERED_SET_RESERVE, &CMainFrame::OnStdcontainerUnorderedSetReserve)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// create a view to occupy the client area of the frame
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// forward focus to the view window
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::OnStdcontainerVector()
{
	CString sMSG = _T("");

	std::vector<CString> svNames;
	INT_PTR nSize = svNames.capacity();
	CString sName = _T("");

	std::chrono::system_clock::time_point startTime;
	std::chrono::system_clock::time_point endTime;

	startTime = std::chrono::system_clock::now();
	for(INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{
		sName.Format(_T("%d"), nIndex);
		svNames.push_back(sName);
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("vector push_back 10000000번 수행 시간 : %g초"), (std::chrono::duration<double>)(endTime-startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime= std::chrono::system_clock::now();
	for(INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{		
		sName = svNames[nIndex];
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("vector 전체 원소 탐색 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime= std::chrono::system_clock::now();
	for(INT_PTR nIndex = 0; nIndex < 10; nIndex++)
	{
		svNames.insert(svNames.begin(), _T("10000000"));
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("vector 첫 번째 원소 자리에 원소 1개씩 10번 삽입 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime= std::chrono::system_clock::now();
	for(INT_PTR nIndex = 0; nIndex < 10; nIndex++)
	{
		svNames.erase(svNames.begin());
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("vector 첫 번째 자리에 있는 원소 1개씩 10번 삭제 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);
}

void CMainFrame::OnStdcontainerVectorReserve()
{
	CString sMSG = _T("");

	std::vector<CString> svNames;
	svNames.reserve(10000010);
	INT_PTR nSize = svNames.capacity();
	CString sName = _T("");

	std::chrono::system_clock::time_point startTime;
	std::chrono::system_clock::time_point endTime;

	startTime = std::chrono::system_clock::now();
	for(INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{
		sName.Format(_T("%d"), nIndex);
		svNames.push_back(sName);
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("vector reserve(10000010) 후 push_back 10000000번 수행 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime = std::chrono::system_clock::now();
	for(INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{		
		sName = svNames[nIndex];
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("vector(reserve수행) 전체 원소 탐색 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime = std::chrono::system_clock::now();
	for(INT_PTR nIndex = 0; nIndex < 10; nIndex++)
	{		
		svNames.insert(svNames.begin(), _T("10000000"));
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("vector(reserve수행) 첫 번째 원소 자리에 원소 1개씩 10번 삽입 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////	

	startTime= std::chrono::system_clock::now();
	for(INT_PTR nIndex = 0; nIndex < 10; nIndex++)
	{
		svNames.erase(svNames.begin());
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("vector(reserve수행) 첫 번째 자리에 있는 원소 1개씩 10번 삭제 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);
}

void CMainFrame::OnStdcontainerMap()
{
	CString sMSG = _T("");

	std::map<int, CString> smNames;	
	CString sName = _T("");

	std::chrono::system_clock::time_point startTime;
	std::chrono::system_clock::time_point endTime;

	startTime = std::chrono::system_clock::now();
	for(INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{
		sName.Format(_T("%d"), nIndex);
		smNames.insert(std::make_pair(nIndex, sName));
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("map insert 10000000번 수행 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime = std::chrono::system_clock::now();
	for(INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{		
		sName = smNames[nIndex];
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("map 전체 원소 탐색 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime = std::chrono::system_clock::now();
	for(INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{
		sName.Format(_T("%d"), nIndex + 10000000);
		smNames.insert(smNames.begin(), std::make_pair(nIndex + 10000000, sName));
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("map 원소 1개씩 10000000번 삽입 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime = std::chrono::system_clock::now();
	for(INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{
		smNames.erase(nIndex + 10000000);
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("map 원소 1개씩 10000000번 삭제 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);
}

void CMainFrame::OnStdcontainerUnorderedMap()
{
	CString sMSG = _T("");

	std::unordered_map<int, CString> sumNames;
	CString sName = _T("");

	std::chrono::system_clock::time_point startTime;
	std::chrono::system_clock::time_point endTime;

	startTime = std::chrono::system_clock::now();
	for (INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{
		sName.Format(_T("%d"), nIndex);
		sumNames.insert(std::make_pair(nIndex, sName));
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("unordered_map insert 10000000번 수행 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime = std::chrono::system_clock::now();
	for (INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{
		sName = sumNames[nIndex];
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("unordered_map 전체 원소 탐색 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime = std::chrono::system_clock::now();
	for (INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{
		sName.Format(_T("%d"), nIndex + 10000000);
		sumNames.insert(sumNames.begin(), std::make_pair(nIndex + 1000000, sName));
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("unordered_map 원소 1개씩 10000000번 삽입 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime = std::chrono::system_clock::now();
	for (INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{
		sumNames.erase(nIndex + 10000000);
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("unordered_map 원소 1개씩 10000000번 삭제 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);
}

void CMainFrame::OnStdcontainerUnorderedMapReserve()
{
	CString sMSG = _T("");

	std::unordered_map<int, CString> sumNames;
	sumNames.reserve(20000000);
	CString sName = _T("");

	std::chrono::system_clock::time_point startTime;
	std::chrono::system_clock::time_point endTime;

	startTime = std::chrono::system_clock::now();
	for (INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{
		sName.Format(_T("%d"), nIndex);
		sumNames.insert(std::make_pair(nIndex, sName));
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("unordered_map(reserve수행) insert 10000000번 수행 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime = std::chrono::system_clock::now();
	for (INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{
		sName = sumNames[nIndex];
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("unordered_map(reserve수행) 전체 원소 탐색 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime = std::chrono::system_clock::now();
	for (INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{
		sName.Format(_T("%d"), nIndex + 10000000);
		sumNames.insert(sumNames.begin(), std::make_pair(nIndex + 10000000, sName));
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("unordered_map(reserve수행) 원소 1개씩 10000000번 삽입 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime = std::chrono::system_clock::now();
	for (INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{
		sumNames.erase(nIndex + 10000000);
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("unordered_map(reserve수행) 원소 1개씩 10000000번 삭제 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);
}

void CMainFrame::OnStdcontainerSet()
{
	CString sMSG = _T("");

	std::set<CString> ssNames;
	CString sName = _T("");

	std::chrono::system_clock::time_point startTime;
	std::chrono::system_clock::time_point endTime;

	startTime = std::chrono::system_clock::now();
	for (INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{
		sName.Format(_T("%d"), nIndex);
		ssNames.insert(sName);
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("set insert 10000000번 수행 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////	

	startTime = std::chrono::system_clock::now();
	for (std::set<CString>::iterator it = ssNames.begin(); it != ssNames.end(); it++)
	{
		sName = *it;
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("set 전체 원소 탐색 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime = std::chrono::system_clock::now();
	for (INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{
		sName.Format(_T("%d"), nIndex + 10000000);
		ssNames.insert(sName);
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("set 원소 1개씩 10000000번 삽입 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime = std::chrono::system_clock::now();
	for (INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{
		ssNames.erase(ssNames.begin());
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("set 원소 1개씩 10000000번 삭제 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);
}

namespace std
{
	template <>
	struct hash<CString>
	{   // hash functor for CString
		size_t operator()(const CString& _Keyval) const
		{   // hash _Keyval to size_t value by pseudorandomizing transform
			return (_Hash_seq((const unsigned char*)(LPCWSTR)_Keyval, _Keyval.GetLength() * sizeof(wchar_t)));
		}
	};

	template <>
	struct hash<CStringA>
	{   // hash functor for CStringA
		size_t operator()(const CStringA& _Keyval) const
		{   // hash _Keyval to size_t value by pseudorandomizing transform
			return (_Hash_seq((const unsigned char*)(LPCSTR)_Keyval, _Keyval.GetLength() * sizeof(char)));
		}
	};
}

void CMainFrame::OnStdcontainerUnorderedSet()
{
	CString sMSG = _T("");

	std::unordered_set<CString, std::hash<CString>> susNames;	
	CString sName = _T("");

	std::chrono::system_clock::time_point startTime;
	std::chrono::system_clock::time_point endTime;

	startTime = std::chrono::system_clock::now();
	for (INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{
		sName.Format(_T("%d"), nIndex);
		susNames.insert(sName);
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("unordered_set insert 10000000번 수행 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime = std::chrono::system_clock::now();
	for (auto it = susNames.begin(); it != susNames.end(); it++)
	{
		sName = *it;
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("unordered_set 전체 원소 탐색 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime = std::chrono::system_clock::now();
	for (INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{
		sName.Format(_T("%d"), nIndex + 10000000);
		susNames.insert(sName);
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("unordered_set 원소 1개씩 10000000번 삽입 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime = std::chrono::system_clock::now();
	for (INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{
		susNames.erase(susNames.begin());
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("unordered_set 원소 1개씩 10000000번 삭제 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);
}

void CMainFrame::OnStdcontainerUnorderedSetReserve()
{
	CString sMSG = _T("");

	std::unordered_set<CString, std::hash<CString>> susNames;
	susNames.reserve(20000000);
	CString sName = _T("");

	std::chrono::system_clock::time_point startTime;
	std::chrono::system_clock::time_point endTime;

	startTime = std::chrono::system_clock::now();
	for (INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{
		sName.Format(_T("%d"), nIndex);
		susNames.insert(sName);
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("unordered_set(reserve수행) insert 10000000번 수행 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime = std::chrono::system_clock::now();
	for (auto it = susNames.begin(); it != susNames.end(); it++)
	{
		sName = *it;
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("unordered_set(reserve수행) 전체 원소 탐색 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime = std::chrono::system_clock::now();
	for (INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{
		sName.Format(_T("%d"), nIndex + 10000000);
		susNames.insert(sName);
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("unordered_set(reserve수행) 원소 1개씩 10000000번 삽입 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime = std::chrono::system_clock::now();
	for (INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{
		susNames.erase(susNames.begin());
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("unordered_set(reserve수행) 원소 1개씩 10000000번 삭제 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);
}

void CMainFrame::OnStdcontainerList()
{
	CString sMSG = _T("");

	std::list<CString> slistNames;
	CString sName = _T("");

	std::chrono::system_clock::time_point startTime;
	std::chrono::system_clock::time_point endTime;

	startTime = std::chrono::system_clock::now();
	for(INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{
		sName.Format(_T("%d"), nIndex);
		slistNames.push_back(sName);
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("list push_back 10000000번 수행 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////	 

	startTime = std::chrono::system_clock::now();
	for(std::list<CString>::iterator it = slistNames.begin(); it != slistNames.end(); it++)
	{		
		sName = *it;
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("list 전체 원소 탐색 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);


	//////////

	startTime = std::chrono::system_clock::now();
	for(INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{
		slistNames.insert(slistNames.begin(), _T("10000000"));
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("list 원소 1개씩 10000000번 삽입 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime = std::chrono::system_clock::now();
	for(INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{
		slistNames.erase(slistNames.begin());
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("list 원소 삭제 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);
}

void CMainFrame::OnMfccollectionCarray()
{
	CString sMSG = _T("");

	CArray<CString> saNames;
	CString sName = _T("");

	std::chrono::system_clock::time_point startTime;
	std::chrono::system_clock::time_point endTime;

	startTime = std::chrono::system_clock::now();
	for(INT_PTR nIndex = 0; nIndex < 4000000; nIndex++)
	{
		sName.Format(_T("%d"), nIndex);
		saNames.Add(sName);
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("CArray Add 4000000번 수행 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime = std::chrono::system_clock::now();
	for(INT_PTR nIndex = 0; nIndex < 4000000; nIndex++)
	{		
		sName = saNames[nIndex];
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("CArray 전체 원소 탐색 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime = std::chrono::system_clock::now();
	for(INT_PTR nIndex = 0; nIndex < 1000; nIndex++)
	{
		saNames.InsertAt(0, _T("1000000"));
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("CArray 원소 1000개 삽입 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime = std::chrono::system_clock::now();
	for(INT_PTR nIndex = 0; nIndex < 1000; nIndex++)
	{
		saNames.RemoveAt(0);
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("CArray 원소 1000개 삭제 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);
}

void CMainFrame::OnMfccollectionCarraySetsize()
{
	CString sMSG = _T("");

	CArray<CString> saNames;
	saNames.SetSize(0, 20000000);
	saNames.Add(_T(""));
	saNames.RemoveAt(0);
	CString sName = _T("");

	std::chrono::system_clock::time_point startTime;
	std::chrono::system_clock::time_point endTime;

	startTime = std::chrono::system_clock::now();
	for(INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{
		sName.Format(_T("%d"), nIndex);
		saNames.Add(sName);
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("CArray SetSize(20000000) 후 SetAt 10000000번 수행 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime = std::chrono::system_clock::now();
	for(INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{		
		sName = saNames[nIndex];
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("CArray(SetSize) 전체 원소 탐색 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime = std::chrono::system_clock::now();
	for(INT_PTR nIndex = 0; nIndex < 1000; nIndex++)
	{		
		saNames.InsertAt(0, _T("10000000"));
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("CArray(SetSize) 원소 1000개 삽입 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime = std::chrono::system_clock::now();
	for(INT_PTR nIndex = 0; nIndex < 1000; nIndex++)
	{
		saNames.RemoveAt(0);
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("CArray(SetSize) 원소 1000개 삭제 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);
}

void CMainFrame::OnMfccollectionCmap()
{
	CString sMSG = _T("");

	CMap<int, int, CString, CString> smNames;
	smNames.InitHashTable(20000000);
	CString sName = _T("");
	
	std::chrono::system_clock::time_point startTime;
	std::chrono::system_clock::time_point endTime;

	startTime = std::chrono::system_clock::now();
	for(INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{
		sName.Format(_T("%d"), nIndex);
		smNames.SetAt(nIndex, sName);
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("CMap SetAt 10000000번 수행 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime = std::chrono::system_clock::now();
	for(INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{		
		sName = smNames[nIndex];
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("CMap 전체 원소 탐색 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime = std::chrono::system_clock::now();
	for(INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{
		sName.Format(_T("%d"), nIndex + 10000000);
		smNames.SetAt(nIndex + 10000000, sName);
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("CMap 원소 10000000개 삽입 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime = std::chrono::system_clock::now();
	for(INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{
		smNames.RemoveKey(nIndex + 10000000);
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("CMap 원소 10000000개 삭제 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);
}

void CMainFrame::OnMfccollectionClist()
{
	CString sMSG = _T("");

	CList<CString> slistNames;
	CString sName = _T("");

	std::chrono::system_clock::time_point startTime;
	std::chrono::system_clock::time_point endTime;

	startTime = std::chrono::system_clock::now();
	for (INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{
		sName.Format(_T("%d"), nIndex);
		slistNames.AddTail(sName);
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("CList AddTail 10000000번 수행 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	POSITION pos = slistNames.GetHeadPosition();

	startTime = std::chrono::system_clock::now();
	while (pos != NULL)
	{
		sName = slistNames.GetNext(pos);
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("CList 전체 원소 탐색 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);


	//////////

	startTime = std::chrono::system_clock::now();
	for (INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{
		sName.Format(_T("%d"), nIndex + 10000000);
		slistNames.InsertAfter(slistNames.GetHeadPosition(), sName);
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("CList 원소 10000000개 삽입 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);

	//////////

	startTime = std::chrono::system_clock::now();
	for (INT_PTR nIndex = 0; nIndex < 10000000; nIndex++)
	{
		slistNames.RemoveAt(slistNames.GetHeadPosition());
	}
	endTime = std::chrono::system_clock::now();
	sMSG.Format(_T("CList 원소 10000000개 삭제 시간 : %g초"), (std::chrono::duration<double>)(endTime - startTime));
	AfxMessageBox(sMSG);
}