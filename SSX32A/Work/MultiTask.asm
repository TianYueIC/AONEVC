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
//�ڷ�����DUMP�ļ��������ǰʱ�䡢����źͺ�����
//====================================================================
#define DUMP(x)		\
	RD3 = (x)|0x900000;	\
	TRACE_PORT = RD3;

///////////////////////////////////////////////////////////
// �������̨������Ҫ������
// 1.��ǰ�������
//		���ö˿� Task_Sel, ��ʼֵΪ 0
// 2.������ջָ��� curRSP  
//		��СΪ TASK_NUM ������,ȫ����ʼ��Ϊ PRIVATE_RAM_SIZE-1
// 3.������ȴ����ͱ� waitType
//		��СΪ TASK_NUM ������, ȫ����ʼ��Ϊ GETINPUT
//	��6�����Ͷ���
//		GETINPUT
//		GETOUTPUT
//		GETASDSP
//		GETECC
//		WAIT
//		RELEASE
// 4. ��Դռ�ñ� resState		
//		��СΪ 64 ������, ��32�����ݣ�
//			Ӳ�������ֺ�ռ�������(-1��ʾ��)
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
//  ��ʼ������ջָ��� curRSP
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
//  ��ʼ������ȴ����ͱ� waitType
	RD0 = waitType;
	RA0 = RD0;
	RD1 = TASK_NUM;
	RD0 = GETINPUT;
init2:
	M[RA0++] = RD0;
	RD1--;
	if(nZero) goto init2;

//==================================
//  ��ʼ����Դռ�ñ� resState
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
//  ��ʼ��������Ķ�ջ����Ϊ offset TaskStart
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
    set(INT_EN);                            // �����ж�
	SELECT_INPUT;							
	set(ACK);								// �Ի������ղ���
	call InitRA;
	RD0 = 0;
	M[RA0+1] = RD0;
///////////////////////////////////////////////////////////
// �л�����(�ڲ�����)
// ���: RD3: TaskID
ToTask:
	Task_Sel = RD3;
	RSP = M[RA1+RD3];
	DUMP(RETURN)
	return;

/////////////////////////////////////////////////////////////////////
// RA0 = resState, RA1 = curRSP, RA2 = waitType,RD3 = Task_Sel
sub InitRA;
	RD0 = resState;				// ��Դռ�ñ��ͷ
	RA0 = RD0;
	RD0 = curRSP;
	RA1 = RD0;
	RD0 = waitType;
	RA2 = RD0;
	RD3 = Task_Sel;
	return;

///////////////////////////////////////////////////////////
// ��ȡ ASDSP �������
// ����: RD0 Ӳ�������
//		RD1 = 1 ��ʾ��ȡ����Դ
sub GetASDSP;
	DUMP(GETASDSP)
	RD0 = resState;				// ��Դռ�ñ��ͷ
	RA0 = RD0;
	RD0 = 2;					// ���� INPUT Ӳ��
	RD3 = ASDSP_NUM;

GetNextASDSP:
	RD2 = M[RA0+RD0];				// ȡӲ��������
	RD0++;
	RD1 = M[RA0+RD0];				// ȡռ��Ӳ�������
	RD0++;
	RD1++;
	if(Zero) goto FindACC;	// ռ��Ӳ�������Ϊ -1
	RD3--;
	if(nZero) goto GetNextASDSP;
	nop;
	// ��
FindACC:
	Res_Sel = RD2;
	set(ACK);
	RD2 = RD0;
	ShiftR1(RD2);
	RD2 --;
	SetPortBit(Res_State,RD2);
	RD0 --;						// RD0 ���Ӳ��������
	M[RA0+RD0] = Task_Sel;		// ����ռ�������
	RD1 = 1;
	DUMP(RETURN)
	return;

///////////////////////////////////////////////////////////
// ��ȡ ECCACC �������
// 
sub GetECCACC;
	DUMP(GETECC)
	RD0 = resState;				// ��Դռ�ñ��ͷ
	RA0 = RD0;
	RD0 = (ASDSP_NUM+1)*2;		// ���� INPUT Ӳ���� ASDSP Ӳ��
	RD3 = ECCACC_NUM;
