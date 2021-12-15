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

// ���������֣����Ǻ������-1
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
		param = str.Mid(pos+1);	//�궨�����
	}
	else 
	{
		strDef = str; 
		param = "";
	}
	// �����궨��ؼ���
	for(int i = m_iSizePredefID-1; i >= 0; i --)
	{
		if(strDef == m_pPredefIDs[i]) break;
	}
	return i;
}

//����������
//	"if",		// 3 
//	"ifdef",	// 4 
//	"ifndef",	// 5 
//	"else",		// 6 
//	"endif",	// 7 
//	"elif",		// 8 
void CPreSource::ConditionDef(CString& cmd,CString &param)
{
	if(m_TermStack.CheckError(cmd))
		AddErrorMsg("Ԥ������������\"%s\"��ƥ��",cmd);
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
		{ // ifdef ifndef ֮��ֻ�ܸ�һ���ִ�
			CString strID,garbage;
			CStringTransfer tran(NULL,param);
			if(tran.GetString(strID))
			{
				if(tran.GetString(garbage))
					AddWarningMsg("Ԥ��������\"%s\"֮���������Ч�ַ���\"%s\"",strID,garbage);
				cond = m_pDefine->Lookup(strID) != 0;
			}
			else //�޺����ִ�
				AddErrorMsg("Ԥ��������\"%s\"֮��ȱ�ַ���",strID);
			if(cmd == "ifndef") cond = ! cond;
		}
		//	"else",		else �� endif ֮����Ը����κ��ִ�������ע��
		//	"endif",	
		//��ʱ��Ӧ���ɴ˲����������
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
	//���Ƚ� < > ת��Ϊ " "�����к��滻
	//���Ƚ� < > ת��Ϊ " "�����к��滻
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
	
	//ȡ�ļ���
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
		AddErrorMsg("include �����﷨����");
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
			AddErrorMsg("�ļ�������������Ԥ����δƥ�����");
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

//�ڻ������У�0 �� \n ֮ǰ���ҳ� " " �ַ���
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
		if(*m_pSource == 0) return false; //��һ���ַ�Ϊ����ʱ�˳�
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

//�ڻ������У�0 �� \n ֮ǰ���ҳ�һ����Ч�ַ���
//  ע�����ַ������� "  " ' '
//  Ŀǰ�궨�崮�ڣ��ͶԳ����ı���ɨ�趼���ô˳����ҵ����滻�ִ�
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
				if(*m_pSource == 0) break; //��һ���ַ�Ϊ����ʱ�˳�
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

// �����βα��ʵ�α�ȡ����һ���ִ�
// �βα��ڽ��ܶ���ʱ�Ѿ����й������Լ�飬���в������ " ( �ȵ�
// ����ʵ��ʱ������Ҫ����, () "" ֮Ӱ�� 
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
//��ʵ�α� DList ���룬��һ��','ȡ����һ���ִ�������')' str�ÿգ������� true
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
		AddErrorMsg("���ú����ͺ궨��ʱ�޲����б�");
		return false;//�޲����б�
	}
	c = GetNextChar();
	while (1)
	{
		c = GetNextChar();
		if(c == 0) 
		{
			AddErrorMsg("���ú����ͺ궨��ʱ'('��ƥ��");
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
// ��������ں궨��ʱʹ��
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
//����','�ָ�Ĳ�����ת�� str
bool CStringAnalyze::GetParamList(CString & str)//������false
{
	char c;
	m_pSource ++; //��һ���ַ�һ����'('
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
		if(c == ')') return true; // ���� ')' ����
		else if( c == ',' ) str += ',';
		else if(isalpha(c))
		{
			AddErrorMsg("�����ͺ궨���������Ӧʹ��','����������");
			return false;
		}
		else 
		{
			m_pSource--;
			if(GetString(param))
				AddErrorMsg("�����ͺ궨��������г��ַǷ��ַ���\"%s\"",param);
			else
				break;
		}
	}
	if(count == 0 && c == ')') 
	{	//�����ͺ궨�����޲���
		str = ' ';
		return true;
	}
	AddErrorMsg("�����ͺ궨��������г����﷨����");
	return false;
}
bool CStringAnalyze::GetDefine(CString & strID,CString &strList, CString & strDef)
{
	bool bError = false;
	if(GetString(strID))
	{
		if(*m_pSource == '(') //������'('���Ǻ����ͺ궨��
		{
			if(!GetParamList(strList)) return false;
		}
		if(*m_pSource) //�����沿��ȫ���������崮
			strDef = m_pSource;
	}
	else 
		AddErrorMsg("�궨���﷨����");
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
		// ����ƥ��
	}
	else 
	{
		if( (cmd != "endif") && (m_State.Top() & Else)) //else elif�����Ѿ����� ELSE
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
		if(condition) state |= True;//���������������
		m_State.Push(state);
	}
	else 
	{
		int & iState = m_State.Top();
		if(cmd == "else")
		{
			iState |= Else;
			if(iState & Enable) //����Ϊ����״̬��������ֵ��ת
				iState = ( iState & ~True) | ((~(iState)) & True);
		}
		else //type == ELIF
		{
			if(iState & Enable)			//����Ϊ����״̬
			{
				if(iState & True)		//��ǰ�Ѿ�Ϊ��
				{
					iState &= ~True;	//תΪ��
					iState &= ~Enable;	//ȡ������
				}
				else if(condition) iState |= True; //��ǰΪ�٣����������������
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
