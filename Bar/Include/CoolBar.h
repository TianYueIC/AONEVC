//CoolBar.h
#ifndef CCoolBar_h
#define CCoolBar_h

class CCoolBar : public CSizingControlBar
{
	DECLARE_DYNAMIC(CCoolBar);
public:
	CCoolBar();
	virtual BOOL HasGripper() const;
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
public:
	virtual ~CCoolBar();
	
protected:
	// implementation helpers
	virtual void NcPaintGripper(CDC* pDC, CRect rcClient);
	virtual void NcCalcClient(LPRECT pRc, UINT nDockBarID);
	
protected:
	int     m_cyGripper;
	CSCBButton m_biHide;
	BOOL    m_bActive; // a child has focus
	CString m_sFontFace;
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CCoolBar)
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

#endif //CCoolBar_h