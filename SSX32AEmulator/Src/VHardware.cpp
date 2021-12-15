// VHardware.cpp

#include "stdafx.h"
#include "..\Include\VHardware.h"
#include "..\Include\IntSource.h"
#include "..\..\Library\Include\xpthread.h"
#include "..\..\Library\Include\corethread.h"
#include "..\..\Emulator\Include\Emulator.h"
#include "..\Include\SSX32AEmulator.h"
#include "..\Include\ModuleSource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CVHardware g_Hardwre;

CVHardware::CVHardware()
{
	m_bRA2RAM = FALSE;
	m_bInterruptEN = FALSE;
	m_ResSel = 0;	
	int i;
	m_RF= 0x80000003;
	for(i = 0; i < 8; i++) m_BarrelReg[i] = 0;
	for(i = 0; i < 28; i++) m_RM[i] = 0;
	for(i = 0; i < 28; i++) m_RP[i] = 0;
	// Interrupt 初始化
	CIntTimer * pTimer = new CIntTimer();
	pTimer->SetEn(false);
	m_pIntSource[0] = pTimer;
	m_pIntSource[1] = new CASDSPReq();
	
	for(i = 2; i < 32; i ++)
	{
		m_pIntSource[i] = new CIntSource();
	}
	for(i = 0; i < 32; i ++)
	{
		m_bIntReg[i] = FALSE;
	}
	srand(0);
	m_pDumpFile = NULL;
	m_iDumpLine = 0;
}

CVHardware::~CVHardware()
{
	for(int i = 0; i < 32; i ++) 
	{
		delete m_pIntSource[i];
	}
	if(m_pDumpFile) fclose(m_pDumpFile);
}

void CVHardware::Reset(bool &err, CString &errmsg) // 
{
	int i;
	bool errtmp;
	CString str;
	// RB 初始化
	for(i = 0; i < 64; i ++) ClearRB(i, errtmp, str);
	// RF 初始化
	m_RF= 0x80000003;
	// RM 初始化
	for(i=0;i<28;i++) m_RM[i] = 0;
	// RP 初始化
	for(i=0;i<28;i++) m_RP[i] = 0;
	m_bRA2RAM = FALSE;
	m_bInterruptEN = FALSE;

	// Interrupt 初始化
	for(i = 0; i < 32; i ++)
	{
		m_pIntSource[i]->GetMessage(str);
		m_pIntSource[i]->Reset();
		m_bIntReg[i] = FALSE;
	}
	((CIntTimer*)m_pIntSource[0])->SetEn(false);

	m_ResState = 0;
	m_ResSel = 0;
	g_SSX32A_input.Reset(err, errmsg);
	g_SSX32A_output.Reset(err, errmsg);
	g_SSX32A_expram.Reset(err, errmsg);
	if(m_pDumpFile) fclose(m_pDumpFile);
	CString name = m_strProjectName + ".dump";
	m_pDumpFile = fopen(name,"wt");
	m_iDumpLine = 0;
	if(m_pDumpFile)
	{
		fprintf(m_pDumpFile,"==时间====任务号=====函数名===============================\n");
		err =true;
		CString str;
		str.Format("成功打开输入数据文件\"%s\"\r\n",name);
		errmsg += str;
	}
}
void CVHardware::SimEnd()
{
	for(int i = 0; i < 32; i ++)
		m_pIntSource[i]->SimEnd();
	g_SSX32A_input.SimEnd();
	g_SSX32A_output.SimEnd();
	g_SSX32A_expram.SimEnd();
	if(m_pDumpFile) fclose(m_pDumpFile);
	m_pDumpFile = NULL;
}

void CVHardware::SetRB(int index, bool &err, CString &errmsg)
{
	switch(index)
	{
	case RB_INT_EN: // 0x10
		m_bInterruptEN = TRUE; break;
	case RB_RA2ROM: // 0x11
		m_bRA2RAM = TRUE; break;
	case RB_DB1TOLSHIFT:	// 0x31  
		g_SSX32A_expram.DB1ToLShift(); 
		break;
	case RB_LSHIFTTODB1:	// 0x32 
		g_SSX32A_expram.LShiftToDB1(); 
		break;
	case RB_EXPRAMEN0: 
		g_SSX32A_expram.SetEn0(true,err,errmsg);
		break;
	case RB_EXPRAMEN1: 
		g_SSX32A_expram.SetEn1(true,err,errmsg);
		break;
	case RB_ACK: // 0x18
		Ack(true, err, errmsg);
		break;
	case RB_OUTERIOEN: // 0x19
		break;

	case RB_MOTRIGAB:		// 0x29
		break;
	case RB_MOTRIGX:		// 0x2a
		break;
	case RB_WMOX:			// 0x2b
		break;
	case RB_TIMERRESET:		// 0x33
		((CIntTimer*)m_pIntSource[0])->SetEn(true); break;
	default: ClearIntMask(index & 0x1f); break;
	}
}

