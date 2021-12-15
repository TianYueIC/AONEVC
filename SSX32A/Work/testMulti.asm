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
// �������뻺����������
	// 1.����GetInput ȡ�����뻺�������
	call GetInput;
TaskStart:
	clear(ACK);
	call Wait;
	set(ACK);
	// 2.��ȡ�˿�TxRDataLen�õ����뻺������������
	RD0 = 0;
	RA0 = RD0;
	RD0 = TxRDataLen;
	push RD0;
	push RA0;
	// 3.��ȡ�˿�TxRData�õ���������
receivloop:
	M[RA0++] = TxRData;
	RD0--;
	if(nZero) goto receivloop;
	// 4.���� ReleaseInput �ͷ����뻺�������
	call ReleaseInput;

///////////////////////////////////////////////////////////
//  ���� ASDSP ������
	call GetASDSP;
	RD0 = 5000;				// �ӳ�ʱ��
	ACCIR = RD0;
	clear(ACK);
	call Wait;
	call Release;

///////////////////////////////////////////////////////////
//  �������������������
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
