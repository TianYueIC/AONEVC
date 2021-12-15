#if !defined(AFX_DSPCOREMAKE_H__5B28FA03_6044_4363_A934_D9A4FCEB2D1E__INCLUDED_)
#define AFX_DSPCOREMAKE_H__5B28FA03_6044_4363_A934_D9A4FCEB2D1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dspcoremake.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDSPCoreMake document

class CDSPCoreMake : public CDocument
{
protected:
	CDSPCoreMake();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDSPCoreMake)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDSPCoreMake)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDSPCoreMake();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CDSPCoreMake)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSPCOREMAKE_H__5B28FA03_6044_4363_A934_D9A4FCEB2D1E__INCLUDED_)