void CVHardware::ClearRB(int index, bool &err, CString &errmsg)
{
	switch(index)
	{
	case RB_INT_EN: // 0x10
		m_bInterruptEN = FALSE; 
		break;
	case RB_RA2ROM: // 0x11
		m_bRA2RAM = FALSE; 
		break;
	case RB_EXPRAMEN0: 
		g_SSX32A_expram.SetEn0(false,err,errmsg);
		break;
	case RB_EXPRAMEN1: 
		g_SSX32A_expram.SetEn1(false,err,errmsg);
		break;
	case RB_ACK: // 0x18
		Ack(false, err, errmsg);
		break;
	case RB_OUTERIOEN: // 0x19
		break;

	default: SetIntMask(index & 0x1f); break;
	}
}

void CVHardware::Ack(bool ack, bool &err, CString &errmsg)
{
	if(m_ResSel & RES_INPUT)
		g_SSX32A_input.ACK(ack, err, errmsg);
	else if(m_ResSel & RES_OUTPUT)
		g_SSX32A_output.ACK(ack, err, errmsg);
	else if(m_ResSel & RES_ASDSP)
	{
		int scan = RES_ASDSP0;
		for(int id = 0; id < ASSDSP_NUM; id++)
		{
			if(scan&m_ResSel) break;
			scan <<= 1;
		}
		g_SSX32A_asdsp[id].ACK(ack, err, errmsg);
	}
}
void CVHardware::AccIR(int ir, bool &err, CString &errmsg)
{
	if(m_ResSel & RES_ASDSP)
	{
		int scan = RES_ASDSP0;
		for(int id = 0; id < ASSDSP_NUM; id++)
		{
			if(scan&m_ResSel) break;
			scan <<= 1;
		}
		g_SSX32A_asdsp[id].ASDSPIR(ir, err, errmsg);
	}
}
unsigned CVHardware::ResFlag()
{
	unsigned r = 0;
	if(g_SSX32A_input.IsReady()) r |= RES_INPUT;
	if(g_SSX32A_output.IsReady()) r |= RES_OUTPUT;
	int scan = RES_ASDSP0;
	for(int id = 0; id < ASSDSP_NUM; id++)
	{
		if(g_SSX32A_asdsp[id].IsReady()) r |= scan;
		scan <<= 1;
	}
	return r;
}

BOOL CVHardware::ReadRF(int index)
{
	return (m_RF >> index) & 0x1;
}

void CVHardware::WriteRF(int index , unsigned int data)
{
	if (data) m_RF |=   0x1 << index;
	else  m_RF &= ~(0x1 << index); 
}

unsigned int CVHardware::StackIn()
{
	return 
		((m_RF << 8 ) & (1<<31)) |
		((m_RF << 9 ) & (1<<30)) |
		((m_RF << 10) & (1<<29)) |
		((m_RF << 11) & (1<<28)) |
		((m_RF << 3 ) & (1<<27)) |
		((m_RF << 1 ) & (1<<26)) |
		((m_RF >> 2 ) & (1<<25)) |
		((m_RF >> 5 ) & (1<<24)) ;
}

void CVHardware::StackOut(unsigned s)
{
	unsigned t;
	m_RF &= 0x8000ffff;
	t =	((s&(1<<31))>>8 );
	t |= (((~s)&(1<<31))>>9 );
	t |= ((s&(1<<30))>>9 );
	t |= (((~s)&(1<<30))>>10);
	t |= ((s&(1<<29))>>10);
	t |= (((~s)&(1<<29))>>11);
	t |= ((s&(1<<28))>>11);
	t |= (((~s)&(1<<28))>>12);
	t |= ((s&(1<<27))>>3 );
	t |= ((s&(1<<26))>>1 );
	t |= ((s&(1<<25))<<2 );
	t |= (((~s)&(1<<25))<<1 );
	t |= ((s&(1<<24))<<5 );
	t |= (((~s)&(1<<24))<<4 );
	m_RF |= t;
}



