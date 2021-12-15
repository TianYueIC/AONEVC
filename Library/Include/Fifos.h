#if !defined(__FIFOS_H__)
#define __FIFOS_H__

class CFifoBase
{
protected:
	int	 m_iSize;
	int  m_iInPos;
	int  m_iOutPos;
	int  m_iMask;
	CFifoBase();
public:
	void Clear();
};

class CCharFifo : public CFifoBase
{
	char * m_pFifo;
public:
	CCharFifo();
	~CCharFifo();
	char &End(){return m_pFifo[m_iOutPos];}
	char &First(){return m_pFifo[m_iInPos];}
	bool Empty(){return m_iOutPos == m_iInPos;}
	char Out();
	void In(char c);
	int  Size();
};

#endif //__FIFOS_H__
