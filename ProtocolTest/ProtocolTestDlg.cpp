// ProtocolTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProtocolTest.h"
#include "ProtocolTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProtocolTestDlg dialog

CProtocolTestDlg::CProtocolTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProtocolTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProtocolTestDlg)
	m_strRxFileName = _T("");
	m_strTxFileName = _T("");
	m_bVerbos = FALSE;
	m_strParamFileName = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	segLength = 6;
	ecc.B.SetHex("1854BEBDC31B21B7AEFC80AB0ECD10D5B1B3308E6DBF11C1");
	InitCheckList();
}

void CProtocolTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProtocolTestDlg)
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Text(pDX, IDC_RX_FILENAME, m_strRxFileName);
	DDX_Text(pDX, IDC_TX_FILENAME, m_strTxFileName);
	DDX_Check(pDX, IDC_VERBOS, m_bVerbos);
	DDX_Text(pDX, IDC_PARAM_FILENAME, m_strParamFileName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProtocolTestDlg, CDialog)
	//{{AFX_MSG_MAP(CProtocolTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BROWSER, OnBrowser)
	ON_BN_CLICKED(IDC_BROWSERPARAM, OnBrowserParam)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProtocolTestDlg message handlers

BOOL CProtocolTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CProtocolTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CProtocolTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CProtocolTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CProtocolTestDlg::OnBrowser() 
{
	CFileDialog dlg(TRUE,NULL,NULL,
		OFN_HIDEREADONLY | OFN_ENABLESIZING,"*.data|*.data||");	
	if (dlg.DoModal() == IDOK)
	{
		CString str = dlg.GetPathName();
		int pos = str.Find(".Rx.");
		m_strRxFileName.Empty();
		m_strTxFileName.Empty();
		if (pos > 0)
		{
			m_strRxFileName = str;
			m_strTxFileName = str;
			m_strTxFileName.SetAt(pos + 1, 'T');
		}
		else 
		{
			pos = str.Find(".Tx.");
			if (pos > 0)
			{
				m_strTxFileName = str;
				m_strRxFileName = str;
				m_strRxFileName.SetAt(pos + 1, 'R');
			}
		}
		if (pos > 0)
		{
			m_strLogFileName = str.Left(pos);
			m_strLogFileName += ".prot.log";
		}
		UpdateData(FALSE);
	}
}
void	CProtocolTestDlg::AddMessage(const char *msg, ...)
{
	va_list list;
	va_start( list, msg);
	CString str;
	str.FormatV(msg, list);
	if (m_bVerbos) m_ListBox.InsertString(-1, str);
	if (logfp) fprintf(logfp,"%s\n", str);
}
void	CProtocolTestDlg::AddErrorMessage(const char *msg, ...)
{
	va_list list;
	va_start( list, msg);
	CString str;
	str.FormatV(msg, list);
	CString s;
	s.Format("�� %d ��Э����(rx line: %d, tx line: %d):%s", protcount, rxLineCount, txLineCount, str);
	errorList.AddTail(s);
	s.Format("!!!!!!!!!!! %s !!!!!!!!!!!!!!", str);
	if(m_bVerbos) m_ListBox.InsertString(-1, s);
	if(logfp) fprintf(logfp, "%s\n", s);
}

class WordItem
{
public:
	unsigned w;
	WordItem * next;
	WordItem(unsigned i,WordItem *p){next = p;w = i;}
};
class ProtocolWord
{
public:
	unsigned ID;
	char * name;
	WordItem * OPD1;
	WordItem * OPD2;
	WordItem * OPDL;
	WordItem * OPR;
	ProtocolWord * next;
	ProtocolWord(unsigned id,char * name);
	~ProtocolWord();
	void AddOpD1(unsigned w){ OPD1 = new WordItem(w,OPD1);}
	void AddOpD2(unsigned w){ OPD2 = new WordItem(w,OPD2);}
	void AddOpDL(unsigned w){ OPDL = new WordItem(w,OPDL);}
	void AddOpR(unsigned w){ OPR = new WordItem(w,OPR);}
	bool Check(unsigned type,unsigned attr,CString& msg);
};
static ProtocolWord * root = NULL;
ProtocolWord::ProtocolWord(unsigned id,char * n)
{
	ID = id;
	OPD1 = NULL;
	OPD2 = NULL;
	OPDL = NULL;
	OPR = NULL;
	next = root;
	root = this;
	name = n;
}
ProtocolWord::~ProtocolWord()
{
	WordItem * next;
	WordItem * cur;
	cur = OPD1;
	while (cur)
	{
		next = cur->next;
		delete cur;
		cur = next;
	}
	OPD1 = NULL;
	cur = OPD2;
	while (cur)
	{
		next = cur->next;
		delete cur;
		cur = next;
	}
	OPD2 = NULL;
	cur = OPDL;
	while (cur)
	{
		next = cur->next;
		delete cur;
		cur = next;
	}
	OPDL = NULL;
	cur = OPR;
	while (cur)
	{
		next = cur->next;
		delete cur;
		cur = next;
	}
	OPR = NULL;
}

