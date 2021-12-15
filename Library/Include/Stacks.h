#if !defined(__STACKS_H__)
#define __STACKS_H__

class CStackBase
{
protected:
	int	 m_iSize;
	int  m_iPos;
	CStackBase(){m_iSize=16;m_iPos=-1;}
public:
	void Clear(){m_iPos = -1;}
};

class CCharStack : public CStackBase
{
	char * m_pStack;
public:
	CCharStack();
	~CCharStack();
	char &Top(){return m_pStack[m_iPos];}
	bool Empty(){return m_iPos < 0;}
	char Pop(){return m_pStack[m_iPos--];}
	int  Size(){return m_iPos+1;}
	void Push(char c);
	char * GetText(){return m_pStack;}
	char Bottom(){return m_pStack[0];}
};

class CIntStack : public CStackBase
{
	int * m_pStack;
public:
	CIntStack();
	~CIntStack();
	int  &Top(){return m_pStack[m_iPos];}
	bool Empty(){return m_iPos < 0;}
	int  Pop(){return m_pStack[m_iPos--];}
	int  Size(){return m_iPos+1;}
	void Push(int i);
};

class CPtrStack : public CStackBase
{
	typedef void * VOIDP;
	VOIDP * m_pStack;
public:
	CPtrStack();
	~CPtrStack();
	VOIDP  &Top(){return m_pStack[m_iPos];}
	bool Empty(){return m_iPos < 0;}
	VOIDP  Pop();//{return m_pStack[m_iPos--];}
	int  Size(){return m_iPos+1;}
	void Push(void * p);
	VOIDP Peek(int pos);
	VOIDP Get(int pos);
};

class CStringStack : public CStackBase
{
	CString * m_pStack;
public:
	CStringStack();
	~CStringStack();
	CString  &Top(){return m_pStack[m_iPos];}
	bool Empty(){return m_iPos < 0;}
	CString  &Pop(){return m_pStack[m_iPos--];}
	int  Size(){return m_iPos+1;}
	void Push(CString &str);
};
#endif
