#include "ssx32acpu.def"
extern sub SetupFT;
extern label TaskStart;
extern sub TaskInit;

export GetInput;
export GetOutput;
export GetASDSP;
export ReleaseInput;
export ReleaseOutput;
export Release;
export Wait;

//====================================================================
//在仿真器DUMP文件中输出当前时间、任务号和函数名
//====================================================================
#define DUMP(x)		\
	RD3 = (x)|0x900000;	\
	TRACE_PORT = RD3;

///////////////////////////////////////////////////////////
// 多任务后台程序需要的数据
// 1.当前任务号码
//		借用端口 Task_Sel, 初始值为 0
// 2.各任务栈指针表 curRSP  
//		大小为 TASK_NUM 的数组,全部初始化为 PRIVATE_RAM_SIZE-1
// 3.各任务等待类型表 waitType
//		大小为 TASK_NUM 的数组, 全部初始化为 GETINPUT
//	共6种类型定义
//		GETINPUT
//		GETOUTPUT
//		GETASDSP
//		GETECC
//		WAIT
//		RELEASE
// 4. 资源占用表 resState		
//		大小为 64 的数组, 共32项数据，
//			硬件操作字和占用任务号(-1表示空)
#define curRSP PRIVATE_RAM_SIZE
#define waitType curRSP + TASK_NUM
#define resState waitType + TASK_NUM

#define GETINPUT		1
#define GETOUTPUT		2
#define GETASDSP		4
#define GETECC			8
#define WAIT			16
#define RELEASE			32

#define RETURN			128
Main:
    RD0 = 256;
	RSP = RD0;
    call SetupFT;
	RD0 = 0;
	Task_Sel = RD0;
//==================================
//  初始化任务栈指针表 curRSP
	RD0 = curRSP;
	RA0 = RD0;
	RD1 = TASK_NUM;
	RD0 = PRIVATE_RAM_SIZE;
	RD0--;
init1:
	M[RA0++] = RD0;
	RD1--;
	if(nZero) goto init1;

//==================================
//  初始化任务等待类型表 waitType
	RD0 = waitType;
	RA0 = RD0;
	RD1 = TASK_NUM;
	RD0 = GETINPUT;
init2:
	M[RA0++] = RD0;
	RD1--;
	if(nZero) goto init2;

//==================================
//  初始化资源占用表 resState
	RD0 = resState;
	RA0 = RD0;
	RD1 = 32;
	RD2 = 1;
	RD0 = 0;
	RD0--;
init3:
	M[RA0++] = RD2;
	RotateL1(RD2);
	M[RA0++] = RD0;
	RD1--;
	if(nZero) goto init3;

//==================================
//  初始化各任务的堆栈内容为 offset TaskStart
//
	RD0 = PRIVATE_RAM_SIZE;
	RSP = RD0;
	RD1 = offset TaskStart;
	RD3 = TASK_NUM;
init4:
	RD3--;
	Task_Sel = RD3;
	push RD1;
	push RD3;
	call TaskInit;
	pop  RD3;
	pop  RD1;
	RD3 &= RD3;
	if(nZero) goto init4;
	push RD1;

	set(RA2RAM);
    set(INT_EN);                            // 打开总中断
	SELECT_INPUT;							
	set(ACK);								// 对缓冲区空操作
	call InitRA;
	RD0 = 0;
	M[RA0+1] = RD0;
///////////////////////////////////////////////////////////
// 切换任务(内部函数)
// 入口: RD3: TaskID
ToTask:
	Task_Sel = RD3;
	RSP = M[RA1+RD3];
	DUMP(RETURN)
	return;

/////////////////////////////////////////////////////////////////////
// RA0 = resState, RA1 = curRSP, RA2 = waitType,RD3 = Task_Sel
sub InitRA;
	RD0 = resState;				// 资源占用表表头
	RA0 = RD0;
	RD0 = curRSP;
	RA1 = RD0;
	RD0 = waitType;
	RA2 = RD0;
	RD3 = Task_Sel;
	return;

