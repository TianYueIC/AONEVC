#include "stdafx.h"
#include "..\include\TextSource.h"
#include "..\include\Lex.h"
#include "..\include\LALR.h"
#include "..\include\PreSource.h"
#include "..\include\PreDefine.h"
#include "..\include\ConstParse.h"
#include "..\..\Library\include\utility.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CPreSource::CPreSource(char def,CTextSource* source):CCComment(def,source)
{
	m_iLineCnt = 0;
	m_pDefine = NULL;
}

CPreSource::~CPreSource()
{
}

// 解析命令字，不是宏命令返回-1
int	CPreSource::Resolve(CString& strDef, CString &param)
{
	int pos = m_strBuffer.Find(m_cDefFlag);
	CString str = m_strBuffer.Mid(pos+1);
	str.Replace('\t',' ');
	str.Replace('\n',' ');
	str.TrimLeft();
	pos = str.Find(' ');
	if(pos > 0) 
	{
		strDef = str.Left(pos);
		param = str.Mid(pos+1);	//宏定义参数
	}
	else 
	{
		strDef = str; 
		param = "";
	}
	// 分析宏定义关键字
	for(int i = m_iSizePredefID-1; i >= 0; i --)
	{
		if(strDef == m_pPredefIDs[i]) break;
	}
	return i;
}

//处理条件宏
//	"if",		// 3 
//	"ifdef",	// 4 
//	"ifndef",	// 5 
//	"else",		// 6 
//	"endif",	// 7 
//	"elif",		// 8 
void CPreSource::ConditionDef(CString& cmd,CString &param)
{
	if(m_TermStack.CheckError(cmd))
		AddErrorMsg("预处理条件命令\"%s\"不匹配",cmd);
	else 
	{
		bool cond = false;
		if( cmd == "if" || 
			cmd == "elif")
		{
			CConstParse parse(param);
			if(parse.Parse() == 0)
				cond = ( parse.GetConst() != 0);
		}
		else if(cmd == "ifdef" || 
				cmd == "ifndef")
		{ // ifdef ifndef 之后只能跟一个字串
			CString strID,garbage;
			CStringTransfer tran(NULL,param);
			if(tran.GetString(strID))
			{
				if(tran.GetString(garbage))
					AddWarningMsg("预处理命令\"%s\"之后跟随了无效字符串\"%s\"",strID,garbage);
				cond = m_pDefine->Lookup(strID) != 0;
			}
			else //无合理字串
				AddErrorMsg("预处理命令\"%s\"之后缺字符串",strID);
			if(cmd == "ifndef") cond = ! cond;
		}
		//	"else",		else 和 endif 之后可以跟随任何字串，用来注释
		//	"endif",	
		//临时，应该由此产生条件结果
		m_TermStack.CheckIn(cmd,cond);
	}
}

void CPreSource::Define(bool bUndefine,CString &param)
{
	CStringAnalyze analyze(param);
	CString strID,strList,strDef;
	if(analyze.GetDefine(strID,strList,strDef))
	{
		if(bUndefine) m_pDefine->Remove(strID);
		else 
		{
			if(strList.IsEmpty()) 
				m_pDefine->Add(strID,strDef);
			else 
				m_pDefine->Add(strID,strDef,strList);
		}
		ExtractMsg(*m_pDefine);
	}
	ExtractMsg(analyze);
}

