// ExpRamTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ExpRamTest.h"
#include "ExpRamTestDlg.h"

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
// CExpRamTestDlg dialog

CExpRamTestDlg::CExpRamTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExpRamTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExpRamTestDlg)
	m_strDataFileName = _T("");
	m_strParamFileName = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExpRamTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExpRamTestDlg)
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Text(pDX, IDC_DATA_FILENAME, m_strDataFileName);
	DDX_Text(pDX, IDC_PARAM_FILENAME, m_strParamFileName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExpRamTestDlg, CDialog)
	//{{AFX_MSG_MAP(CExpRamTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BROWSER, OnBrowser)
	ON_BN_CLICKED(IDC_BROWSERPARAM, OnBrowserParam)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExpRamTestDlg message handlers

BOOL CExpRamTestDlg::OnInitDialog()
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

void CExpRamTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CExpRamTestDlg::OnPaint() 
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
HCURSOR CExpRamTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CExpRamTestDlg::OnBrowser() 
{
	CFileDialog dlg(TRUE,NULL,NULL,
		OFN_HIDEREADONLY | OFN_ENABLESIZING,"*.data|*.data||");	
	if(dlg.DoModal()==IDOK)
	{
		m_strDataFileName = dlg.GetPathName();
		UpdateData(FALSE);
	}
}
#include "..\ECCLib\Include\MSegInt.h"

