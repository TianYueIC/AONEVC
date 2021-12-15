//////////////////////////////////////////////////////////////////////
// SourceFilter.cpp: implementation of the follow filter class.
// 1.CTextBackOne
// 2.CJuncLine
// 3.CLineComment
// 4.CBlockComment
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include <stdio.h>
#include "..\include\TextSource.h"
/////////////////////////////////////////////////////////////////////////////

CCComment::CCComment(char def,CTextSource * pLast) : CTextSource(pLast)
{
	m_iPos = 0;
	m_iBufferLen = 0;
	m_iNewLineCnt = 0;
	m_cDefFlag = def;
	m_bDefine = false;
}

bool CCComment::GetBack(char &c)
{
	static int debug = 0;
	debug ++;
	if(m_iPos >= m_iBufferLen) return false;
	else 
	{
		c = m_strBuffer[m_iPos++];
		return true; 
	}
}
void CCComment::GetLine()
{
	m_bDefine = false;
	if(m_iNewLineCnt)
	{
		m_strBuffer = '\n';
		m_iNewLineCnt--;
		m_iBufferLen = 1;
		m_iPos = 0;
	}
	else 
	{
		m_strBuffer.Empty();
		char c,c1;
		c = m_pLast->GetChar();
		bool bBlank = true;
		while(1)
		{
			if(bBlank)
			{
				if(c == m_cDefFlag) m_bDefine = true;
				else if( c != ' ' || c != '\t' ) bBlank = false;//遇到非空格字符
			}
			if(c == '\'' && m_cDefFlag == '#') 
			{
				c = MeetComma(c);//遇到单引号或双引号
			}
			else if(c == '"') c = MeetComma(c);//遇到单引号或双引号
			else if( c == '\\' ) //续行
			{
				c1 = m_pLast->GetChar();
				if(c1 == '\n') 
				{
					m_iNewLineCnt ++;
					c = m_pLast->GetChar();
				}
				else 
				{
					AddErrorMsg("非法使用续行符号");
					c = c1;
				}
			}
			else if( c == '/')		//注释
			{
				c1 = m_pLast->GetChar();
				if(c1 == '*') 		//块注释
					c = MeetBlockComment();
				else if( c1 == '/') //行注释
				{
					while(1)		//找到行尾
					{
						c = m_pLast->GetChar();
						if(c == '\n' || c == 0) break;
					}
					break;
				}
				else
				{
					m_strBuffer += c;
					c = c1;
				}
			}
			else if( c == 0 || c == '\n') break;
			else
			{
				m_strBuffer += c; 
				c = m_pLast->GetChar();
			}
		}
		if(c) m_strBuffer += c;
		m_iBufferLen = m_strBuffer.GetLength();
		m_iPos = 0;
	}
}

char CCComment::MeetBlockComment()
{
	char c;
	int line = 0;
	while(1)
	{
		c = m_pLast->GetChar();
		if(c == '*')
		{
			c = m_pLast->GetChar();
			if(c == '/') break;
		}
		if( c == '\n') line ++;
		else if( c == 0 ) 
		{
			AddErrorMsg("注释块内文件结束");
			return 0;
		}
	}
	if(line)
	{
		line --;
		m_iNewLineCnt += line;
		return '\n';
	}
	else return m_pLast->GetChar();
}

char CCComment::MeetComma(char c)
{
	char c0, c1;
	m_strBuffer += c;
	while(1)
	{
		c0 = m_pLast->GetChar();
		if(c0 == '\\') //转意
		{
			c1 = m_pLast->GetChar();
			if(c1 == '\n')	//续行
				m_iNewLineCnt ++;
			else			//非续行
			{
				m_strBuffer += c0;
				m_strBuffer += c1;
				//此处可以加上对转意符号判断
			}
			continue;
		}
		else
		{
			if(c0 == 0)
				AddErrorMsg("字符串内遇到文件结束");
			else if( c0 == '\n')
				AddErrorMsg("字符串内遇到换行");
			else 
			{
				m_strBuffer += c0;
				if(c != c0) continue;
				c0 = m_pLast->GetChar();
			}
			return c0;
		}
	}
}