int g_xianjun=0;
// Functions: define x=RP_n
// index: n
// data:  x
unsigned int CVHardware::ReadRP(int index,bool &err, CString &errmsg)
{
	unsigned r = m_RP[index];
	switch(index)
	{
	case RP_TXRDATA:		// 读输入缓冲区
		r = g_SSX32A_input.Read(err, errmsg); break;
	case RP_TXRDATA_LEN:	// 读输入字数
		r = g_SSX32A_input.GetCount(); break;
	case RP_LSHIFTDATA:		// 288-16 bit 转换过程读 16 bit
		r = g_SSX32A_expram.Read(err, errmsg);break;
	case RP_TASK_SEL:		// 读当前任务号
		r = g_SSX32A_ram.GetTaskID();break;
	case RP_RES_STATE:		// 读硬件使用状态字
		r = m_ResState;
		break;
	case RP_RES_ENABLE: 	// 读硬件可用状态字
		break;
	case RP_RES_SEL:		// 读硬件选择字
		r = m_ResSel;
		break;
	case RP_RES_FLAG:		// 读硬件申请信号
		r = ResFlag() & m_ResState;
		break;
	case RP_ASDSP:			// 读ASDSP数据端口288 bit数据读入？？
		break;
	case RP_ECCACC: 		// 读ECCACC数据端口288 bit数据读入？？
		break;
	case RP_DB1REG:  		// 读DB1总线寄存器288 bit数据读入？？
		break;
	case RP_CPUTIME:
		r = m_iSteps;
		break;
	case RP_BITINDEX:
		r = ReadRM(0); break;
	case RP_BITMASK:
		r = ReadRM(1); break;
	case RP_INTVECTOR:
		r = m_iIntVector; break;
    case RP_XIANJUN:
        /////////////////////////////////////////////////
        // test by xianjun:
        m_xianjun[0]*=m_xianjun[1];
        r=m_xianjun[0];
        /////////////////////////////////////////////////
        break;
	}
	return r;
}


// Functions: define RP_n=x
// index: n
// data:  x
void CVHardware::WriteRP(int index, unsigned int data, bool &err, CString &errmsg)
{
	m_RP[index] = data; 
	switch(index)
	{
	case RP_TIMERDATA: 
		m_pIntSource[0]->Write(data);
		break;
	case RP_TXRDATA: 		// 写输出缓冲区
		g_SSX32A_output.Write(data, err, errmsg); 
		break;
	case RP_TXRDATA_LEN: 	// 写输出字数
		g_SSX32A_output.SetCount(data); 
		break;
	case RP_LSHIFTDATA:		// 288-16 bit 转换过程写 16 bit
		g_SSX32A_expram.Write(data, err, errmsg);
		break;
	case RP_TASK_SEL:		// 写当前任务号
		if(data >= TASK_NUM) 
		{
			err = true;
			errmsg += "任务号超出正常范围";
		}
		g_SSX32A_expram.SetTask(data);
		g_SSX32A_ram.SetTask(data);
		break;
	case RP_EXPRAMIR: 
        break;
	case RP_ACCIR: 
		AccIR(data, err, errmsg);
		break;
	case RP_RES_STATE:		// 写硬件使用状态字
		m_ResState = data;
		break;
	case RP_RES_ENABLE: 	// 写硬件可用状态字
		break;
	case RP_RES_SEL:		// 写硬件选择字
		m_ResSel = data;
		break;
	case RP_ASDSP:			// 写ASDSP数据端口288 bit数据 来源？？
		break;
	case RP_ECCACC: 		// 写ECCACC数据端口288 bit数据 来源？？
		break;
	case RP_DB1REG:  		// 写DB1总线寄存器288 bit数据 来源？？
		break;
	case RP_BITMASK:
		WriteRM(0,data);break;
	case RP_BITINDEX:
		WriteRM(1,data);break;
	case RP_BARRELPORT:
		SetBarrelReg(data);break;
	case RP_INTVECTOR:
		ClearInt();break;
	case RP_TRACE:
		if(data & 0x800000)	Trace(data); break;
    /////////////////////////////////////////////////
    // test by xianjun:
    case RP_TEMP1:
        m_bRA2RAM = TRUE; 
        break;
    case RP_TEMP2:
        m_bRA2RAM = FALSE; 
        break;
    case RP_XIANJUN:
        if(g_xianjun==0)
            g_Hardwre.WriteRF(RF_XIANJUN, 0);
        m_xianjun[g_xianjun++]=data;
        if(g_xianjun==2)
            g_Hardwre.WriteRF(RF_XIANJUN, 1);
        break;
    /////////////////////////////////////////////////
	}
}