void CExpRamTestDlg::OnOK() 
{
	FILE *fp = fopen(m_strDataFileName,"rt");
	CString msg;
	if(fp == NULL)
	{
		msg.Format("文件%s打开出错!",m_strDataFileName);
		m_ListBox.InsertString(-1,msg);
	}
	else
	{
		MSegInt P,A,B,N,R,Ku,P1x,P1y;
		ECC  ecc;
		ecc.bitLength = 288;
		ecc.A.SetHex("BB8E5E8FBC115E139FE6A814FE48AAA6F0ADA1AA5DF91985");
		ecc.B.SetHex("1854BEBDC31B21B7AEFC80AB0ECD10D5B1B3308E6DBF11C1");
		ecc.Pr.SetHex("BDB6F4FE3E8B1D9E0DA8C0D46F4C318CEFE4AFE3B6B8551F");
		ecc.N.SetHex("BDB6F4FE3E8B1D9E0DA8C0D40FC962195DFAE76F56564677");
		ecc.P0.x.SetHex("4AD5F7048DE709AD51236DE65E4D4B482C836DC6E4106640");
		ecc.P0.y.SetHex("02BB3A02D4AAADACAE24817A4CA3A1B014B5270432DB27D2");
		P1x.SetHex("7e1969fd0b001810a4e7f414c23f2badf6b2de96ae6b7856");
		P1y.SetHex("29426771edd3001f4a4253d8eeb9ffc18684c6c0b43aca08");
		Ku.SetHex("3ac0e717eb61602efcbb1de81aa144a272b44ba1f16936ac");
		FILE *paramfp = fopen(m_strParamFileName,"rt");
		if(paramfp)
		{
			msg.Format("读参数文件%s....",m_strParamFileName);
			m_ListBox.InsertString(-1,msg);
			ecc.Pr.ReadHex(paramfp);
			ecc.A.ReadHex(paramfp);
			ecc.N.ReadHex(paramfp);
			ecc.P0.ReadHex(paramfp);
			Ku.ReadHex(paramfp);
			P1x.ReadHex(paramfp);
			P1y.ReadHex(paramfp);
			fclose(paramfp);
		}
		else
		{
			msg.Format("参数文件%s不存在",m_strParamFileName);
			m_ListBox.InsertString(-1,msg);
		}
		ecc.PrepareV16(288);
		P = ecc.Pr;
		A = ecc.A;
		B = ecc.B;
		N = ecc.N;
		R = ecc.R;
		msg.Format("读数据文件%s....",m_strDataFileName);
		m_ListBox.InsertString(-1,msg);
		MSegInt expRam[256];
		char buffer[1000];
		for(int i=0; i < 256/3; i++)
		{
			fgets(buffer,1000,fp);
			expRam[i].SetHex(buffer);
			msg.Format("ExpRam[%02x]=%s",i,buffer);
			m_ListBox.InsertString(-1,msg);
			fgets(buffer,1000,fp);
			expRam[i+0x40].SetHex(buffer);
			msg.Format("ExpRam[  ]=%s",buffer);
			m_ListBox.InsertString(-1,msg);
			fgets(buffer,1000,fp);
			expRam[i+0x80].SetHex(buffer);
			msg.Format("ExpRam[  ]=%s",buffer);
			m_ListBox.InsertString(-1,msg);
		}
		CString str0,str1;
		char *name;
		int index;
		MSegInt t0,t1,t2;
		CString str;
		index = 0x9a;	
		name = "0";
		t0 = expRam[index];
		SetList((t0 == 0),index,name);

		index = 0x9b;	
		name = "1";
		t0 = expRam[index];
		SetList((t0 == 1),index,name);
		
		t1 = Ku;
		t1.NAFCode(3);
		index = 0x9c; 
		name = "Ku";
		t0 = expRam[index];
		SetList((t0 == t1),index,name);
		
		index = 0x9d;
		name = "3Rn";
		t1 = expRam[index];
		t0 = expRam[0x5b];
		t0 *= 3;
		SetList((t0 == t1),index,name);

		index = 0x9e;
		name = "3Rp";
		t0 = expRam[index];
		t1 = expRam[0x5e];
		SetList((t0 == t1),index,name);

		index = 0x9f;	
		name = "aRp";
		t0 = expRam[index];
		t0.ReduceByM(P,288);
		SetList((t0 == A),index,name);

		index = 0xa0;
		name = "3aRp";
		t1 = expRam[index];
		t0 = expRam[0x1f];
		t0 *= 3;
		SetList((t0 == t1),index,name);

		index = 0xa1;	
		name = "Td";
		t0 = expRam[index];
		t1.SetHex("E250_830ED1F2_46FECF0D_C6D305D0_C20F73CF_0F05D70F_9EC70C10_830E18E3");
		SetList((t0 == t1),index,name);

		index = 0xa2;
		name = "Ta1";
		t0 = expRam[index];
		t1.SetHex("E43F70C_1AF70C18_D70C5193_0F91870E_CDE10C14_670C19CF_0C1E810C_14FB0C14_510C14D3");
		SetList((t0 == t1),index,name);

		index = 0xa3;	
		name = "R2n";
		t0 = expRam[index];
		t0.ReduceByM(N,288*2);
		SetList((t0 == 1),index,name);

		index = 0xa4;	
		name = "R2p";
		t0 = expRam[index];
		t0.ReduceByM(P,288*2);
		SetList((t0 == 1),index,name);
		
		index = 0xa5;	
		name = "R16n";
		t1 = expRam[index];
		SetList((t1 == 0x10000),index,name);
	
		index = 0xa6;	
		name = "R16p";
		t1 = expRam[index];
		SetList((t1 == 0x10000),index,name);

		index = 0xa7;	
		name = "kRn";
		t0 = expRam[index];
		t0.ReduceByM(N,288);
		SetList((t0 == k),index,name);

		index = 0xa8;
		name = "Ta2";
		t0 = expRam[index];
		t1.SetHex("E250830E_86FA0C17_C70C1BEF_0F89EB06_44D24411_C70F9BD1");
		SetList((t0 == t1),index,name);

		index = 0xa9;
		name = "Ta3";
		t0 = expRam[index];
		t1.SetHex("C03DB04_C4D20D5D_F70D8BFB_4413FB0E_DB930E1B_AF0C0DE0_0C15810F_94BB0C14_510C14D3");
		SetList((t0 == t1),index,name);

		index = 0xaa;
		name = "Ta4";
		t0 = expRam[index];
		t1.SetHex("E150830F_8AE61916_B70C1AEB");
		SetList((t0 == t1),index,name);

		for(index = 0xab; index < 0xb0; index++)
			SetList(true,index,NULL);
		
		index = 0x5a;
		name = "Nmi";
		t0 = expRam[index];
		t1 = N;
		if(t1 != 0)
		{
			while(t1.TestBit(276) == 0) 
				t1<<= 1;
		}
		t1 += 1;
		SetList(t0 == t1,index,name);

		index = 0x5b;	
		name = "Rn";
		t0 = expRam[index];
		t0 %= N;
		t1 = N;
		t1.ChangToR(288);
		SetList((t0 == t1),index,name);

		for(i = 0x1c; i < 0x30; i ++)
		{
			t0 = expRam[i];
			t0 *= 3;
			t1 = expRam[i+0x40];
			str.Format("ExpRam[%02x]的3倍",i);
			SetList((t0 == t1),i+0x40,str);
		}

		index = 0x1a;
		name = "Pmi";
		t0 = expRam[index];
		t1 = P;
		if(t1 != 0)
		{
			while(t1.TestBit(276) == 0) 
				t1<<= 1;
		}
		t1 += 1;
		SetList(t0 == t1,index,name);

		index = 0x1b;	
		name = "Rp";
		t0 = expRam[index];
		t0 %= P;
		SetList((t0 == R),index,name);

		ECCMix p;
		index = 0x1c;	
		name = "P0.xR";
		p.x = expRam[index];
		p.x.ReduceByM(P,288);
		SetList((p.x == ecc.P0.x),index,name);

		index = 0x1d;	
		name = "P0.yR";
		p.y = expRam[index];
		p.y.ReduceByM(P,288);
		SetList((p.y == ecc.P0.y),index,name);

		index = 0x1e;	
		name = "P0.zR";
		p.z = expRam[index];
		p.z %= P;
		SetList((p.z == ecc.R),index,name);

		index = 0x1f;	
		name = "P0.aRp";
		t0 = expRam[index];
		t0 %= P;
		SetList((t0 == ecc.RA),index,name);

		index = 0x20;	
		name = "P0.-yR";
		t0 = expRam[index];
		
		// 生成 -yR
		//t0 = P;
		//t0 <<= 18; // P * 2^18
		//t0 -= expRam[0x1d];//-yR

		t0.ReduceByM(P,288);
		t0 %= P;
		t1 = P;
		t1 -= t0;
		SetList((t1 == ecc.P0.y),index,name);

		t0 = 3;
		ECCAff paff;
		ecc.kP0(t0,paff);
		
		index = 0x21;	
		name = "3P0.xR";
		p.x = expRam[index];
		p.x.ReduceByM(P,288);
		SetList((p.x == paff.x),index,name);

		index = 0x22;	
		name = "3P0.yR";
		p.y = expRam[index];
		p.y.ReduceByM(P,288);
		SetList((p.y == paff.y),index,name);

		index = 0x23;	
		name = "3P0.zR";
		p.z = expRam[index];
		p.z %= P;
		SetList((p.z == ecc.R),index,name);
		
		index = 0x24;	
		name = "3P0.aRp";
		t0 = expRam[index];
		t1 = expRam[0x1f];
		SetList((t0 == t1),index,name);

		index = 0x25;	
		name = "3P0.-yR";
		t0 = expRam[index];
		t0.ReduceByM(P,288);
		t1 = P;
		t1 -= t0;
		SetList((t1 == paff.y),index,name);

		ECCAff P1;
		P1.x.SetHex("7E1969FD0B001810A4E7F414C23F2BADF6B2DE96AE6B7856");
		P1.y.SetHex("29426771EDD3001F4A4253D8EEB9FFC18684C6C0B43ACA08");
		
		/////
		index = 0x26;	
		name = "P1.xR";
		p.x = expRam[index];
		p.x.ReduceByM(P,288);
		SetList((p.x == P1.x),index,name);

		index = 0x27;	
		name = "P1.yR";
		p.y = expRam[index];
		p.y.ReduceByM(P,288);
		SetList((p.y == P1.y),index,name);

		index = 0x28;	
		name = "P1.zR";
		p.z = expRam[index];
		p.z %= P;
		SetList((p.z == ecc.R),index,name);

		index = 0x29;	
		name = "P1.aRp";
		t0 = expRam[index];
		t0 %= P;
		SetList((t0 == ecc.RA),index,name);

		index = 0x2a;	
		name = "P1.-yR";
		t0 = expRam[index];
		t0.ReduceByM(P,288);
		t1 = P;
		t1 -= t0;
		SetList((t1 == P1.y),index,name);

		k = 3;
		paff.x = P1.x;
		paff.y = P1.y;
		ecc.kP(k,paff);
		
		index = 0x2b;	
		name = "3P1.xR";
		p.x = expRam[index];
		p.x.ReduceByM(P,288);
		SetList((p.x == paff.x),index,name);

		index = 0x2c;	
		name = "3P1.yR";
		p.y = expRam[index];
		p.y.ReduceByM(P,288);
		SetList((p.y == paff.y),index,name);

		index = 0x2d;	
		name = "3P1.zR";
		p.z = expRam[index];
		p.z %= P;
		SetList((p.z == ecc.R),index,name);
		
		index = 0x2e;	
		name = "3P1.aRp";
		t0 = expRam[index];
		t1 = expRam[0x1f];
		SetList((t0 == t1),index,name);

		index = 0x2f;	
		name = "3P1.-yR";
		t0 = expRam[index];
		t0.ReduceByM(P,288);
		t1 = P;
		t1 -= t0;
		SetList((t1 == paff.y),index,name);
	}
	fclose(fp);
}
static const char * errorstr = "ExpRam[%02x] = %s is ERROR";
static const char * okstr = "ExpRam[%02x] = %s is OK";
void CExpRamTestDlg::SetList(bool isok,int index,const char * name)
{
	const char * resStr = isok ? okstr:errorstr;
	CString msg;
	if(name) msg.Format(resStr,index,name);
	else msg.Format("ExpRam[%02x] = NULL",index);
	m_ListBox.InsertString(-1,msg);
}

void CExpRamTestDlg::OnBrowserParam() 
{
	CFileDialog dlg(TRUE,NULL,NULL,
		OFN_HIDEREADONLY | OFN_ENABLESIZING,"*.txt|*.txt||");	
	if(dlg.DoModal()==IDOK)
	{
		m_strParamFileName = dlg.GetPathName();
		UpdateData(FALSE);
	}
}
