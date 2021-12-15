#if !defined(AFX_IPCoreCODEDOC_H__BBA1B9CF_A25E_4CD2_BBA3_6253E01855A9__INCLUDED_)
#define AFX_IPCoreCODEDOC_H__BBA1B9CF_A25E_4CD2_BBA3_6253E01855A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IPCorecodedoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIPCoreCodeDoc document

class CIPCoreCodeDoc : public CDocument
{
protected:
	CIPCoreCodeDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CIPCoreCodeDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIPCoreCodeDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CIPCoreCodeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CIPCoreCodeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPCoreCODEDOC_H__BBA1B9CF_A25E_4CD2_BBA3_6253E01855A9__INCLUDED_)
