#if !defined(__CCONSTPARSE_H__)
#define __CCONSTPARSE_H__

#if _MSCP_VER > 1000
#pragma once
#endif // _MSCP_VER > 1000
#include "ConstLex.h"
class CPreDefine;
class CConstParse : public CConstLALR
{
	int	m_iConst;
public:
	CConstParse(const char *buffer);
	~CConstParse();
	virtual void Reduction(int num,int len);

	virtual void action(int i1 = 0, int i2 = 0);
	virtual int CheckTypeName();
	void	SetType(int set);
	void	Operation(int type);
	void	UnaryExpress();
	void	Primary(int i);
	void	Accept();
	void	Condition();
	void	Constant(int i);
	int		GetConst(){return m_iConst;}
};

#endif
