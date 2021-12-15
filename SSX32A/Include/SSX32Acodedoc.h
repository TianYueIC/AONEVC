#if !defined(AFX_SSX32ACODEDOC_H__BBA1B9CF_A25E_4CD2_BBA3_6253E01855A9__INCLUDED_)
#define AFX_SSX32ACODEDOC_H__BBA1B9CF_A25E_4CD2_BBA3_6253E01855A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SSX32Acodedoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSSX32ACodeDoc document

class CSSX32ACodeDoc : public CDocument
{
protected:
	CSSX32ACodeDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSSX32ACodeDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSSX32ACodeDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSSX32ACodeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CSSX32ACodeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SSX32ACODEDOC_H__BBA1B9CF_A25E_4CD2_BBA3_6253E01855A9__INCLUDED_)
