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
				else if( c != ' ' || c != '\t' ) bBlank = false;//�����ǿո��ַ�
			}
			if(c == '\'' && m_cDefFlag == '#') 
			{
				c = MeetComma(c);//���������Ż�˫����
			}
			else if(c == '"') c = MeetComma(c);//���������Ż�˫����
			else if( c == '\\' ) //����
			{
				c1 = m_pLast->GetChar();
				if(c1 == '\n') 
				{
					m_iNewLineCnt ++;
					c = m_pLast->GetChar();
				}
				else 
				{
					AddErrorMsg("�Ƿ�ʹ�����з���");
					c = c1;
				}
			}
			else if( c == '/')		//ע��
			{
				c1 = m_pLast->GetChar();
				if(c1 == '*') 		//��ע��
					c = MeetBlockComment();
				else if( c1 == '/') //��ע��
				{
					while(1)		//�ҵ���β
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
			AddErrorMsg("ע�Ϳ����ļ�����");
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
		if(c0 == '\\') //ת��
		{
			c1 = m_pLast->GetChar();
			if(c1 == '\n')	//����
				m_iNewLineCnt ++;
			else			//������
			{
				m_strBuffer += c0;
				m_strBuffer += c1;
				//�˴����Լ��϶�ת������ж�
			}
			continue;
		}
		else
		{
			if(c0 == 0)
				AddErrorMsg("�ַ����������ļ�����");
			else if( c0 == '\n')
				AddErrorMsg("�ַ�������������");
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