bool ProtocolWord::Check(unsigned type,unsigned attr,CString& msg)
{
	unsigned tmp;
	bool b = true;
	WordItem * cur;
	CString str,dstr;
	type >>= 8;
	tmp = type & 0xff;
	cur = OPD1;
	msg = name;
	msg += "Э���� ";
	str  = "OPD1ASW ӦΪ:";
	while (cur)
	{
		dstr.Format("0x%02x",cur->w);
		str += dstr;
		if (cur->w == tmp) break;
		cur = cur->next;
		if(cur) str += " �� ";
	}
	if(OPD1 != NULL && cur == NULL)
	{
		b = false;
		msg += str;
	}
	type >>= 8;
	tmp = type & 0xff;
	cur = OPD2;
	str = "OPD2ASW ӦΪ:";
	while (cur)
	{
		dstr.Format("0x%02x",cur->w);
		str += dstr;
		if (cur->w == tmp) break;
		cur = cur->next;
		if(cur) str += " �� ";
	}
	if(OPD2 != NULL && cur == NULL)
	{
		b = false;
		msg += str;
	}
	type >>= 8;
	tmp = type & 0xff;
	cur = OPR;
	str = "OPRASW ӦΪ:";
	while (cur)
	{
		dstr.Format("0x%02x",cur->w);
		str += dstr;
		if (cur->w == tmp) break;
		cur = cur->next;
		if(cur) str += " �� ";
	}
	if(OPR != NULL && cur == NULL)
	{
		b = false;
		msg += str;
	}
	tmp = (attr>>16) & 0xffff;
	cur = OPDL;
	str = "OPDLEN ӦΪ:";
	while (cur)
	{
		dstr.Format("0x%02x",cur->w);
		str += dstr;
		if (cur->w == tmp) break;
		cur = cur->next;
		if(cur) str += " �� ";
	}
	if(OPDL != NULL && cur == NULL)
	{
		b = false;
		msg += str;
	}
	return b;
}
void CProtocolTestDlg::InitCheckList()
{
	ProtocolWord * p;
	p = new ProtocolWord(0x01,"�Լ�");
		p->AddOpD1(0xff);
		p->AddOpDL(0x0004);
	p = new ProtocolWord(0x0a,"Ԥ��ģ��");
		p->AddOpD1(0xff);
		p->AddOpDL(0x0004);
	p = new ProtocolWord(0x0f,"Ԥ����Բ���߲���");
		p->AddOpD1(0xff);
		p->AddOpD1(0x7f);
		p->AddOpDL(0x0078);
	p = new ProtocolWord(0x14,"Ԥ���û�˽Կ");
		p->AddOpD1(0xff);
		p->AddOpDL(0x0018);
		p->AddOpR(0x00);
		p->AddOpR(0x80);
	p = new ProtocolWord(0x19,"Ԥ���û���Կ");
		p->AddOpD1(0xff);
		p->AddOpDL(0x0030);
		p->AddOpR(0x20);
		p->AddOpR(0xa0);
	p = new ProtocolWord(0x1e,"���������");
		p->AddOpDL(0x0000);
        p->AddOpR(0xff);
        p->AddOpR(0x7f);
        p->AddOpR(0xc0);
        p->AddOpR(0xc1);
        p->AddOpR(0xc2);
        p->AddOpR(0xc3);
        p->AddOpR(0x40);
        p->AddOpR(0x41);
        p->AddOpR(0x42);
        p->AddOpR(0x43);
	p = new ProtocolWord(0x23,"������Բ������Կ��");
		p->AddOpDL(0x0000);
        p->AddOpR(0xff);
        p->AddOpR(0x7f);
	p = new ProtocolWord(0x64,"����");
        p->AddOpD1(0xff);
        p->AddOpD2(0xff);
        p->AddOpD2(0xa0);
		p->AddOpDL(0x0018);
        p->AddOpDL(0x0048);
        p->AddOpR(0xff);
        p->AddOpR(0x7f);
	p = new ProtocolWord(0x65,"����");
        p->AddOpD1(0xff);
        p->AddOpD2(0xff);
        p->AddOpD2(0x80);
		p->AddOpDL(0x0048);
        p->AddOpDL(0x0060);
        p->AddOpR(0xff);
        p->AddOpR(0x7f);
    p = new ProtocolWord(0x66,"ǩ��");
        p->AddOpD1(0xff);
        p->AddOpD2(0xff);
        p->AddOpD2(0x80);
		p->AddOpDL(0x0018);
        p->AddOpDL(0x0030);
        p->AddOpR(0xff);
        p->AddOpR(0x7f);
	p = new ProtocolWord(0x67,"����");
        p->AddOpD1(0xff);
        p->AddOpD2(0xff);
        p->AddOpD2(0xa0);
		p->AddOpDL(0x0048);
        p->AddOpDL(0x0078);
        p->AddOpR(0xff);
        p->AddOpR(0x7f);
	p = new ProtocolWord(0x28,"��������:�ж�ȫ��");
        p->AddOpD1(0xff);
        p->AddOpD1(0xc0);
        p->AddOpD1(0xc1);
        p->AddOpD1(0xc2);
        p->AddOpD1(0xc3);
		p->AddOpDL(0x0000);
        p->AddOpDL(0x0018);
        p->AddOpR(0xff);
        p->AddOpR(0x7f);
	p = new ProtocolWord(0x29,"��������:Լ��");
        p->AddOpD1(0xff);
        p->AddOpD1(0xc0);
        p->AddOpD1(0xc1);
        p->AddOpD1(0xc2);
        p->AddOpD1(0xc3);
        p->AddOpD2(0xff);
        p->AddOpD2(0xc0);
        p->AddOpD2(0xc1);
        p->AddOpD2(0xc2);
        p->AddOpD2(0xc3);
		p->AddOpDL(0x0000);
        p->AddOpDL(0x0018);
        p->AddOpDL(0x0030);
        p->AddOpR(0xff);
        p->AddOpR(0x7f);
        p->AddOpR(0xc0);
        p->AddOpR(0xc1);
        p->AddOpR(0xc2);
        p->AddOpR(0xc3);
        p->AddOpR(0x40);
        p->AddOpR(0x41);
        p->AddOpR(0x42);
        p->AddOpR(0x43);
	p = new ProtocolWord(0x2a,"��������:ģ��");
        p->AddOpD1(0xff);
        p->AddOpD1(0xc0);
        p->AddOpD1(0xc1);
        p->AddOpD1(0xc2);
        p->AddOpD1(0xc3);
        p->AddOpD2(0xff);
        p->AddOpD2(0xc0);
        p->AddOpD2(0xc1);
        p->AddOpD2(0xc2);
        p->AddOpD2(0xc3);
		p->AddOpDL(0x0000);
        p->AddOpDL(0x0018);
        p->AddOpDL(0x0030);
        p->AddOpR(0xff);
        p->AddOpR(0x7f);
        p->AddOpR(0xc0);
        p->AddOpR(0xc1);
        p->AddOpR(0xc2);
        p->AddOpR(0xc3);
        p->AddOpR(0x40);
        p->AddOpR(0x41);
        p->AddOpR(0x42);
        p->AddOpR(0x43);
	p = new ProtocolWord(0x2b,"��������:ģ��");
        p->AddOpD1(0xff);
        p->AddOpD1(0xc0);
        p->AddOpD1(0xc1);
        p->AddOpD1(0xc2);
        p->AddOpD1(0xc3);
        p->AddOpD2(0xff);
        p->AddOpD2(0xc0);
        p->AddOpD2(0xc1);
        p->AddOpD2(0xc2);
        p->AddOpD2(0xc3);
		p->AddOpDL(0x0000);
        p->AddOpDL(0x0018);
        p->AddOpDL(0x0030);
        p->AddOpR(0xff);
        p->AddOpR(0x7f);
        p->AddOpR(0xc0);
        p->AddOpR(0xc1);
        p->AddOpR(0xc2);
        p->AddOpR(0xc3);
        p->AddOpR(0x40);
        p->AddOpR(0x41);
        p->AddOpR(0x42);
        p->AddOpR(0x43);
	p = new ProtocolWord(0x2c,"��������:ģ��");
        p->AddOpD1(0xff);
        p->AddOpD1(0xc0);
        p->AddOpD1(0xc1);
        p->AddOpD1(0xc2);
        p->AddOpD1(0xc3);
        p->AddOpD2(0xff);
        p->AddOpD2(0xc0);
        p->AddOpD2(0xc1);
        p->AddOpD2(0xc2);
        p->AddOpD2(0xc3);
		p->AddOpDL(0x0000);
        p->AddOpDL(0x0018);
        p->AddOpDL(0x0030);
        p->AddOpR(0xff);
        p->AddOpR(0x7f);
        p->AddOpR(0xc0);
        p->AddOpR(0xc1);
        p->AddOpR(0xc2);
        p->AddOpR(0xc3);
        p->AddOpR(0x40);
        p->AddOpR(0x41);
        p->AddOpR(0x42);
        p->AddOpR(0x43);
	p = new ProtocolWord(0x2d,"��������:����");
        p->AddOpD1(0xff);
        p->AddOpD1(0xc0);
        p->AddOpD1(0xc1);
        p->AddOpD1(0xc2);
        p->AddOpD1(0xc3);
		p->AddOpDL(0x0000);
        p->AddOpDL(0x0018);
        p->AddOpR(0xff);
        p->AddOpR(0x7f);
        p->AddOpR(0xc0);
        p->AddOpR(0xc1);
        p->AddOpR(0xc2);
        p->AddOpR(0xc3);
        p->AddOpR(0x40);
        p->AddOpR(0x41);
        p->AddOpR(0x42);
        p->AddOpR(0x43);
	p = new ProtocolWord(0x2e,"��������:HASH");
        p->AddOpD1(0xff);
        p->AddOpD1(0x51);
        p->AddOpD1(0x50);
		p->AddOpDL(0x0010);
        p->AddOpDL(0x0020);
        p->AddOpDL(0x0030);
        p->AddOpDL(0x0040);
        p->AddOpDL(0x0050);
        p->AddOpDL(0x0060);
        p->AddOpDL(0x0070);
        p->AddOpDL(0x0080);
        p->AddOpDL(0x0090);
        p->AddOpDL(0x00a0);
        p->AddOpDL(0x00b0);
        p->AddOpDL(0x00c0);
        p->AddOpDL(0x00d0);
        p->AddOpDL(0x00e0);
        p->AddOpDL(0x00f0);
        p->AddOpDL(0x0100);
		p->AddOpDL(0x0110);
        p->AddOpDL(0x0120);
        p->AddOpDL(0x0130);
        p->AddOpDL(0x0140);
        p->AddOpDL(0x0150);
        p->AddOpDL(0x0160);
        p->AddOpDL(0x0170);
        p->AddOpDL(0x0180);
        p->AddOpDL(0x0190);
        p->AddOpDL(0x01a0);
        p->AddOpDL(0x01b0);
        p->AddOpDL(0x01c0);
        p->AddOpDL(0x01d0);
        p->AddOpDL(0x01e0);
        p->AddOpDL(0x01f0);
        p->AddOpDL(0x0200);
		p->AddOpDL(0x0210);
        p->AddOpDL(0x0220);
        p->AddOpDL(0x0230);
        p->AddOpDL(0x0240);
        p->AddOpDL(0x0250);
        p->AddOpDL(0x0260);
        p->AddOpDL(0x0270);
        p->AddOpDL(0x0280);
        p->AddOpDL(0x0290);
        p->AddOpDL(0x02a0);
        p->AddOpDL(0x02b0);
        p->AddOpDL(0x02c0);
        p->AddOpDL(0x02d0);
        p->AddOpDL(0x02e0);
        p->AddOpDL(0x02f0);
        p->AddOpDL(0x0300);
		p->AddOpDL(0x0310);
        p->AddOpDL(0x0320);
        p->AddOpDL(0x0330);
        p->AddOpDL(0x0340);
        p->AddOpDL(0x0350);
        p->AddOpDL(0x0360);
        p->AddOpDL(0x0370);
        p->AddOpDL(0x0380);
        p->AddOpDL(0x0390);
        p->AddOpDL(0x03a0);
        p->AddOpDL(0x03b0);
        p->AddOpDL(0x03c0);
        p->AddOpDL(0x03d0);
        p->AddOpDL(0x03e0);
        p->AddOpDL(0x03f0);
        p->AddOpDL(0x0400);
		p->AddOpDL(0x0410);
        p->AddOpDL(0x0420);
        p->AddOpDL(0x0430);
        p->AddOpDL(0x0440);
        p->AddOpDL(0x0450);
        p->AddOpDL(0x0460);
        p->AddOpDL(0x0470);
        p->AddOpDL(0x0480);
        p->AddOpDL(0x0490);
        p->AddOpDL(0x04a0);
        p->AddOpDL(0x04b0);
        p->AddOpDL(0x04c0);
        p->AddOpDL(0x04d0);
        p->AddOpDL(0x04e0);
        p->AddOpDL(0x04f0);        
        p->AddOpDL(0x0500);
		p->AddOpDL(0x0510);
        p->AddOpDL(0x0520);
        p->AddOpDL(0x0530);
        p->AddOpDL(0x0540);
        p->AddOpDL(0x0550);
        p->AddOpDL(0x0560);
        p->AddOpDL(0x0570);
        p->AddOpDL(0x0580);
        p->AddOpDL(0x0590);
        p->AddOpDL(0x05a0);
        p->AddOpDL(0x05b0);
        p->AddOpDL(0x05c0);
        p->AddOpDL(0x05d0);
        p->AddOpDL(0x05e0);
        p->AddOpDL(0x05f0);      
        p->AddOpDL(0x0600);
		p->AddOpDL(0x0610);
        p->AddOpDL(0x0620);
        p->AddOpDL(0x0630);
        p->AddOpDL(0x0640);
        p->AddOpDL(0x0650);
        p->AddOpDL(0x0660);
        p->AddOpDL(0x0670);
        p->AddOpDL(0x0680);
        p->AddOpDL(0x0690);
        p->AddOpDL(0x06a0);
        p->AddOpDL(0x06b0);
        p->AddOpDL(0x06c0);
        p->AddOpDL(0x06d0);
        p->AddOpDL(0x06e0);
        p->AddOpDL(0x06f0);      
        p->AddOpDL(0x0c80);
        p->AddOpR(0xff);
        p->AddOpR(0x7f);
        p->AddOpR(0xc0);
        p->AddOpR(0xc1);
        p->AddOpR(0xc2);
        p->AddOpR(0xc3);
        p->AddOpR(0x40);
        p->AddOpR(0x41);
        p->AddOpR(0x42);
        p->AddOpR(0x43);
	p = new ProtocolWord(0x32,"������Բ�����ϵĵ��");
        p->AddOpD1(0xff);
        p->AddOpD1(0xc4);
        p->AddOpD1(0xc5);
        p->AddOpD2(0xff);
        p->AddOpD2(0xc4);
        p->AddOpD2(0xc5);
        p->AddOpD2(0xa0);
        p->AddOpD2(0xb0);
		p->AddOpDL(0x0000);
        p->AddOpDL(0x0030);
        p->AddOpDL(0x0060);
        p->AddOpR(0xff);
        p->AddOpR(0x7f);
        p->AddOpR(0xc4);
        p->AddOpR(0xc5);
        p->AddOpR(0x44);
        p->AddOpR(0x45);
	p = new ProtocolWord(0x33,"������Բ�����ϵı���");
        p->AddOpD1(0xff);
        p->AddOpD1(0xc4);
        p->AddOpD1(0xc5);
		p->AddOpDL(0x0000);
        p->AddOpDL(0x0030);
        p->AddOpR(0xff);
        p->AddOpR(0x7f);
        p->AddOpR(0xc4);
        p->AddOpR(0xc5);
        p->AddOpR(0x44);
        p->AddOpR(0x45);
	p = new ProtocolWord(52,"������Բ�����ϵĵ��");
        p->AddOpD1(0xff);
        p->AddOpD1(0xc0);
        p->AddOpD1(0xc1);
        p->AddOpD1(0xc2);
        p->AddOpD1(0xc3);
        p->AddOpD1(0x80);
        p->AddOpD2(0xff);
        p->AddOpD2(0xc4);
        p->AddOpD2(0xc5);
        p->AddOpD2(0xa0);
        p->AddOpD2(0xb0);
		p->AddOpDL(0x0000);
        p->AddOpDL(0x0018);
        p->AddOpDL(0x0030);
        p->AddOpDL(0x0048);
        p->AddOpR(0xff);
        p->AddOpR(0x7f);
        p->AddOpR(0xc4);
        p->AddOpR(0xc5);
        p->AddOpR(0x44);
        p->AddOpR(0x45);
	p = new ProtocolWord(170,"�ڲ�ʹ�ã��������");
}
const char * CProtocolTestDlg::GetProtocolName(int type)
{
	ProtocolWord * cur = root;
	while (cur)
	{
		if (cur->ID == (unsigned)type) 
			return cur->name;
		cur = cur->next;
	}
	return "δ֪Э��!";
}