void CPreSource::Include(CString &param)
{
	CString str = param;
	//首先将 < > 转换为 " "，进行宏替换
	//首先将 < > 转换为 " "，进行宏替换
	int begin = str.Find('<');
	int end = str.ReverseFind('>');
	if(begin >= 0 && end > 0)
	{
		str.SetAt(begin,'\"');
		str.SetAt(end,'\"');
	}
	else
	{
		begin = str.Find('\"');
		end = str.ReverseFind('\"');
		if(begin < 0 && end < 0)
			m_pDefine->Transfer(str,param);
	}
	
	//取文件名
	str.TrimLeft();
	str.TrimRight();
	int len = str.GetLength();
	char c = 0,c1 = 0;
	if(len >= 2) 
	{
		c = str[0];
		c1 = str[len-1];
	}
	if(len < 2 || c != '\"' || c != c1)
		AddErrorMsg("include 后面语法错误");
	else
	{
		str = str.Mid(1,len-2);
		CString filepath;
		GetFileNamePath(filepath,GetFileName());
		AddFileNamePath(filepath,str);
		m_pLexSource->Push(str);
	}
}

char CPreSource::GetChar()
{
	char c;
	if(!GetBack(c)) 
	{
		Look();
		if(!GetBack(c)) c = 0;
	}
	if(c == '\n' || c == 0) m_iLineCnt ++;
	if(c == 0)
	{
		if(m_TermStack.IsEmpty() == FALSE)		
			AddErrorMsg("文件非正常结束，预处理未匹配结束");
	}
	return c;
}

CStringTransfer::CStringTransfer(CString * pTarget, const char * pSource,CTextSource* pTextSource)
{
	m_uBuffer = 0;
	m_pTarget = pTarget;
	m_pSource = pSource;
	m_pTextSource = pTextSource;
	m_bEmpty = (*m_pSource == 0);
}

//在缓冲区中，0 或 \n 之前，找出 " " 字符串
bool	CStringTransfer::GetCharString(CString & str)
{
	char c;
	str.Empty();
	c = GetChar();
	bool bEsc = false;
	if(c == '"') 
	{
		str = c;
		while(1)
		{
			c = GetChar();
			if(c == 0 || c == '\n') break;
			str += c;
			if(!bEsc && c == '"') return true;
			if(c == '\\') bEsc = true;
			else bEsc = false;
		}
	} 
	else if( c =='\'')
	{
		str = c;
		while(1)
		{
			c = GetChar();
			if(c == 0 || c == '\n') break;
			str += c;
			if(!bEsc && c == '\'') return true;
			if(c == '\\') bEsc = true;
			else bEsc = false;
		}
	}
	else str.Empty();
	return false;
}

bool	CStringTransfer::FindVerilogString(CString & str)
{
	char c;
	str.Empty();
	while(1)
	{
		c = GetChar();
		if(c == 0) return false;
		else if(c == '`') break;
		
		if( c == '"' || c == '\'')
		{
			CString str;
			UnputChar(c);
			bool bNoErr = GetCharString(str);
			if(m_pTarget)(*m_pTarget) += str;
			if(!bNoErr) return false;
		}
		else if(m_pTarget)(*m_pTarget) += c;
		if(*m_pSource == 0) return false; //下一个字符为结束时退出
	}
	int count = 0;
	while(1)
	{
		c = GetChar();
		count ++;
		if( isalpha(c) || isdigit(c) || c == '_') 
			str += c;
		else if(c == 0) break;
		else
		{
			UnputChar(c);
			break;
		}
	}
	return count != 0;
}

//在缓冲区中，0 或 \n 之前，找出一个有效字符串
//  注意跨过字符串定义 "  " ' '
//  目前宏定义串内，和对程序文本的扫描都是用此程序找到被替换字串
bool	CStringTransfer::FindString(CString & str)
{
	char c;
	str.Empty();
	bool bBlank = true;
	while(1)
	{
		c = GetChar();
		if(c == 0) break;
		if( isalpha(c) || isdigit(c) || c == '_') 
		{
			str += c;
			bBlank = false;
		}
		else
		{
			if(bBlank)
			{
				if(c == '"' || c == '\'') 
				{
					CString str;
					UnputChar(c);
					bool bNoErr = GetCharString(str);
					if(m_pTarget)(*m_pTarget) += str;
					if(!bNoErr) break;
				}
				else if(m_pTarget)(*m_pTarget) += c;
				if(*m_pSource == 0) break; //下一个字符为结束时退出
			}
			else
			{
				UnputChar(c);
				break;
			}
		}
	}
	return !bBlank;
}