GetNextECCACC:
	RD2 = M[RA0+RD0];				// ȡӲ��������
	RD0++;
	RD1 = M[RA0+RD0];				// ȡռ��Ӳ�������
	RD0++;
	RD1++;
	if(Zero) goto FindACC; // ռ��Ӳ�������Ϊ -1
	RD3--;
	if(nZero) goto GetNextECCACC;
	nop;
	// ��
	DUMP(RETURN)
	return;

//////////////////////////////////////////////////////
// �ͷ�Ӳ����Դ
// ���:RD0 ��Դ���
sub Release;
	DUMP(RELEASE)
	RD1 = resState;				// ��Դռ�ñ��ͷ
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
// ��ȡ INPUT �������
// 
sub GetInput;
	DUMP(GETINPUT)
	call InitRA;				// RA0 = resState, RA1 = curRSP, 
								// RA2 = waitType, RD3 = Task_Sel
	RD0 = 1;					// ��� INPUT Ӳ��������
	RD1 = M[RA0+RD0];			// ȡ INPUT ռ��Ӳ�������
	RD1++;
	if(Zero) goto FindInput;	// ռ��Ӳ�������Ϊ -1
	M[RA1+RD3]=RSP;				// ���浱ǰջָ��
	RD1 = GETINPUT;				// �õȴ�����
	M[RA2+RD3]=RD1;
	goto waitEvent;
FindInput:
	M[RA0+RD0] = RD3;				// ����ռ�������
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
	M[RA0+1] = RD2;				// �� INPUT ռ��Ӳ�������
	M[RA1+RD3]=RSP;				// ���浱ǰջָ��
	RD1 = RELEASE;				// �õȴ�����
	M[RA2+RD3]=RD1;
	// ɨ����������ȴ�����
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
// ��ȡ OUTPUT �������
// 
sub GetOutput;
	DUMP(GETOUTPUT)
	call InitRA;				// RA0 = resState, RA1 = curRSP, 
								// RA2 = waitType, RD3 = Task_Sel
	RD0 = 32*2-1;				// ��� OUTPUT Ӳ�������
	RD1 = M[RA0+RD0];			// ȡӲ�� OUTPUT ռ��Ӳ�������
	RD1++;
	if(Zero) goto FindOutput;	// ռ��Ӳ�������Ϊ -1
	M[RA1+RD3]=RSP;				// ���浱ǰջָ��
	RD1 = GETOUTPUT;			// �õȴ�����
	M[RA2+RD3]=RD1;
	goto waitEvent;
FindOutput:
	SELECT_OUTPUT;
	set(ACK);
	RD0 = 63;
	M[RA0+RD0] = Task_Sel;		// ����ռ�������
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
// �ȴ��¼�����
// ����: RD0 ��Դ����� resState[RD0] Ϊ��Դռ�������
sub Wait;
	DUMP(WAIT)
	call InitRA;				// RA0 = resState, RA1 = curRSP, 
								// RA2 = waitType, RD3 = Task_Sel
	M[RA1+RD3]=RSP;				// ���浱ǰջָ��
	RD1 = WAIT;					// �õȴ�����
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
scanEvent:						// ɨ���¼�
	RD0 = 31;					// ɨ����Դ�����
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
	EXIT(99);					// ������ֵ�error 
	
findEvent:
	RD0 <<;
	RD1 = M[RA0+RD0];			// Ӳ��������
	Res_Sel = RD1;
	RD0 ++;
	RD3 = M[RA0+RD0];			// �����
	goto ToTask;				// ���: RD3
findOutputEven:
	RD0 = 63;
	RD1 = 0;
	RD1 --;
	M[RA0+RD0] = RD1;			// �����
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
	M[RA0+RD0] = RD3;			// ����ռ�������
	RD1 = 1;
	goto ToTask;
