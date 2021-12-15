#if !defined(__HASHMEMERYVIEW_H__)
#define __HASHMEMERYVIEW_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// hashmemeryview.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHashMemeryView view

class CHashMap;

class CHashMemeryView : public CLineView
{
	int m_iCols;
	CHashMap * m_pMap;
	CHashMap* m_pOldMap;
	int		m_iMemerySize;
protected:
	CHashMemeryView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CHashMemeryView)
// Attributes
public:

// Operations
public:
	void SetHashMap(CHashMap* pMap,CHashMap* pOldMap);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHashMemeryView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CHashMemeryView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CHashMemeryView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(__HASHMEMERYVIEW_H__)
