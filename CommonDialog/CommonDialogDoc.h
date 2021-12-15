// CommonDialogDoc.h : interface of the CCommonDialogDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMONDIALOGDOC_H__2925E9D4_FE96_4169_B087_292A38E7234F__INCLUDED_)
#define AFX_COMMONDIALOGDOC_H__2925E9D4_FE96_4169_B087_292A38E7234F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCommonDialogDoc : public CDocument
{
protected: // create from serialization only
	CCommonDialogDoc();
	DECLARE_DYNCREATE(CCommonDialogDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommonDialogDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCommonDialogDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCommonDialogDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMONDIALOGDOC_H__2925E9D4_FE96_4169_B087_292A38E7234F__INCLUDED_)
