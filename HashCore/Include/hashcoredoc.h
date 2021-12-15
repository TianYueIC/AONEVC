// HashCoreDoc.h : interface of the CHashCoreDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HASHCOREDOC_H__7998FF86_6432_4C4C_B603_03E8271C0BD2__INCLUDED_)
#define AFX_HASHCOREDOC_H__7998FF86_6432_4C4C_B603_03E8271C0BD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHashSourceView;
class CHashCoreDoc : public CDocument
{
	CFileStatus m_FileStatus;
	
protected: // create from serialization only
	CHashCoreDoc();
	DECLARE_DYNCREATE(CHashCoreDoc)
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHashCoreDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHashCoreDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CHashSourceView* GetSourceViewView();
	void UpdateDocFile();

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHashCoreDoc)
	afx_msg void OnMenuCompileFile();
	afx_msg void OnUpdateMenuCompileFile(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HASHCOREDOC_H__7998FF86_6432_4C4C_B603_03E8271C0BD2__INCLUDED_)
