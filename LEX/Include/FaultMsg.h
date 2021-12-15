#if !defined(__FAULTMSG_H__)
#define __FAULTMSG_H__
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define UNSUPORT() Unsuport(__FILE__,__LINE__)
class CFaultMsg
{
protected:
	CString m_strError;
	CString m_strWarning;
	int	m_iErrorCount;
	int m_iWarningCount;
public:
	CFaultMsg();
	void Unsuport(const char * name,int line);
	virtual	void AddErrorMsg(const char *msg,...);
	virtual	void AddWarningMsg(const char *msg,...);

	virtual bool GetErrorMsg(CString &error);
	virtual bool GetWarningMsg(CString &error);
	virtual void GetMsgCount(int &error,int&warning);
	void	ExtractMsg(CFaultMsg & faultmsg);
};
#endif //__FAULTMSG_H__
