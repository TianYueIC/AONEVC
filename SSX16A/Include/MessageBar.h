// DebugBar.h: interface for the CMessageBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_MESSAGEBAR_H_)
#define _MESSAGEBAR_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "..\..\bar\include\bar.h"

class CMessageBar : public CCoolBar  
{
	DECLARE_DYNAMIC(CMessageBar)
public:
	CMessageBar();
	virtual ~CMessageBar();
	CEdit m_Edit;
public:
	void AddMessage(CString &str);
	void ClearMessage();
//	long DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_DEBUGBAR_H__2D08A271_ACAE_42A9_B7BB_AA173D86A92F__INCLUDED_)
