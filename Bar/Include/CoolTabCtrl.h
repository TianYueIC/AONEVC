////////////////////////////////////////////////////////////////
// CoolTabCtrl.h : header file                                //
//															  //
// Copyright 2001 WangJun									  //
// All Rights Reserved.										  //
//															  //
// Email: wangjun98@sohu.com								  //
// URL:   www.vckbase.com									  //
//															  //
// 1.0     2001/9/30   First release version.				  //
//															  //
////////////////////////////////////////////////////////////////

#ifndef CCoolTabCtrl_h
#define CCoolTabCtrl_h

#define TCS_UP		0x0001		///向上
#define TCS_DOWN		0x0002		///向下
#define TCS_MONOSPACE	0x0004		///等宽效果
#define TCS_ANIMATE	0x0008		///窗口拉动的动画效果
#define TCS_MASK		0x000f		///掩码:所有类型值相"或",供程序内部使用

class CCoolTabCtrl : public CWnd
{
public:
	class CPageItem
	{
		friend class CCoolTabCtrl;

		CWnd*		m_pWnd;		///窗口,可以为NULL
		UINT		m_nStyle;	///窗口类型，0:普通，1:对话框
		CString		m_sText;	///文字
		HICON		m_hIcon;	///图标
	public:
		CRect		m_rect;		
	public:
		CWnd* GetPageWnd(){return m_pWnd;};
		UINT GetAreaWidth(CDC *pDC);
		void Draw(CDC *pDC,UINT nStyle,BOOL bActive);

	};
	DECLARE_DYNCREATE(CCoolTabCtrl)
public:
	CCoolTabCtrl();

public:
	void SetStyleMonoSpace(BOOL bEnable = TRUE);
	void SetStyleDirection(int Direction);		///Direction取值:TCS_UP,TCS_DOWN
	void SetStyleAnimate(BOOL bEnable = TRUE);	///允许动画bEnable = TRUE,否则为FALSE
	void UpdateWindow();
	BOOL m_bEraseBkgnd;
	UINT GetStyle();
	void SetStyle(UINT style);
	void DrawFrame(CDC *pDC);
	void* GetPageItem(UINT nIndex);
	void SetActivePage(int nIndex);
	BOOL AddPage(CRuntimeClass* pClass,UINT nIDTemplate,LPCTSTR sText,UINT IconID = NULL);
	void AddPage(CWnd *pWnd,LPCTSTR sText,UINT IconID = NULL);
	void AutoSize();
	void GetClientRect(LPRECT lpRect );
	BOOL Create(UINT wStyle, const CRect & rect, CWnd * pParentWnd, UINT nID);
	virtual ~CCoolTabCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCoolTabCtrl)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CFont		m_font;
	int			m_nActivePage;
	UINT		m_nStyle;
	UINT		m_nBorder;
	CPtrList	m_PageList;
};
#endif //CCoolTabCtrl_h