// 分离形参表和实参表，取得下一个字串
// 形参表在接受定义时已经进行过合理性检查，其中不会出现 " ( 等等
// 分离实参时，则需要考虑, () "" 之影响 
bool	CStringTransfer::GetParamString(CString &str)
{
	str.Empty();
	char c = NextChar();
	bool bFirst = true;
	while(1)
	{
		if( c == '(')
		{
			CString pl;
			if(GetParamList(pl))
			{
				str += c;
				str += pl;
				str += ')';
				if(bFirst) return true;
			}
			else return false;
		}
		else if(c == '"' || c == '\'')
		{
			UnputChar(c);
			CString s;
			bool bNoErr = GetCharString(s);
			str += s;
			if(!bNoErr) return false;
		}
		else if(c == 0) return true;
		else if(c == ',' || c == ')') break;
		else str += GetChar();
		c = NextChar();
		bFirst = false;
	}
	return true;
}
//将实参表 DList 分离，跨一个','取得下一个字串，遇到')' str置空，但返回 true
bool	CStringTransfer::GetNextParamString(CString &str)
{
	str.Empty();
	char c = GetNextChar();
	if(c == ',') 
		return GetParamString(str);
	else if( c == ')') 
		return true;
	else 
		return false;
}

bool	CStringTransfer::GetString(CString & str)
{
	char c= GetNextChar();;
	str.Empty();
	bool bBlank = true;
	while(1)
	{
		if(c == 0) break;
		if( isalpha(c) || isdigit(c) || c == '_') 
		{
			str += c;
			bBlank = false;
		}
		else
		{
			if(bBlank)
				if(m_pTarget)(*m_pTarget) += c;
			else
			{
				UnputChar(c);
				break;
			}
		}
		c = GetChar();
	}
	return !bBlank;
}

char	CStringTransfer::GetChar()
{
	char c = 0;
	if(!GetBack(c)) 
	{
		if(!m_bEmpty) 
		{
			c = *m_pSource++;
			m_bEmpty = (*m_pSource == 0);
		}
		else if(m_pTextSource != NULL)
			c = m_pTextSource->GetChar();
	}
	return c;
}

void CStringTransfer::UnputChar(char c)
{
	m_uBuffer = 0x10000 | (unsigned)c;
}
bool	CStringTransfer::GetBack(char &c)
{
	if(m_uBuffer & 0x10000)
	{
		c = (char) m_uBuffer;
		m_uBuffer = 0;
		return true;
	}
	else return false;
}

char	CStringTransfer::NextChar()
{
	char c = GetNextChar();
	UnputChar(c);
	return c;
}

char	CStringTransfer::GetNextChar()
{
	char c;
	while(1)
	{
		c = GetChar();
		if( c != ' ' && c != '\t' && c != '\n') break;
		if(m_pTarget) *m_pTarget += c;
	}
	return c;
}

