#if !defined( _SYSBASE_H_ )
#define _SYSBASE_H_
class CXPMemCDC
{
public:
	BOOL	m_bOK;
	CDC*	m_pDC;
	RECT	m_Rect;
	CDC		m_memDC;
	CDC*	m_pMemDC;
	CBitmap m_BMP;
	CBitmap*	m_pOldBmp;
	CXPMemCDC(){m_bOK = FALSE;m_pMemDC = m_pDC = NULL;}
	~CXPMemCDC();
	CDC* Start(CDC* pDC,RECT &rect);
};

#endif
