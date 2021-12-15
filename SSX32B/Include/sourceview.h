#if !defined(AFX_SOURCEVIEW_H__E50CA494_BDE4_4AEF_8713_7376D066B760__INCLUDED_)
#define AFX_SOURCEVIEW_H__E50CA494_BDE4_4AEF_8713_7376D066B760__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SourceView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSourceView view

class CSourceView : public CLineView
{
	CStringArray	m_SrcFile;
protected:
	CSourceView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSourceView)

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

virtual void DrawLine(CDC& dc,CRect& rect,int line);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSourceView)
	protected:
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSourceView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CSourceView)
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

#endif // !defined(AFX_SOURCEVIEW_H__E50CA494_BDE4_4AEF_8713_7376D066B760__INCLUDED_)