bool	CStringTransfer::GetParamList(CString & str)
{
	str.Empty();
	char c = NextChar();
	if(c != '(') 
	{
		AddErrorMsg("引用函数型宏定义时无参数列表");
		return false;//无参数列表
	}
	c = GetNextChar();
	while (1)
	{
		c = GetNextChar();
		if(c == 0) 
		{
			AddErrorMsg("引用函数型宏定义时'('不匹配");
			return false;
		}
		else if(c == ')') return true;
		else str += c;
		if(c == '(') 
		{
			UnputChar(c);
			CString str1;
			if(!GetParamList(str1)) return false;
			str += str1;
			str += ')';
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// 该类仅仅在宏定义时使用
CStringAnalyze::CStringAnalyze(const char *pSource)
{
	m_pSource = pSource;
}
bool CStringAnalyze::GetString(CString & str)
{
	str.Empty();
	char c;
	bool bBlank = true;
	while(1)
	{
		c = *m_pSource++;
		if(c == 0) break;
		if( isalpha(c) || isdigit(c) || c == '_') 
		{
			str += c;
			bBlank = false;
		}
		else 
		{
			if(bBlank)
			{
				if(c == ' '|| c == '\t' || c == '\n') continue;
			}
			m_pSource--;
			break;
		}
	}
	return !bBlank;
}
char	CStringAnalyze::GetNextChar()
{
	char c;
	while(1)
	{
		c = *m_pSource++;
		if( c != ' ' && c != '\t' && c != '\n') break;
	}
	return c;
}
//将以','分割的参数表转入 str
bool CStringAnalyze::GetParamList(CString & str)//出错返回false
{
	char c;
	m_pSource ++; //第一个字符一定是'('
	CString param;
	int count = 0;
	bool bString = false;
	while (1)
	{
		bString = GetString(param);
		c = GetNextChar();
		if(!bString) break;
		count ++;
		str += param;
		if(c == ')') return true; // 遇到 ')' 结束
		else if( c == ',' ) str += ',';
		else if(isalpha(c))
		{
			AddErrorMsg("函数型宏定义参数表中应使用','将参数隔开");
			return false;
		}
		else 
		{
			m_pSource--;
			if(GetString(param))
				AddErrorMsg("函数型宏定义参数表中出现非法字符串\"%s\"",param);
			else
				break;
		}
	}
	if(count == 0 && c == ')') 
	{	//函数型宏定义中无参数
		str = ' ';
		return true;
	}
	AddErrorMsg("函数型宏定义参数表中出现语法错误");
	return false;
}
bool CStringAnalyze::GetDefine(CString & strID,CString &strList, CString & strDef)
{
	bool bError = false;
	if(GetString(strID))
	{
		if(*m_pSource == '(') //紧接着'('，是函数型宏定义
		{
			if(!GetParamList(strList)) return false;
		}
		if(*m_pSource) //将后面部分全部交给定义串
			strDef = m_pSource;
	}
	else 
		AddErrorMsg("宏定义语法错误");
	return true;
}

///////////////////////////////////////////////////////////////////////////////

CTermStack::~CTermStack()
{
}
CTermStack::CTermStack()
{
}

bool CTermStack::CheckError(CString& cmd)
{
	if(m_State.Empty())
	{
		if(cmd == "else" || cmd == "elif" || cmd == "endif") 
			return true;
		// 出错不匹配
	}
	else 
	{
		if( (cmd != "endif") && (m_State.Top() & Else)) //else elif出错，已经有了 ELSE
			return true;
	}
	return false;
}

void CTermStack::CheckIn(CString& cmd , bool condition)
{
	if(cmd == "endif") m_State.Pop();
	else if(cmd == "if"	  ||
			cmd == "ifdef"||
			cmd == "ifndef"   )
	{
		bool bTrue = true;
		if(!m_State.Empty()) 
			bTrue = (m_State.Top() & True) != 0;
		int state = Enable;
		if(condition) state |= True;//根据条件设置真假
		m_State.Push(state);
	}
	else 
	{
		int & iState = m_State.Top();
		if(cmd == "else")
		{
			iState |= Else;
			if(iState & Enable) //如若为激活状态，则将条件值翻转
				iState = ( iState & ~True) | ((~(iState)) & True);
		}
		else //type == ELIF
		{
			if(iState & Enable)			//如若为激活状态
			{
				if(iState & True)		//当前已经为真
				{
					iState &= ~True;	//转为假
					iState &= ~Enable;	//取消激活
				}
				else if(condition) iState |= True; //当前为假，根据条件设置真假
			}
		}
	}
}

bool CTermStack::IsTrue()
{
	if(!m_State.Empty()) 
		return (m_State.Top() & True) != 0; 
	else return true;
}
bool CTermStack::IsEmpty()
{
	return m_State.Empty();
}
