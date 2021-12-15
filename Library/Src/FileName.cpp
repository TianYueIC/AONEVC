#include "stdafx.h"
#include "../include/Utility.h"

void GetFileNamePrefix(CString& nameprefix,const CString& filename)
{
	int i = filename.ReverseFind('.');
	if(i > 0) nameprefix = filename.Left(i);
	else nameprefix = filename;
}

void GetFileNamePath(CString& filepath,const CString& filename)
{
	int i = filename.ReverseFind('\\');
	if(i > 0) filepath = filename.Left(i);
	else filepath = filename;
}

//filepath Ϊ·��ȫ�� 
// �� C:      C �̸�Ŀ¼
//    c:\dsp  C �̣�Ŀ¼dsp 
void AddFileNamePath(CString& filepath,CString& filename)
{
	if(filepath.IsEmpty() | filename.IsEmpty()) return;
	if(filename[0] == '\\') // filename �Ѿ��Ǿ���·��
		return; 
	if(filename.GetLength() > 2 && filename[1] == ':') // filename �Ѿ��Ǿ���·��
		return;
	CString name;
	CString tmp = filepath;
	tmp += '\\';
	tmp += filename;
	tmp.Replace('/','\\');
	CString strpre;
	int i,j;
	while ((i = tmp.Find('\\'))!= -1)
	{
		strpre = tmp.Left(i);
		if(strpre == "..") 
		{
			if(name.IsEmpty()) 
			{
				name = tmp;
				break;
			}
			j = name.ReverseFind('\\');
			if(j < 0)
			{
				name += '\\';
				name += tmp;
				break;
			}
			else
				name = name.Left(j);
		}
		else if(strpre != '.')
		{
			if(name.IsEmpty() == FALSE || strpre.IsEmpty()) name += '\\';
			if(strpre.IsEmpty() == FALSE) name += strpre;
		}
		tmp = tmp.Mid(i+1);
	}
	filename = name;
	if(i == -1) 
	{
		filename += '\\';
		filename += tmp;
	}
}

