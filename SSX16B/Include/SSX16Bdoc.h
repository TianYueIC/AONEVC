// SSX16BDoc.h : interface of the CSSX16BDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SSX16BDOC_H__3A0759C5_58E6_49B9_85B7_831A77C75269__INCLUDED_)
#define AFX_SSX16BDOC_H__3A0759C5_58E6_49B9_85B7_831A77C75269__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSourceView;
class CSSX16BDoc : public CDocument
{
	CFileStatus m_FileStatus;

protected: // create from serialization only
	CSSX16BDoc();
	DECLARE_DYNCREATE(CSSX16BDoc)
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSSX16BDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSSX16BDoc();
	void	CompileFile(int &total_error,int &total_warning);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CSourceView* GetSourceView();
	void UpdateDocFile();

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSSX16BDoc)
	afx_msg void OnMenuCompileAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SSX16BDOC_H__3A0759C5_58E6_49B9_85B7_831A77C75269__INCLUDED_)