void CVHardware::Trace(unsigned data)
{
	if(data & RT_TRACE_EXIT ) g_pSSX32AEmulator->ExecStop(data & 0xff);
	else if(data & RT_TRACE_OUT ) g_pSSX32AEmulator->TraceOut(data & 0xff);
	else if(data & RT_TRACE_DUMP ) TraceDump(data & 0xff);
}

struct _dumpSt
{
	char * name;
	unsigned id;
};

static _dumpSt dumpType[] = 
{
	{"GetInput",1},
	{"GetOutput",2},
	{"GetASDSP",4},
	{"GetECC",8},
	{"Wait",16},
	{"Release",32},
	{"Return",128}
};

void CVHardware::TraceDump(unsigned data)
{
	if(m_pDumpFile)
	{
		int task = g_SSX32A_ram.GetTaskID();
		char *name = "Unkown";
		for(int i = 0; i < sizeof(dumpType)/sizeof(dumpType[0]); i ++)
		{
			if(data == dumpType[i].id) 
			{
				name = dumpType[i].name;
				break;
			}
		}
		fprintf(m_pDumpFile,"%08d\t%d\t\t%s\n",m_iSteps,task,name);
		m_iDumpLine++;
		if((m_iDumpLine % 20) == 0)
		fprintf(m_pDumpFile,"==时间====任务号=====函数名===============================\n");
	}
}


/*
#define ShiftR1                         FT0
#define RotateL24		                FT1
#define RotateL16		                FT2
#define RotateL8		                FT3
#define RotateL1		                FT4
#define RotateR1                        FT5
#define Reverse	                        FT6
#define Not			                    FT7
#define High16Set1                      FT15    // the input data should be 0X0000xxxx, the output is 0Xffffxxxx
#define Low16Set1_01                    FT15    // the input data should be 0X0001xxxx, the output is 0Xxxxxffff
#define Exp_03                          FT15    // the input data should be 0X0003xxxx, the output is 2^x
#define Log_04                          FT15    // the input data should be 0X0004xxxx, the output is int[log2(x)]
*/

// Functions: define FT_n(x)
// index: n
// data:  x
void CVHardware::Transfor(int index ,unsigned int &data)
{
    unsigned int u,v,r;

	switch(index)
	{
	case 0:                 // FT0: ShiftR1
        data>>=1;
		break;
	case 1:                 // FT1: RotateL24
		u=data;
        u>>=8;
        v=((data&0xff)<<24);
        u|=v;
        data=u;
        break;
    case 2:                 // FT2: RotateL16
		u=data;
        u>>=16;
        v=((data&0xffff)<<16);
        u|=v;
        data=u;
        break;		
    case 3:                 // FT3: RotateL8
		u=data;
        u>>=24;
        v=((data&0xffffff)<<8);
        u|=v;
        data=u;
        break;		
    case 4:                 // FT4: RotateL1
		u=data;
        u>>=31;
        v=((data&0x7fffffff)<<1);
        u|=v;
        data=u;
        break;		
    case 5:                 // FT5: RotateR1
		u=data;
        u>>=1;
        v=((data&0x1)<<31);
        u|=v;
        data=u;
        break;		
    case 6:                 // FT6: Reverse
		r = data;
		r = ((r&0xaaaaaaaa) >> 1) | ((r&0x55555555) << 1);
		r = ((r&0xcccccccc) >> 2) | ((r&0x33333333) << 2);
		r = ((r&0xf0f0f0f0) >> 4) | ((r&0x0f0f0f0f) << 4);
		r = ((r&0xff00ff00) >> 8) | ((r&0x00ff00ff) << 8);
		r = (            r  >>16) | (             r <<16);
		data = r;
        break;		
    case 7:                 // FT7: Not
        data = ~data;
        break;		
    case 15:                // FT15: 
        r=(data&0xffff0000);
        if(r==0x00000000)           // High16Set1
            data|=0xffff0000;
        else if(r==0x00010000)      // Low16Set1_01
        {
            data<<=16;
            data|=0x0000ffff;
        }
        else if(r==0x00030000)      // Exp_03
        {
            u=(data&0x0000ffff);
            data=(1<<u);
        }        
        else if(r==0x00040000)      // Log_04
        {
            data<<=16;
            for(u=15;u>0;u--)
            {
                if(data&0x80000000)
                    break;
                else
                    data<<=1;
            }
            data=u;
        }                
        break;		    
    }// end of switch(index)

    MaskFlag(data);
	return;
}

