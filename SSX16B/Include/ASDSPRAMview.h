#if !defined(__ASDSPRAMVIEW_H__)
#define __ASDSPRAMVIEW_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ASDSPRAMview.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHashMemeryView view

class CDSPMap;

class CASDSPRAMView : public CLineView
{
	int m_iCols;
	CDSPMap * m_pMap;
	CDSPMap* m_pOldMap;
	virtual void DrawLine(CDC& dc,CRect& rect,int line);
protected:
	CASDSPRAMView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CASDSPRAMView)
// Attributes
public:
virtual void	DumpData(FILE *fp);
// Operations
public:
	void SetDSPMap(CDSPMap* pMap,CDSPMap* pOldMap);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CASDSPRAMView)
	protected:
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CASDSPRAMView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CASDSPRAMView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(__ASDSPRAMVIEW_H__)
