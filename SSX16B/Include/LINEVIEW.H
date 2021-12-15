#if !defined(AFX_LINEVIEW_H__E0B4B384_86B2_4EE6_B9C8_3C510D0530A9__INCLUDED_)
#define AFX_LINEVIEW_H__E0B4B384_86B2_4EE6_B9C8_3C510D0530A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LineView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLineView view

class CLineView : public CView
{
protected:
	BOOL m_bOnFocus;
	CRect	m_Rect;
	int		m_iTotalLine, m_iFirstLine, m_iLineSize, m_iCursorLine;
	int		m_iCharWidth;
	int		m_iCharHeight;
	CLineView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CLineView)

// Attributes
public:

// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLineView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CLineView();
	void SetScrollState();
virtual void	DumpData(FILE *fp);
	void GotoLine(int line);

	virtual void DrawLine(CDC& dc,CRect& rect,int line);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CLineView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINEVIEW_H__E0B4B384_86B2_4EE6_B9C8_3C510D0530A9__INCLUDED_)
