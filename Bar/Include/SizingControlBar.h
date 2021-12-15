//SizingControlBar.h

#ifndef CSizingControlBar_h
#define CSizingControlBar_h

#include <afxtempl.h>


#define SCBS_EDGELEFT       0x00000001
#define SCBS_EDGERIGHT      0x00000002
#define SCBS_EDGETOP        0x00000004
#define SCBS_EDGEBOTTOM     0x00000008
#define SCBS_EDGEALL        0x0000000F
#define SCBS_SHOWEDGES      0x00000010
#define SCBS_SIZECHILD      0x00000020

class CSizingControlBar;
typedef CTypedPtrArray <CPtrArray, CSizingControlBar*> CSCBArray;

class CSizingControlBar : public CControlBar
{
	DECLARE_DYNAMIC(CSizingControlBar);
	
	// Construction
public:
	CSizingControlBar();
	
	virtual BOOL Create(LPCTSTR lpszWindowName, CWnd* pParentWnd,
		CSize sizeDefault, BOOL bHasGripper,
		UINT nID, DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP);
	virtual BOOL Create(LPCTSTR lpszWindowName, CWnd* pParentWnd,
		UINT nID, DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP);
	
	// Attributes
public:
	const BOOL IsFloating() const;
	const BOOL IsHorzDocked() const;
	const BOOL IsVertDocked() const;
	const BOOL IsSideTracking() const;
	const BOOL GetSCBStyle() const {return m_dwSCBStyle;}
public:
#if defined(_SCB_REPLACE_MINIFRAME) && !defined(_SCB_MINIFRAME_CAPTION)
	void EnableDocking(DWORD dwDockStyle);
#endif
	virtual void LoadState(LPCTSTR lpszProfileName);
	virtual void SaveState(LPCTSTR lpszProfileName);
	static void GlobalLoadState(CFrameWnd* pFrame, LPCTSTR lpszProfileName);
	static void GlobalSaveState(CFrameWnd* pFrame, LPCTSTR lpszProfileName);
	void SetSCBStyle(DWORD dwSCBStyle)
		{m_dwSCBStyle = (dwSCBStyle & ~SCBS_EDGEALL);}
	
	// Overridables
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSizingControlBar)
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	virtual CSize CalcDynamicLayout(int nLength, DWORD dwMode);
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CSizingControlBar();
	
protected:
	UINT GetEdgeHTCode(int nEdge);
	BOOL GetEdgeRect(CRect rcWnd, UINT nHitTest, CRect& rcEdge);
	virtual void StartTracking(UINT nHitTest, CPoint point);
	virtual void StopTracking();
	virtual void OnTrackUpdateSize(CPoint& point);
	virtual void OnTrackInvertTracker();
	virtual void NcPaintGripper(CDC* pDC, CRect rcClient);
	virtual void NcCalcClient(LPRECT pRc, UINT nDockBarID);
	virtual void AlignControlBars();
	void GetRowInfo(int& nFirst, int& nLast, int& nThis);
	void GetRowSizingBars(CSCBArray& arrSCBars);
	void GetRowSizingBars(CSCBArray& arrSCBars, int& nThis);
	BOOL NegotiateSpace(int nLengthTotal, BOOL bHorz);
	
protected:
	DWORD   m_dwSCBStyle;
	UINT    m_htEdge;
	
	CSize   m_szHorz;
	CSize   m_szVert;
	CSize   m_szFloat;
	CSize   m_szMinHorz;
	CSize   m_szMinVert;
	CSize   m_szMinFloat;
	int     m_nTrackPosMin;
	int     m_nTrackPosMax;
	int     m_nTrackPosOld;
	int     m_nTrackEdgeOfs;
	BOOL    m_bTracking;
	BOOL    m_bKeepSize;
	BOOL    m_bParentSizing;
	BOOL    m_bDragShowContent;
	UINT    m_nDockBarID;
	int     m_cxEdge;
	
protected:
	//{{AFX_MSG(CSizingControlBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNcPaint();
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
	
	DECLARE_MESSAGE_MAP()
		
		
		//friend class CSCBMiniDockFrameWnd;
};
#endif //CSizingControlBar_h