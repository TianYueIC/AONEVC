#if !defined(__UECCIPSOURCEVIEW_H__)
#define __UECCIPSOURCEVIEW_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HashSourceView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHashSourceView view
#include "..\Include\LineView.h"
class CuECCIPSourceView : public CLineView
{
	CStringArray	m_SrcFile;
protected:
	CuECCIPSourceView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CuECCIPSourceView)

// Attributes
public:
	int	m_iFileIndex;
// Operations
public:
	void DrawExecutePoint(CDC *pDC);
	void DrawBreakPoint(CDC *pDC);
	void ReadFile(FILE*fp);
	void SetFileIndex(int index){m_iFileIndex = index;}
	void UpdateFirstLine();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CuECCIPSourceView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CuECCIPSourceView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CHashSourceView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMenuBreakPoint();
	afx_msg void OnUpdateMenuBreakPoint(CCmdUI* pCmdUI);
	afx_msg void OnMenuGotoCursor();
	afx_msg void OnUpdateMenuGotoCursor(CCmdUI* pCmdUI);
	afx_msg void OnMenuGotoLine();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(__HASHSOURCEVIEW_H__)
