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

#define TCS_UP		0x0001		///����
#define TCS_DOWN		0x0002		///����
#define TCS_MONOSPACE	0x0004		///�ȿ�Ч��
#define TCS_ANIMATE	0x0008		///���������Ķ���Ч��
#define TCS_MASK		0x000f		///����:��������ֵ��"��",�������ڲ�ʹ��

class CCoolTabCtrl : public CWnd
{
public:
	class CPageItem
	{
		friend class CCoolTabCtrl;

		CWnd*		m_pWnd;		///����,����ΪNULL
		UINT		m_nStyle;	///�������ͣ�0:��ͨ��1:�Ի���
		CString		m_sText;	///����
		HICON		m_hIcon;	///ͼ��
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
	void SetStyleDirection(int Direction);		///Directionȡֵ:TCS_UP,TCS_DOWN
	void SetStyleAnimate(BOOL bEnable = TRUE);	///������bEnable = TRUE,����ΪFALSE
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