bool CProtocolTestDlg::CheckOP(CString &msg)
{
	unsigned rxT = rxType & 0xff;
	ProtocolWord * cur = root;
	while (cur)
	{
		if (cur->ID == rxT) return cur->Check(rxType,rxAttr, msg);
		cur = cur->next;
	}
	msg = "Э��ų���!";
	return false;
}
void CProtocolTestDlg::OnOK() 
{
	UpdateData(TRUE);
	CString msg;
	rxfp = txfp = logfp = NULL;
	rxok = txok = false;
	errorList.RemoveAll();
	m_ListBox.ResetContent();
	R0 = 1;
	R1 = 1;
	R2 = 1;
	R3 = 1;
	if (m_strRxFileName.IsEmpty()) AddErrorMessage("Ӧ��ѡ��Э���ļ�!");
	else
	{
		protcount = txLineCount = rxLineCount = 1;

		rxfp = fopen(m_strRxFileName, "rt");
		txfp = fopen(m_strTxFileName, "rt");
		logfp = fopen(m_strLogFileName, "wt");

		FILE *paramfp = NULL;
		if (!m_strParamFileName.IsEmpty())
			paramfp= fopen(m_strParamFileName, "rt");
		ecc.bitLength = 288;
		if (paramfp)
		{
			msg.Format("�������ļ�%s....", m_strParamFileName);
			ecc.Pr.ReadHex(paramfp);
			ecc.A.ReadHex(paramfp);
			ecc.N.ReadHex(paramfp);
			ecc.P0.ReadHex(paramfp);
			K.ReadHex(paramfp);
			Pu.ReadHex(paramfp);
			m_KeyList.ReadFile(paramfp);
			fclose(paramfp);
		}
		else
		{
			if (!m_strParamFileName.IsEmpty())
				msg.Format("�����ļ�%s������",m_strParamFileName);
			else 
				msg.Format("δ�趨�����ļ�");
			ecc.Pr.  SetHex("BDB6F4FE3E8B1D9E0DA8C0D46F4C318CEFE4AFE3B6B8551F");
			ecc.A.   SetHex("BB8E5E8FBC115E139FE6A814FE48AAA6F0ADA1AA5DF91985");
			ecc.N.   SetHex("BDB6F4FE3E8B1D9E0DA8C0D40FC962195DFAE76F56564677");
			ecc.P0.x.SetHex("4AD5F7048DE709AD51236DE65E4D4B482C836DC6E4106640");
			ecc.P0.y.SetHex("02BB3A02D4AAADACAE24817A4CA3A1B014B5270432DB27D2");
			K.       SetHex("3ac0e717eb61602efcbb1de81aa144a272b44ba1f16936ac");
			Pu.x.    SetHex("7e1969fd0b001810a4e7f414c23f2badf6b2de96ae6b7856");
			Pu.y.    SetHex("29426771edd3001f4a4253d8eeb9ffc18684c6c0b43aca08");
			ecc.B.   SetHex("1854BEBDC31B21B7AEFC80AB0ECD10D5B1B3308E6DBF11C1");
		}
		m_ListBox.InsertString(-1, msg);
		P = ecc.Pr;
		A = ecc.A;
		N = ecc.N;
		P0 = ecc.P0;
		
		if (rxfp == NULL)
			AddErrorMessage("�ļ�%s�򿪳���!", m_strRxFileName);
		else rxok = true;
		if (txfp == NULL)
			AddErrorMessage("�ļ�%s�򿪳���!", m_strTxFileName);
		else txok = true;
		if (logfp == NULL)
			AddErrorMessage("�ļ�%s�򿪳���!", m_strLogFileName);
		while (rxok || txok)
		{
			AddMessage("\n-------- �� %d ��Э�� rx line: %d, tx line: %d -------", protcount, rxLineCount, txLineCount);
			if (rxok)
			{
				if (!ReadRxFile())
				{
					AddMessage("����Э�����");
					rxok = false;
				}
			}
			if (txok)
			{
				if (!ReadTxFile())
				{
					AddMessage("Ӧ��Э�����");
					txok = false;
				}
			}
			Process();
			protcount++;
		}
		int errors = errorList.GetCount();
		if (errors)
		{
			msg.Format("============��Ǹ! ������%d������, �б�����===================", errors);
			m_ListBox.InsertString(-1, msg);
			
			POSITION pos = errorList.GetHeadPosition();
			while (pos)
			{
				CString &s = errorList.GetNext(pos);
				m_ListBox.InsertString(-1, s);
				if (logfp) fprintf(logfp, "%s\n", s);
			}
		}
		else 
		{
			msg = "======= ף����! ����Э����֤���� ! =================";
			m_ListBox.InsertString(-1, msg);
		}
	}
	if (rxfp) fclose(rxfp);
	if (txfp) fclose(txfp);
	if (logfp) fclose(logfp);

	UpdateData(FALSE);
}
static unsigned int hextoi(const char *hex)
{
	int data = 0;
	while (*hex)
	{
		char c = *hex;
		int d;
		if (c >= 'a' && c <= 'f') d = c - 'a' + 10;
		else if (c >= 'A' && c <= 'F') d = c - 'A' + 10;
		else if (isdigit(c)) d = c - '0';
		else break;
		data <<= 4;
		data += d;
		hex++;
	}
	return data;
}
// �ú�������һ��Э��
bool CProtocolTestDlg::ReadTxFile()
{
	int i,s;
	while (1)
	{
		s = ReadLine(txfp);
		if (s == 1) break;
		else if (s == -1)
		{
			AddErrorMessage("Ӧ��Э���ʽ����!");
			break;
		}
		txType = hextoi(buffer);//������
		txdata[0] = txType;
		s = ReadLine(txfp);
		if (s != 0) 
		{
			AddErrorMessage("Ӧ��Э���ʽ����!");
			break;
		}
		txAttr = hextoi(buffer);//������
		txdata[1] = txAttr;
		int len = (txAttr & 0xffff0000) >> 16;
		if ((len & 3)  ||
			(len >> 2) > 1000 ) 
		{
			AddErrorMessage("Ӧ�����ݳ��ȳ���!");
			break;
		}
		else
		{
			for (i = 0; i < len/4; i++)
			{
				s = ReadLine(txfp);
				if (s != 0) 
				{
					AddErrorMessage("Ӧ�����ݳ��Ȳ���!");
					break;
				}
				txdata[i+2] = hextoi(buffer);
			}
			s = ReadLine(txfp);
			if (s != 0) 
			{
				AddErrorMessage("Ӧ��������У��� 0 !");
				break;
			}
			txchksum0 = hextoi(buffer);
			txdata[i+2] = txchksum0;
			s = ReadLine(txfp);
			
			if (s != 0) 
			{
				AddErrorMessage("Ӧ��������У��� 1 !");
				break;
			}
			txchksum1 = hextoi(buffer);
			break;
		}
	}
	if (s == 0) ToEmptyLine(txfp);
	return s != 1;
}
bool CProtocolTestDlg::ReadRxFile()
{
	int i, s = 0;
	while (1)
	{
		s = ReadLine(rxfp);
		if (s == 1) break;
		else if (s == -1)
		{
			AddErrorMessage("����Э���ʽ����!");
			break;
		}
		rxType = hextoi(buffer);//������
		rxdata[0] = rxType;
		s = ReadLine(rxfp);
		if (s != 0) 
		{
			AddErrorMessage("����Э���ʽ����!");
			break;
		}
		rxAttr = hextoi(buffer);//������
		rxdata[1] = rxAttr;
		int len = (rxAttr & 0xffff0000) >> 16;
		if ((len & 3) ||
			(len >> 2) > 1000) 
		{
			AddErrorMessage("�������ݳ��ȳ���!");
			break;
		}
		else
		{
			for (i = 0; i < len / 4; i++)
			{
				s = ReadLine(rxfp);
				if (s != 0) 
				{
					AddErrorMessage("�������ݳ��Ȳ���!");
					break;
				}
				rxdata[i + 2] = hextoi(buffer);
			}
			break;
		}
	}
	if (s == 0) ToEmptyLine(rxfp);
	return s != 1;
}
// ���� 1: ����
//      -1: ����
//	    0: ����
int CProtocolTestDlg::ReadLine(FILE *fp)
{
	while (fgets(buffer, 1000, fp))
	{
		if (fp == txfp) txLineCount++;
		else rxLineCount++;
		
		if (buffer[0] == '\n') return -1;
		else return 0;
	}
	return 1;
}
//
bool CProtocolTestDlg::ToEmptyLine(FILE *fp)
{
	bool bEmpty = false;
	while (fgets(buffer, 1000, fp))
	{
		if (fp == txfp) txLineCount++;
		else rxLineCount++;
		if (buffer[0] == '\n') break;
	}
	return false;
}

