#if !defined(AFX_WATCHVIEW_H__D0881F4F_9F78_44D8_B343_7A8C8C097CA2__INCLUDED_)
#define AFX_WATCHVIEW_H__D0881F4F_9F78_44D8_B343_7A8C8C097CA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// watchview.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWatchView view
class CDSPMap;
class CWatchView : public CLineView
{
	CRect m_RectName,m_RectValue;
	CRect   m_MouseHotRect;
	int		m_iOldTrace;
	BOOL	m_bCursorSeted;
	BOOL	m_bLButtonDown;
	CSize m_SizeView;
	CStringList m_VarNameList;
	CEdit	m_Edit;
	int		m_iEditIndex;
	CDSPMap* m_pMap;
	CDSPMap* m_pOldMap;
protected:
	CWatchView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CWatchView)

// Attributes
public:

// Operations
public:
	void DrawGridding(CDC* pDC);
	void DrawTitle(CDC* pDC);
	int	 GetIndexByPoint(CPoint& pt);
	void ShowEdit();
	void AddWatchItem(CString &strVarname);
	void UpdateWatchItem(CString &strVarname,int index);
	void UpdateWatchItem();
	void SetDSPMap(CDSPMap* pMap,CDSPMap* pOldMap){m_pMap = pMap;m_pOldMap = pOldMap;}
	void InvertTracker(int x);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWatchView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL
	afx_msg void OnEditKillFocus(NMHDR*,LRESULT*);      

// Implementation
protected:
	virtual ~CWatchView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CWatchView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WATCHVIEW_H__D0881F4F_9F78_44D8_B343_7A8C8C097CA2__INCLUDED_)