///////////////////////////////////////////////////////////
// 获取 ASDSP 句柄函数
// 出口: RD0 硬件句柄号
//		RD1 = 1 表示获取了资源
sub GetASDSP;
	DUMP(GETASDSP)
	RD0 = resState;				// 资源占用表表头
	RA0 = RD0;
	RD0 = 2;					// 跳过 INPUT 硬件
	RD3 = ASDSP_NUM;

GetNextASDSP:
	RD2 = M[RA0+RD0];				// 取硬件控制字
	RD0++;
	RD1 = M[RA0+RD0];				// 取占用硬件任务号
	RD0++;
	RD1++;
	if(Zero) goto FindACC;	// 占用硬件任务号为 -1
	RD3--;
	if(nZero) goto GetNextASDSP;
	nop;
	// 无
FindACC:
	Res_Sel = RD2;
	set(ACK);
	RD2 = RD0;
	ShiftR1(RD2);
	RD2 --;
	SetPortBit(Res_State,RD2);
	RD0 --;						// RD0 输出硬件控制字
	M[RA0+RD0] = Task_Sel;		// 更改占用任务号
	RD1 = 1;
	DUMP(RETURN)
	return;

///////////////////////////////////////////////////////////
// 获取 ECCACC 句柄函数
// 
sub GetECCACC;
	DUMP(GETECC)
	RD0 = resState;				// 资源占用表表头
	RA0 = RD0;
	RD0 = (ASDSP_NUM+1)*2;		// 跳过 INPUT 硬件和 ASDSP 硬件
	RD3 = ECCACC_NUM;
GetNextECCACC:
	RD2 = M[RA0+RD0];				// 取硬件控制字
	RD0++;
	RD1 = M[RA0+RD0];				// 取占用硬件任务号
	RD0++;
	RD1++;
	if(Zero) goto FindACC; // 占用硬件任务号为 -1
	RD3--;
	if(nZero) goto GetNextECCACC;
	nop;
	// 无
	DUMP(RETURN)
	return;

//////////////////////////////////////////////////////
// 释放硬件资源
// 入口:RD0 资源句柄
sub Release;
	DUMP(RELEASE)
	RD1 = resState;				// 资源占用表表头
	RA0 = RD1;
	RD1 = 0;
	RD1 --;
	M[RA0+RD0] = RD1;
	RD0 ++;
	ShiftR1(RD0);
	RD0 --;
	ClearPortBit(Res_State,RD0);
	DUMP(RETURN)
	return;

///////////////////////////////////////////////////////////
// 获取 INPUT 句柄函数
// 
sub GetInput;
	DUMP(GETINPUT)
	call InitRA;				// RA0 = resState, RA1 = curRSP, 
								// RA2 = waitType, RD3 = Task_Sel
	RD0 = 1;					// 输出 INPUT 硬件控制字
	RD1 = M[RA0+RD0];			// 取 INPUT 占用硬件任务号
	RD1++;
	if(Zero) goto FindInput;	// 占用硬件任务号为 -1
	M[RA1+RD3]=RSP;				// 保存当前栈指针
	RD1 = GETINPUT;				// 置等待类型
	M[RA2+RD3]=RD1;
	goto waitEvent;
FindInput:
	M[RA0+RD0] = RD3;				// 更改占用任务号
	RD1 = 1;
	SELECT_INPUT;
	DUMP(RETURN)
	return;

sub ReleaseInput;
	DUMP(RELEASE)
	call InitRA;				// RA0 = resState, RA1 = curRSP, 
								// RA2 = waitType, RD3 = Task_Sel
	RD2 = 0;
	RD2--;
	M[RA0+1] = RD2;				// 清 INPUT 占用硬件任务号
	M[RA1+RD3]=RSP;				// 保存当前栈指针
	RD1 = RELEASE;				// 置等待类型
	M[RA2+RD3]=RD1;
	// 扫描有无任务等待输入
	RD0 = GETINPUT;
	RD1 = TASK_NUM;
	RD3 = 0;
scanWaitType:
	RD2 = M[RA2+RD3];
	RD2 -= RD0;
	if(Zero) goto findWaitInput;
	RD3 ++;
	RD1--;
	if(nZero) goto scanWaitType;
