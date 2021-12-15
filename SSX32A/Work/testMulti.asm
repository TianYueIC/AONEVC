#include "ssx32acpu.def"
extern sub GetInput;
extern sub GetOutput;
extern sub GetASDSP;
extern sub ReleaseInput;
extern sub ReleaseOutput;
extern sub Release;
extern sub Wait;
export TaskStart;
export TaskInit;

TaskLoop:
// 调用输入缓冲器的流程
	// 1.调用GetInput 取得输入缓冲器句柄
	call GetInput;
TaskStart:
	clear(ACK);
	call Wait;
	set(ACK);
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
//  调用 ASDSP 的流程
	call GetASDSP;
	RD0 = 5000;				// 延迟时间
	ACCIR = RD0;
	clear(ACK);
	call Wait;
	call Release;

///////////////////////////////////////////////////////////
//  调用输出缓冲器的流程
	call GetOutput;
	pop	 RA0;
	pop  RD0;
	RD0 ++;
	TxRDataLen = RD0;
	RD1 = Task_Sel;
	TxRData = RD1;
	RD0--;
sendloop:
	TxRData = M[RA0++];
	RD0--;
	if(nZero) goto sendloop;
	call ReleaseOutput;
	goto TaskLoop;

sub TaskInit;
	nop;
	return;
