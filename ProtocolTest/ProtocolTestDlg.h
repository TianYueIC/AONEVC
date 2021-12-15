// ProtocolTestDlg.h : header file
//

#if !defined(AFX_PROTOCOLTESTDLG_H__66CE7F9D_46B5_4CD6_BD8A_6DC92E1A69FA__INCLUDED_)
#define AFX_PROTOCOLTESTDLG_H__66CE7F9D_46B5_4CD6_BD8A_6DC92E1A69FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CProtocolTestDlg dialog

#include "..\ECCLib\Include\MSegInt.h"
#define OPERATOR1(x) (((x)>>8)&0xff)
#define OPERATOR2(x) (((x)>>16)&0xff)
#define TARGET(x) (((x)>>24)&0x7f)

class KeyItem
{
public:
	KeyItem * next;
	MSegInt K;
	ECCAff P;
	KeyItem(){	next = NULL; }
	bool IsMatch(ECCAff&p){return p == P;}
	bool IsMatch(MSegInt&k){return k == K;}
};
class KeyList
{
public:
	KeyItem * first;
	KeyList();
	~KeyList();
	void ReadFile(FILE* fp);
	ECCAff* Search(MSegInt & k);
	MSegInt* Search(ECCAff & p);
};
class CProtocolTestDlg : public CDialog
{
	int segLength,protcount;
	MSegInt P,A,N,X,Y,K,R0,R1,R2,R3,modV;
	ECCAff  P0,Pu;
	ECC ecc;
	KeyList m_KeyList;
////////////////////////////////////////////
	MSegInt mA,mB;
	ECCAff affA,affB;
	unsigned * data;
////////////////////////////////////////////

	void SetMSegInt(MSegInt & m);

	char buffer[1000];
	FILE *txfp;
	bool txok;
	unsigned txdata[1000];
	unsigned txType,txAttr;
	unsigned txchksum0,txchksum1;
	int	txLineCount;

	FILE * rxfp;
	bool rxok;
	unsigned rxdata[1000];
	unsigned rxType,rxAttr;
	int	rxLineCount;

	FILE * logfp;
	CString	m_strLogFileName;
	CStringList errorList;
// Construction
	int ReadLine(FILE *fp);
	bool ToEmptyLine(FILE *fp);
	bool ReadRxFile();
	bool ReadTxFile();
	void AddMessage(const char *msg,...);
	void AddErrorMessage(const char *msg,...);
	const char * GetProtocolName(int type);
	void Process();
	void CheckSum();
	void CheckTxDataLen(int len);
	void SelfTest();
	void PublicPreSet();
	void PrivatePreSet();
	void EccPreSet();
	void ModAdd();
	void ModSub();
	void ModMulti();
	void Mod();
	void Inv();
	void KP();
	void QAddP();
	void QAddQ();
	void Encrypt();
	void Decrypt();
	void GenerateKeys();
	void IsZero();
	void Sign();
	void Verificatiaon();
	void Hash();
	void Random();
	void Operator(int addr, MSegInt & mU);
	void Operator(int addr, ECCAff & affU);
	void Target(int addr, ECCAff & affT);
	void Target(int addr, MSegInt & mT);
	void Verify(MSegInt & S,const char * p);
	void Verify(ECCAff &S,const char * p);
	
	void InitCheckList();
	bool CheckOP(CString & msg); 
public:
	CProtocolTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CProtocolTestDlg)
	enum { IDD = IDD_PROTOCOLTEST_DIALOG };
	CListBox	m_ListBox;
	CString	m_strRxFileName;
	CString	m_strTxFileName;
	BOOL	m_bVerbos;
	CString	m_strParamFileName;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProtocolTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CProtocolTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBrowser();
	virtual void OnOK();
	afx_msg void OnBrowserParam();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROTOCOLTESTDLG_H__66CE7F9D_46B5_4CD6_BD8A_6DC92E1A69FA__INCLUDED_)