void CProtocolTestDlg::Process()
{
	int rxT = rxType & 0xff;
	int txT = txType & 0xff;
	CString datStr;
	AddMessage("����Э��(%d):%s", rxT, GetProtocolName(rxT));
	if (rxok && txok)
	{
		if (rxT != txT)	
			AddErrorMessage("�շ�Э����Ų�һ��!");
		if ((rxAttr&0xff) != (txAttr&0xff)) 
			AddErrorMessage("�շ�Э����ˮ�Ų�һ��!");
		CheckSum();
	}
	if (rxok)
	{
		CString msg;
		if(!CheckOP(msg)) 
			AddErrorMessage(msg);

		if (rxT == 10) // Ԥ��ģ��
		{
			segLength = rxdata[2];
			return;
		}
		else if (rxT != 1 && segLength == 0)
		{
			AddErrorMessage("ִ���κ�����Э��֮ǰ��һ��Ҫ��Ԥ��ģ��");
			return;
		}
		data = &rxdata[2];
		if (rxType & 0x80000000) modV = N;
		else modV = P;

		if (rxT == 15) EccPreSet();			// Ԥ����Բ���߲���
		else if (rxT == 1) SelfTest();		// �Լ�
		else if (rxT == 20) PrivatePreSet();//Ԥ���û�˽Կ
		else if (rxT == 25) PublicPreSet();	//"Ԥ���û���Կ"
		else if (rxT == 30) Random();		//"���������",
		else if (rxT == 35) GenerateKeys();	//"������Բ������Կ��"
		else if (rxT == 100) Encrypt();		//"����",
		else if (rxT == 101) Decrypt();		//"����",
		else if (rxT == 102) Sign();		//"ǩ��",
		else if (rxT == 103) Verificatiaon();//"����",
		else if (rxT == 40) IsZero();		//"��������:�ж�ȫ��",
		else if (rxT == 41) Mod();			//"��������:Լ��",
		else if (rxT == 42) ModAdd();		//"��������:ģ��",
		else if (rxT == 43) ModSub();		//"��������:ģ��",
		else if (rxT == 44) ModMulti();		//"��������:ģ��",
		else if (rxT == 45) Inv();			//"��������:����",
		else if (rxT == 46) Hash();			//"��������:HASH",
		else if (rxT == 50) QAddP();		//"������Բ�����ϵĵ��",
		else if (rxT == 51) QAddQ();		//"������Բ�����ϵı���",
		else if (rxT == 52) KP();			//"������Բ�����ϵĵ��",
	}
}

