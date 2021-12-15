#if !defined(__LEX_H__)
#define __LEX_H__
//////////////////////////////////////////////////////////////////////
// Lex.h: interface for the Lex class.
//////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLexSource;
class LALR;
class Lex  
{
	Lex(Lex&);
protected:
	struct yywork 
	{ 
		int verify;
		int	advance; 
	};

	struct yysvf { 
		struct yywork	*yystoff;
		struct yysvf	*yyother;
		int				*yystops;
	};
private:
	int		m_iPrevious;
	char	m_cText[100];
	char	m_cUndefText;
	struct	yysvf  **m_pStateStack;

	CLexSource	*m_pSource;
protected:
	LALR*		m_parse;
	char		*m_yymatch;
	
	struct yywork *m_pTop;
	struct yywork *m_yycrank;
	struct yysvf  *m_yysvec;

	char	m_cPairs[100];
	int		m_iPairsPos;
	int		m_iUnKnowCharCnt;
public:
				Lex();
virtual			~Lex();
	void		Set(CLexSource * source);
	void		LinkParse(LALR* parse){ m_parse = parse;};
	char*		GetText();
	char		GetUndefText();

virtual	int		Look();

	int			CheckTypeName();// 与 parse 建立的唯一桥梁

	void		MarchChar(char c);
	char		ExpectMarchChar();
	void		UnKnowChar();

	//编译过程中收集警告、错误信息
	void	AddErrorMsg(const char *msg, ...); 
	void	AddWarningMsg(const char *msg, ...);
	void	AddErrorMsgV( LPCTSTR msg, va_list list );
	void	AddWarningMsgV(LPCTSTR msg, va_list list);


	bool	GetErrorMsg(CString & error);
	bool	GetWarningMsg(CString & warning);
	void	GetMsgCount(int &error,int &warning);
	int		CurLineNumber();
};
#endif // !defined(__LEX_H__)
