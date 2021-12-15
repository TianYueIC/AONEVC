#include "ssx32acpu.def"

extern sub SysInitial;
extern sub SetupFT;
extern base var SelfTestWord;

Main:
    // 1. 系统初始化：
    RD0 = 256;
	RSP = RD0;
	RD0 = 1;
	Task_Sel = RD0;
    call SetupFT;
    set(INT_EN);                            // 打开总中断
	SELECT_INPUT;
	set(ACK);
	clear(ACK);

///////////////////////////////////////////////////////////
// 调用输入缓冲器的流程
TaskLoop:
	// 1.调用GetInput 取得输入缓冲器句柄
	call GetInput;
	// 2.读取端口TxRDataLen得到输入缓冲器数据字数
	RD0 = 0;
	RA0 = RD0;
	RD0 = TxRDataLen;
	push RD0;
	push RA0;
	// 3.读取端口TxRData得到输入数据
receivloop:
	M[RA0++] = TxRData;
	RD0--;
	if(nZero) goto receivloop;
	// 4.调用 ReleaseInput 释放输入缓冲器句柄
	call ReleaseInput;

///////////////////////////////////////////////////////////
// 调用 ASDSP 的流程
	call GetASDSP;
	RD0 = 1000;
	ACCIR = RD0;
	clear(ACK);
	call Wait;
	call Release;

///////////////////////////////////////////////////////////
// 调用输出缓冲器的流程
	call GetOutput;
	pop	 RA0;
	pop  RD0;
	TxRDataLen = RD0;
sendloop:
	TxRData = M[RA0++];
	RD0--;
	if(nZero) goto sendloop;
	call ReleaseOutput;

	goto TaskLoop;
	EXIT(0);

//=========================================================
sub GetInput;
	nop;
waitInput:
	if(RxFlag) goto GetInputEnd;
	nop;
	goto waitInput;
GetInputEnd:
	SELECT_INPUT;
	set(ACK);
	return;

//=========================================================
sub ReleaseInput;
	SELECT_INPUT;
	clear(ACK);
	return;

//=========================================================
sub GetOutput;
	nop;
waitOutput:
	if(TxFlag) goto GetOutputEnd;
	nop;
	goto waitOutput;
GetOutputEnd:
	SELECT_OUTPUT;
	set(ACK);
	return;

//=========================================================
sub ReleaseOutput;
	SELECT_OUTPUT;
	clear(ACK);
	return;

//=========================================================
sub GetASDSP;
	SELECT_ASDSP;
	set(ACK);
	return;

sub Wait;
	nop;
	RD1 = 2;
waitLoop:
	RD0 = Res_Flag;
	RD0 &= RD1;
	if(nZero) goto waitEnd;
	goto waitLoop;
waitEnd:
	return;

sub Release;
	return;
