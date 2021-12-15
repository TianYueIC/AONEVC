// DSPCoreDoc.h : interface of the CDSPCoreDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DSPCOREDOC_H__3A0759C5_58E6_49B9_85B7_831A77C75269__INCLUDED_)
#define AFX_DSPCOREDOC_H__3A0759C5_58E6_49B9_85B7_831A77C75269__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSourceView;
class CDSPCoreDoc : public CDocument
{
	CFileStatus m_FileStatus;

protected: // create from serialization only
	CDSPCoreDoc();
	DECLARE_DYNCREATE(CDSPCoreDoc)
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDSPCoreDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDSPCoreDoc();
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
	//{{AFX_MSG(CDSPCoreDoc)
	afx_msg void OnMenuCompileAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSPCOREDOC_H__3A0759C5_58E6_49B9_85B7_831A77C75269__INCLUDED_)
