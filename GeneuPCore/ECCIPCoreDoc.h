// ECCIPCoreDoc.h : interface of the CECCIPCoreDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ECCIPCOREDOC_H__395A2CD2_7E04_4308_A675_381B10CAFC80__INCLUDED_)
#define AFX_ECCIPCOREDOC_H__395A2CD2_7E04_4308_A675_381B10CAFC80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CuECCIPSourceView;
class CECCIPCoreDoc : public CDocument
{
protected: // create from serialization only
	CECCIPCoreDoc();
	DECLARE_DYNCREATE(CECCIPCoreDoc)
	CFileStatus m_FileStatus;
// Attributes
public:
CuECCIPSourceView* GetSourceViewView();
	void UpdateDocFile();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CECCIPCoreDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CECCIPCoreDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CECCIPCoreDoc)
	afx_msg void OnMenuCompileFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ECCIPCOREDOC_H__395A2CD2_7E04_4308_A675_381B10CAFC80__INCLUDED_)