void CProtocolTestDlg::SetMSegInt(MSegInt &m)
{
	m.Clear();
	data += segLength;
	for (int i = 0; i < segLength; i++)
	{
		data --;
		m <<= 32;
		m += *data;
	}
	data += segLength;
}

void CProtocolTestDlg::CheckSum()
{
	unsigned q = 0x55555555;
	unsigned s = 0x55555555;
	int len = rxAttr >> 18;
	len += 2;
	for (int i = 0; i < len; i++)
	{
		q += rxdata[i];
		if(q < rxdata[i]) q++;
		s += q;
		if(s < q) s++;
	}
	if (s != txchksum0)
		AddErrorMessage("Ӧ��Э����CheckSum 0 ����!");
	q = 0x55555555;
	s = 0x55555555;
	len = txAttr >> 18;
	len += 3;
	for (i = 0; i < len; i++)
	{
		q += txdata[i];
		if (q < txdata[i]) q++;
		s += q;
		if (s < q) s++;
	}
	if (s != txchksum1)
		AddErrorMessage("Ӧ��Э����CheckSum 1 ����!");
}

void CProtocolTestDlg::CheckTxDataLen(int len)
{
	int dlen = txAttr >> 18;
	if (dlen % segLength) 
		AddErrorMessage("Ӧ��Э�������ݳ��Ȳ���ģ���ı���!");
	else if ((dlen/segLength) != len)
		AddErrorMessage("Ӧ��Э�������ݳ��Ȳ�����Ҫ��!");
}

void CProtocolTestDlg::OnBrowserParam() 
{
	CFileDialog dlg(TRUE, NULL, NULL,
		OFN_HIDEREADONLY | OFN_ENABLESIZING, "*.txt|*.txt||");	
	if (dlg.DoModal() == IDOK)
	{
		m_strParamFileName = dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CProtocolTestDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	ProtocolWord * cur = root;
	ProtocolWord * next;
	while (cur)
	{
		next = cur->next;
		delete cur;
		cur = next;
	}
}
