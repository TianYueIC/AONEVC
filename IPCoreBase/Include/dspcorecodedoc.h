#if !defined(AFX_DSPCORECODEDOC_H__BBA1B9CF_A25E_4CD2_BBA3_6253E01855A9__INCLUDED_)
#define AFX_DSPCORECODEDOC_H__BBA1B9CF_A25E_4CD2_BBA3_6253E01855A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dspcorecodedoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDSPCoreCodeDoc document

class CDSPCoreCodeDoc : public CDocument
{
protected:
	CDSPCoreCodeDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDSPCoreCodeDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDSPCoreCodeDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDSPCoreCodeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CDSPCoreCodeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSPCORECODEDOC_H__BBA1B9CF_A25E_4CD2_BBA3_6253E01855A9__INCLUDED_)