void CVHardware::MaskFlag(unsigned int data)
{
	int mask = ReadRM(RM_MASK);
	unsigned test = 1 <<(ReadRM(1) & 0x1f);
	WriteRF(RF_EXFLAG, test & data);
	WriteRF(RF_NEXFLAG, (test & data) == 0);
	WriteRF(RF_BITZERO, (mask & data) == 0);
	WriteRF(RF_NBITZERO, (mask & data) != 0);
	WriteRF(RF_ZERO, data == 0);
	WriteRF(RF_NZERO, data != 0);
}

void CVHardware::SetBarrelReg(unsigned int data)
{
	int test = 0x100;
	int index = 0;
	for(;index < 8; index ++)
	{
		if(data & test)
		{
			m_BarrelReg[index] = data & 0xff;
		}
		test <<= 1;
	}
}

BOOL CVHardware::Interrupt()
{
	if( m_bInterruptEN )
	{
		// 3. 取出当前处理的中断级别
		for(int Reg = 0; Reg < 32; Reg ++) 
		{
			if(m_bIntReg[Reg]) break;
		}
		// 4. 检查发生的最高优先级别中断
		for(int Src = 0; Src < 32; Src ++) 
		{
			if(m_pIntSource[Src]->IsActive()) break;
		}
		// 5. 与当前处理的中断比较
		if(Reg > Src)
		{
			// 7. 记录当前处理中断级别
			m_bIntReg[Src] = TRUE;
			// 8.产生中断向量
			m_iIntVector = Src*2+0x100;
			m_bInterruptEN = FALSE;		// 禁止中断
			WriteRF(RF_INTERRUPT,1);	// 置中断标志
			return TRUE;
		}
	}
	return FALSE;
}

void  CVHardware::SetProjectName(CString& str)
{
	CString strFile;
	for(int i = 0; i < 32; i ++)
	{
		strFile.Format("%s.int%02d",str,i);
		m_pIntSource[i]->Setup(strFile);
		m_bIntReg[i] = FALSE;
	}
	g_SSX32A_input.SetProjectName(str);
	g_SSX32A_output.SetProjectName(str);
	g_SSX32A_expram.SetProjectName(str);
	g_SSX32A_ram.SetProjectName(str);
	m_strProjectName = str;
}

void  CVHardware::GetIntMessage(CString& str)
{
	//str += "\r\n";
	CString s;
	for(int i = 0; i < 32; i ++)
	{
		m_pIntSource[i]->GetMessage(s);
		str += s;
	}
}
void  CVHardware::SetIntMask(int index)
{
	m_pIntSource[index]->SetMask();	//将中断屏蔽
}
void  CVHardware::ClearIntMask(int index)
{
	m_pIntSource[index]->ClearMask();	//将中断使能
}

// 每次解释执行指令之前，调用此过程
void  CVHardware::Idle(int iStepCount)
{
	m_iSteps = iStepCount;
	// 1. 锁存所有发生的中断
	for(int i = 0; i < 32; i ++) 
	{
		m_pIntSource[i]->Idle(iStepCount);
	}
	if( m_bInterruptEN )
	{	// 2. 锁存可以接收的中断标志
		for(int i = 0; i < 32; i ++) 
		{
			m_pIntSource[i]->LatchInt();
		}
	}

	g_SSX32A_input.Idle(iStepCount);
	g_SSX32A_output.Idle(iStepCount);
	for(i = 0; i < ASSDSP_NUM; i ++)
	{
		g_SSX32A_asdsp[i].Idle(iStepCount);
	}
}

// 清除当前处理的最高优先级判别中断标志
void  CVHardware::ClearInt()
{	
	for(int Reg = 0; Reg < 32; Reg ++) 
	{
		if(m_bIntReg[Reg]) 
		{
			m_pIntSource[Reg]->ClearInt();
			m_bIntReg[Reg] = FALSE;
			break;
		}
	}
}

void  CVHardware::GetMap(CDSPMap & Map)
{
}