noneWaitInput:
	RD0 = 0;
	RD0--;
	M[RA0+1] = RD0;
	ClearPortBit(Res_State,0);
	DUMP(RETURN)
	return;
findWaitInput:
	M[RA0+1] = RD3;
	RD1 = 0;
	RD0 = 1;
	goto ToTask;

///////////////////////////////////////////////////////////
// 获取 OUTPUT 句柄函数
// 
sub GetOutput;
	DUMP(GETOUTPUT)
	call InitRA;				// RA0 = resState, RA1 = curRSP, 
								// RA2 = waitType, RD3 = Task_Sel
	RD0 = 32*2-1;				// 输出 OUTPUT 硬件句柄号
	RD1 = M[RA0+RD0];			// 取硬件 OUTPUT 占用硬件任务号
	RD1++;
	if(Zero) goto FindOutput;	// 占用硬件任务号为 -1
	M[RA1+RD3]=RSP;				// 保存当前栈指针
	RD1 = GETOUTPUT;			// 置等待类型
	M[RA2+RD3]=RD1;
	goto waitEvent;
FindOutput:
	SELECT_OUTPUT;
	set(ACK);
	RD0 = 63;
	M[RA0+RD0] = Task_Sel;		// 更改占用任务号
	RD1 = 1;
	DUMP(RETURN)
	return;
sub ReleaseOutput;
	DUMP(RELEASE)
	SELECT_OUTPUT;
	clear(ACK);
	DUMP(RETURN)
	return;
///////////////////////////////////////////////////////////
// 等待事件发生
// 出口: RD0 资源句柄号 resState[RD0] 为资源占用任务号
sub Wait;
	DUMP(WAIT)
	call InitRA;				// RA0 = resState, RA1 = curRSP, 
								// RA2 = waitType, RD3 = Task_Sel
	M[RA1+RD3]=RSP;				// 保存当前栈指针
	RD1 = WAIT;					// 置等待类型
	M[RA2+RD3]=RD1;
waitEvent:
	RD0 = RELEASE;
	RD1 = TASK_NUM;
	RD3 = 0;
scanRelease:
	RD2 = M[RA2+RD3];
	RD2 -= RD0;
	if(Zero) goto findRelease;
	RD3 ++;
	RD1--;
	if(nZero) goto scanRelease;
	goto waitLoop;
findRelease:
	goto ToTask;
waitLoop:
	RD1 = Res_Flag;
	RD1 &= RD1;
	if(nZero) goto scanEvent;
	goto waitLoop;
scanEvent:						// 扫描事件
	RD0 = 31;					// 扫描资源句柄号
	BitPos = RD0;
	BitTest(RD1);
	if(ExFlag) goto findOutputEven;
nextRes:
	RD0 --;
	BitPos = RD0;
	BitTest(RD1);
	if(ExFlag) goto findEvent;
	RD0 &= RD0;
	if(nZero) goto nextRes;
	EXIT(99);					// 不会出现的error 
	
findEvent:
	RD0 <<;
	RD1 = M[RA0+RD0];			// 硬件控制字
	Res_Sel = RD1;
	RD0 ++;
	RD3 = M[RA0+RD0];			// 任务号
	goto ToTask;				// 入口: RD3
findOutputEven:
	RD0 = 63;
	RD1 = 0;
	RD1 --;
	M[RA0+RD0] = RD1;			// 任务号
	RD1 = TASK_NUM;
	RD3 = 0;
scanOutputType:
	RD2 = GETOUTPUT;
	RD2 -= M[RA2+RD3];
	if(Zero) goto findWaitOutput;
	RD3 ++;
	RD1 --;
	if(nZero) goto scanOutputType;
	ClearPortBit(Res_State,31);
	goto waitLoop;
findWaitOutput:
	SELECT_OUTPUT;
	set(ACK);
	RD0 = 63;
	M[RA0+RD0] = RD3;			// 更改占用任务号
	RD1 = 1;
	goto ToTask;
