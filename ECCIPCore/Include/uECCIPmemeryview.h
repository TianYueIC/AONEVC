#if !defined(__UECCIPMEMERYVIEW_H__)
#define __UECCIPMEMERYVIEW_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// hashmemeryview.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHashMemeryView view

class CuECCIPMap;

class CuECCIPMemeryView : public CLineView
{
	int m_iCols;
	CuECCIPMap * m_pMap;
	CuECCIPMap* m_pOldMap;
	virtual void DrawLine(CDC& dc,CRect& rect,int line);
protected:
	CuECCIPMemeryView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CuECCIPMemeryView)
// Attributes
public:

// Operations
public:
	void SetMap(CuECCIPMap* pMap,CuECCIPMap* pOldMap);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CuECCIPMemeryView)
	protected:
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CuECCIPMemeryView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CHashMemeryView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(__HASHMEMERYVIEW_H__)
