// 1. �궨��:
// 1.1  �Ĵ����궨��:
#define R_RnRp              R[23]               // Rn/Rp�ĵ�ַ(0x95/0x15)
#define R_MultiIR           R[22]               // �˷�ָ����
#define R_JumpVec           R[21]               // ת�ƿ�������
#define R_BlkSrc            R[20]               // BLOCK��Դ��ַ
#define R_BlkDest           R[19]               // BLOCK��Ŀ���ַ
#define R_BlkLen            R[18]               // BLOCK�ĳ���
#define R_RowNum            R[17]               // e,k���к�0-2

// 1.2  EXPRAM��ַ����:
#define pZero               0x95                // 0�ĵ�ַ
#define pRp3Rp              0x15                // [Rp,3Rp]���е�ַ
#define pRn3Rn              0x17                // [Rn,3Rn]���е�ַ
#define pPminus             0x96                // Pminus�ĵ�ַ
#define paRp                0x16                // aRp
#define pBUFQUE0            0x00                // ���������0��0��ַ
#define pBUFQUE1            0x01                // ���������0��1��ַ
#define pBUFQUE2            0x80                // ���������2��0��ַ

// 1.3  ת���������:
// ���Ӽ����ת�����:
#define PNTDBL1             0x01                // ����1
#define PNTDBL2             0x02                // ����2
// ��Ӽ����ת�����:
#define PNTADD1             0x01                // ���1

// 1.4  �ڴ�����궨��:
#define RAMFresh            IR_EXPRAM=0xfb      // ˢ��EXPRAM
#define RAM_RA0_to_E0       0xb4                // E0=EXPRAM[RA0_ExPRAM]
#define RAM_RA0_to_E1       0xd4                // E1=EXPRAM[RA0_ExPRAM]
#define RAM_RA0_to_R7       0xf4                // DB0=EXPRAM[RA0_EXPRAM]
#define RAM_RA0_to_S0       0x54                // S0=EXPRAM[RA0_EXPRAM]
#define RAM_RA0_to_S1       0x74                // S1=EXPRAM[RA0_EXPRAM]
#define RAM_RA0_to_X3X      0x24                // [xreg,3xreg]=EXPRAM[RA0_EXPRAM], modified by leehe, 2005.04.16
#define RAM_RA0_to_S0X3X    0x64                // [xreg,3xreg,S0reg]=EXPRAM[RA0_EXPRAM], added by leehe, 2005.04.16
#define RAM_RA0_to_Y        0x94                // [yreg]=EXPRAM[RA0_EXPRAM]
#define RAM_RA1_to_E0       0xb5                // E0=EXPRAM[RA1_ExPRAM]
#define RAM_RA1_to_E1       0xd5                // E1=EXPRAM[RA1_ExPRAM]
#define RAM_RA1_to_R7       0xf5                // DB0=EXPRAM[RA1_EXPRAM]
#define RAM_RA1_to_S1       0x75                // S1=EXPRAM[RA1_EXPRAM]
#define RAM_RA1_to_X3X      0x25                // [xreg,3xreg]=EXPRAM[RA1_EXPRAM], modified by leehe, 2005.04.16
#define RAM_RA1_to_Y        0x95                // [yreg]=EXPRAM[RA1_EXPRAM]
#define RAM_RA1inc_to_R7    0xf1                // DB0=EXPRAM[RA1_EXPRAM++]
#define RAM_RA1_to_S0X3X    0x65                // [xreg,3xreg,S0reg]=EXPRAM[RA1_EXPRAM], added by leehe, 2005.04.16
#define RAM_RA2_to_S1       0x76                // S1=EXPRAM[RA2_EXPRAM]
#define E0_to_RAM_RA0       0xbc                // EXPRAM[RA0_ExPRAM]=E0
#define R7_to_RAM_RA0       0xfc                // EXPRAM[RA0_EXPRAM]=DB0
#define R7_to_RAM_RA0inc    0xf8                // EXPRAM[RA0_EXPRAM++]=DB0
#define S0S1_to_RAM_RA2inc  0x0a                // EXPRAM[RA2_EXPRAM++]=[s0,s1,u0]
#define S0S1_to_RAM_RA0     0x0c                // EXPRAM[RA0_EXPRAM]=[s0,s1,u0]
#define S0S1_to_RAM_RA1     0x0d                // EXPRAM[RA1_EXPRAM]=[s0,s1,u0]
#define U0U1_to_RAM_RA2inc  0x6a                // EXPRAM[RA2_EXPRAM++]=[u0,u1,s0];
#define U0U1_to_RAM_RA0     0x6c                // EXPRAM[RA0_EXPRAM]=[u0,u1,s0];
#define U0U1_to_RAM_RA1     0x6d                // EXPRAM[RA1_EXPRAM]=[u0,u1,s0];

// 1.6  ģ�����������궨��:
#define MSubS0              0x2c                // x*y mod m && m-s0
#define S0AddS1             0x28                // x*y mod m && s0+s1
#define ModMultiGo          0x20                // [u0,u1]=[xreg,3xreg]*yreg mod m && t0s0+t1s1, t0=t1=0
#define ModMultiAddS0S1     0x08                // x*y mod m + t0s0 +t1s1 mod m
#define ModMultiUtoX        0x22                // [u0,u1]=>[x,3x], [u0,u1]=[xreg,3xreg]*yreg mod m
#define ModMultiUtoXY       0x23                // [u0,u1]=>[x,3x], u0=>y, [u0,u1]=[xreg,3xreg]*yreg mod m

#define setE0Window         C14

///////////////////////////////////////////////////////////////////
//
//    һ��uP����(L:11, sum:11):
//
///////////////////////////////////////////////////////////////////
    // 1. uP�Լ��(����):

    // 2. �ȴ�ģ�����������ź�:
	set uPIOEn;
LWaitMultiUnit:
    RAMFresh;
    if(!FlagReqFromMulti) goto LWaitMultiUnit;

    // 3. ��CPU�Ķ�д��ַ:
LSetCPUIOAddr:
    RA0_EXPRAM = pBUFQUE0;                       // uP��CPU��EXPRAM�Ķ�ȡ��ַ
    RA1_EXPRAM = pBUFQUE0;                       // uP��CPU��EXPRAM��д���ַ

    // 4. ��CPU��������,���ȴ�CPU��Ӧ:
    set ReqtoCPU;                               // ASDSP��CPU��������
LWaitCPUAck:
    RAMFresh;
    if(!FlagAckFromCPU) goto LWaitCPUAck;

    // 5. ��CPU��Ӧ��,uP����EXPRAM��IO
    //     ����Ȩ����CPU:
    set CPUIOEn;
    
    // 6. �ȴ�CPU��ȡ�����������������:
LWaitCPUIO:
    if(FlagAckFromCPU) goto LWaitCPUIO;

    // 7. CPU��IO����, uP����EXPRAMʹ��:
    set uPIOEn;


///////////////////////////////////////////////////////////////////
//
//    ����������������Э��������(sum:71):
//
///////////////////////////////////////////////////////////////////

    //////////////////////////////////////////
    //
    // (һ): ������D11ָ��NOP����:
    //
    //////////////////////////////////////////
    A = IR_ASDSP_H;
    if(A_bit3) goto LWaitMultiUnit;                 // d11=1: ��������ִ�н���, ֱ�ӻص���ʼ
    
    //////////////////////////////////////////
    //
    // (��): ������D3ָ����ģֵ����:
    //
    //////////////////////////////////////////
    A = IR_ASDSP_L;
    if(A_bit3) goto LNeedModN;                      // ��ģN
    // ģPԤ����:
    R_RnRp = pRp3Rp;                                // Rp�ĵ�ַ
    if(FlagMoAnB) goto LParseProtCmd;               // ��ǰMo�Ĵ���ΪA��:�趨P
    goto LMoTrigAB;  
    // ģNԤ����:
LNeedModN: 
    R_RnRp = pRn3Rn;                                // Rn�ĵ�ַ
    if(!FlagMoAnB) goto LParseProtCmd;              // ��ǰMo�Ĵ���ΪB��:�趨N
LMoTrigAB:
    set MoTrigAB;                                   // ��תMo�Ĵ���

    ////////////////////////////////////////////////////
    //
    // (��): ����Э��������D15-D9,��������Ӧ����:
    //
    ////////////////////////////////////////////////////
LParseProtCmd:
    // ����ASDSP.IR�ĸ�8λIR_ASDSP_H:
    A=IR_ASDSP_H;
    if(!A_bit7) goto LIRH0xxx;
    if(A_bit6) goto LWRITEMOX;                      // 1100: to дMOXЭ��
    if(A_bit5) goto LKP;                            // 1010: to AFkPЭ��
    if(A_bit4) goto LSEND;                          // 1001: to AFSendЭ��
    goto LSETASDSPPARA;                             // 1000: to AFSetAsdspParaЭ��
LIRH0xxx:
    if(A_bit6) goto LMODPOW;                        // 0100: to AFModPowЭ��
    goto LWaitMultiUnit;                            // ��������ִ�н���, ֱ�ӻص���ʼ


///////////////////////////////////////////////////////////////////
//
//    �����ĸ�Э�������ִ��:
//
///////////////////////////////////////////////////////////////////
    ////////////////////////////////
    //  
    // (һ) дMOX����:
    //  ���:
    //      BUFQUE[0]: Vm16;
    //      BUFQUE[1]: 3Vm16;
    //      m=P/N
    //  ����:
    //      ��
    //  ��ʱ����:
    //      ��
    ////////////////////////////////    
    // 1. ��BUFQUE[0],BUFQUE[1]��Vm16, 3Vm16
    //    �ֱ�д��MoXA/MoXB:
LWRITEMOX:    
/*
    set MoTrigAB;                               // ȷ��MoX.X
    A = IR_ASDSP_L;
    if(!A_bit3) goto LExpWriteMoxA;             // D3=0,P=>A; D3=1,N=>B
    // ��дB��
    if(FlagMoAnB) goto LVm3VmtoMox;             // ʹ��A��ʱ,����дB�飻
    goto LSetMoTrigAB;
LExpWriteMoxA:
    // ��дA��
    if(!FlagMoAnB) goto LVm3VmtoMox;            // ʹ��B��ʱ,����дA�飻
LSetMoTrigAB:
    set MoTrigAB;                               // ��תʹ�õĵ�ǰ�鵽Ŀ����
LVm3VmtoMox:
    RA0_EXPRAM = pBUFQUE0;                      // Vm16�ĵ�ַ
    IR_EXPRAM = RAM_RA0_to_R7;                  // R7=EXPARM[RA0_EXPRAM]
    nop;                                        // ����дָ����Ҫ����ִ������
    set WMoX;                                   // Vm16=>MoX
    set MoTrigX;                                // X=>3X
    RA0_EXPRAM = pBUFQUE1;                      // &3Vm16
    IR_EXPRAM = RAM_RA0_to_R7;                  // R7=EXPARM[RA0_EXPRAM]
    nop;                                        // ����дָ����Ҫ����ִ������
    set WMoX;                                   // 3Vm16=>MoX
    set MoTrigAB;                               // ������תΪʹ����
*/
    goto LWaitMultiUnit;                        // ��������ִ�н���, ֱ�ӻص���ʼ


    ////////////////////////////
    // (��) sendЭ��:
    // ���:
    //     IR_ASDSP_L
    // ����:
    //     ��
    ////////////////////////////
LSEND:
    // 1. EXPRAM�������ַ:
    A=IR_ASDSP_L;
    R[0]=A;                                         // uP�ľ��Ե�ַ

    // 2. д/������:
    RA1_EXPRAM=pBUFQUE2;                            // 0x80, source
    RA0_EXPRAM=R[0];                                // dest: BUFQUE => EXPRAM
    A=IR_ASDSP_H;
    if(A_bit0) goto LMoveData;                      // d8==1, д
    // D8==0, ��:
    RA1_EXPRAM=R[0];                                // source
    RA0_EXPRAM=pBUFQUE2;                            // 0x80, dest: BUFQUE <= EXPRAM
LMoveData:
    call MovRamRW1Sub;
    goto LWaitMultiUnit;                            // ���ؿ�ʼ



    ///////////////////////////////////////////////////////////////
    //  
    // (��) ����ASDSP�������㲿��:
    //      AFSetAsdspPara
    //  ���:
    //      BUFQUE[00..04]:ASDSP�Ĳ��ֲ���, ӳ������:
    //                  COL0 COL1 COL2 COL3 COL4
    //          ROW2:   aRp  Td   Ta3  Ta2  R-16n
    //          ROW1:   Rn   3Rp  Ta4  Nmi  3Rn
    //          ROW0:   Rp   3aRp 0    Pmi  Ta1
    //  ����:
    //      Asdsp������:ASDSP.const.[0x15..0x17]����,ӳ������:
    //                  COL0 COL1 COL2
    //          ROW2:   0    Pmi  
    //          ROW1:   3Rp  3aRp 3Rn
    //          ROW0:   Rp   aRp  Rn
    ///////////////////////////////////////////////////////////////
LSETASDSPPARA:
    // 1. ѡ��Asdsp.BUFQUE[0..4]�Ĳ��ֲ�������ASDSP
    //    ��������ӳ���Ƶ�Asdsp������[0x15..0x17]:
    // 1.1 BUFQUE[80].aRp => Const[16]:
    RA1_EXPRAM=0x80;                                // RA1_EXPRAM:BUFQUE.aRpԴַ
    RA0_EXPRAM=0x16;                                // RA0_EXPRAM:Const.aRpĿ���ַ
    call MovRamRW1Sub;                              // ����ASDSP��Ԫ,�ƻ�0x80;[RA0_EXPRAM]=MovRamRW1Sub(RA1_EXPRAM);RA1_EXPRAM:Դ(ASDSP)��ַ,RA0_EXPRAM:Ŀ��(ASDSP)��ַ

    // 1.2 BUFQUE[40].Rn => Const[17]:
    RA1_EXPRAM=0x40;                                // RA1_EXPRAM:BUFQUE.RnԴַ
    RA0_EXPRAM=0x17;                                // RA0_EXPRAM:Const.RnĿ���ַ
    call MovRamRW1Sub;                              // ����ASDSP��Ԫ,�ƻ�0x80;[RA0_EXPRAM]=MovRamRW1Sub(RA1_EXPRAM);RA1_EXPRAM:Դ(ASDSP)��ַ,RA0_EXPRAM:Ŀ��(ASDSP)��ַ

    // 1.3 BUFQUE[00].Rp => Const[15]:
    RA1_EXPRAM=0x00;                                // RA1_EXPRAM:BUFQUE.RpԴַ
    RA0_EXPRAM=0x15;                                // RA0_EXPRAM:Const.RpĿ���ַ
    call MovRamRW1Sub;                              // ����ASDSP��Ԫ,�ƻ�0x80;[RA0_EXPRAM]=MovRamRW1Sub(RA1_EXPRAM);RA1_EXPRAM:Դ(ASDSP)��ַ,RA0_EXPRAM:Ŀ��(ASDSP)��ַ

    // 1.4 BUFQUE[41].3Rp => Const[55]:
    RA1_EXPRAM=0x41;                                // RA1_EXPRAM:BUFQUE.3RpԴַ
    RA0_EXPRAM=0x55;                                // RA0_EXPRAM:Const.3RpĿ���ַ
    call MovRamRW1Sub;                              // ����ASDSP��Ԫ,�ƻ�0x80;[RA0_EXPRAM]=MovRamRW1Sub(RA1_EXPRAM);RA1_EXPRAM:Դ(ASDSP)��ַ,RA0_EXPRAM:Ŀ��(ASDSP)��ַ

    // 1.5 BUFQUE[01].3aRp => Const[56]:
    RA1_EXPRAM=0x01;                                // RA1_EXPRAM:BUFQUE.3aRpԴַ
    RA0_EXPRAM=0x56;                                // RA0_EXPRAM:Const.3aRpĿ���ַ
    call MovRamRW1Sub;                              // ����ASDSP��Ԫ,�ƻ�0x80;[RA0_EXPRAM]=MovRamRW1Sub(RA1_EXPRAM);RA1_EXPRAM:Դ(ASDSP)��ַ,RA0_EXPRAM:Ŀ��(ASDSP)��ַ

    // 1.6 BUFQUE[02].0 => Const[95]:
    RA1_EXPRAM=0x02;                                // RA1_EXPRAM:BUFQUE.0Դַ
    RA0_EXPRAM=0x95;                                // RA0_EXPRAM:Const.0Ŀ���ַ
    call MovRamRW1Sub;                              // ����ASDSP��Ԫ,�ƻ�0x80;[RA0_EXPRAM]=MovRamRW1Sub(RA1_EXPRAM);RA1_EXPRAM:Դ(ASDSP)��ַ,RA0_EXPRAM:Ŀ��(ASDSP)��ַ

    // 1.7 BUFQUE[03].Pmi => Const[96]:
    RA1_EXPRAM=0x03;                                // RA1_EXPRAM:BUFQUE.PmiԴַ
    RA0_EXPRAM=0x96;                                // RA0_EXPRAM:Const.PmiĿ���ַ
    call MovRamRW1Sub;                              // ����ASDSP��Ԫ,�ƻ�0x80;[RA0_EXPRAM]=MovRamRW1Sub(RA1_EXPRAM);RA1_EXPRAM:Դ(ASDSP)��ַ,RA0_EXPRAM:Ŀ��(ASDSP)��ַ

    // 1.8 BUFQUE[44].3Rn => Const[57]:
    RA1_EXPRAM=0x44;                                // RA1_EXPRAM:BUFQUE.3RnԴַ
    RA0_EXPRAM=0x57;                                // RA0_EXPRAM:Const.3RnĿ���ַ
    call MovRamRW1Sub;                              // ����ASDSP��Ԫ,�ƻ�0x80;[RA0_EXPRAM]=MovRamRW1Sub(RA1_EXPRAM);RA1_EXPRAM:Դ(ASDSP)��ַ,RA0_EXPRAM:Ŀ��(ASDSP)��ַ

    // 2. �������:
    goto LWaitMultiUnit;                            // ��������ִ�н���, ֱ�ӻص���ʼ;




    ////////////////////////////////////////////////////////////////
    // (��) ģ������Э��:
    // ���:
    //      BUFQUE[0]: ����[xR,3xR]�ĵ�ַ;
    //      BUFQUE[1]: ָ��E�ĵ�ַ;
    //      R_RowNum:  ָ��E���к�;
    //      R_RnRp:    [R,3R]�ĵ�ַ
    // ����:
    //      BUFQUE[0]: ģ��[zR,3zR]�ĵ�ַ;
    // ��ʱ��Ԫ: 
    //      R[1]:   �������ָ������ʱ��Ԫ;
    //      A:      �ۼ���
    // �ƻ���Ԫ:
    //      R_RowNum:  ָ��E�ľ��Ե�ַ;
    ////////////////////////////////////////////////////////////////
LMODPOW:
    // 1. �趨ģ��������ʱ��Ԫ��ַ:
    R[1]=0x07;                                      // �趨ģ��������ʱ��Ԫ��ַ
    call GetRowNum;                                 // ����IR_ASDSP_H.d2d1��ȡe���к�0x00-0x80; [R_RowNum]=GetRowNum(IR_ASDSP_H)
    A=pBUFQUE1;                                     // ָ��E���к�
    R_RowNum+=A;                                    // ָ��E�ľ��Ե�ַ

    // 2. ������ָ��e�Ķγ�:
    set ClearE0Window;                              // E0_Window=0x00, mxj,2005.12.14
    set ClearSegLength;
    set SetSegLength;                               // ��ʼ���γ�
    RA1_EXPRAM=R_RowNum;                            // R_RowNum:ָ��E�ľ��Ե�ַ
    IR_EXPRAM=RAM_RA1_to_E0;                        // E0=E
LFindE_1st1:
    //#############################################
    // added by yang
    // 2006.01.05
    if(FlagE0Empty) goto LWaitMultiUnit;            // ���ؿ�ʼ
    //#############################################
    if(FlagE0_MSB) goto LE_1st1Found;               // E0.msb==1, Ѱ�ҵ���ָ��E0����1λ��
    set ShiftE0;
    set ShiftE1;
    goto LFindE_1st1;
LE_1st1Found:
    // E1=E:
    RA1_EXPRAM=R_RowNum;                            // R_RowNum:ָ��E�ľ��Ե�ַ
    IR_EXPRAM=RAM_RA1_to_E1;                        // E1=M-2
    
    // 3. ģ�ݼ���:
    // [xreg,3xreg]=[R,3R]:
    RA1_EXPRAM=R_RnRp;                              // x=[R,3R]
    IR_EXPRAM=RAM_RA1_to_X3X;
    RA1_EXPRAM=pBUFQUE0;                            // y=xR
    R_MultiIR=ModMultiGo;
    call ModMultiSub;                               // [u0,u1]=[R,3R]*xR
    RA1_EXPRAM=R_RnRp;                              // y=[R,3R]
    call ModMultiSub;                               // [u0,u1]=[R,3R]*R
    RA0_EXPRAM=R[1];                                // temp
LSquare:
    call ReadU0U1Sub;                               // [u0,u1]=>temp
    R_MultiIR=ModMultiUtoXY;
    call ModMultiSub;                               // [u0,u1]=>[xreg,3xreg],u0=>yreg,[xreg,3xreg]*yreg
    if(FlagE1_LSB) goto LYTemp;
    RA1_EXPRAM=R_RnRp;                              // E0.b0=0: y=[R,3R]
    goto LXmulY;
LYTemp:
    RA1_EXPRAM=R[1];                                // E0.b0=1: y=temp
LXmulY: 
    R_MultiIR=ModMultiUtoX;
    set ShiftE1;
    call ModMultiSub;                               // [u0,u1]=>[xreg,3xreg],[xreg,3xreg]*yreg
    if(!FlagE1Empty) goto LSquare;
    call ModMultiSub;                               // null multi
    RA0_EXPRAM=pBUFQUE0;                            // [xR,3xR]^e=>BUFQUE[0], added by mxj, 2005.05.18
    call ReadU0U1Sub;
    goto LWaitMultiUnit;                            // ��������ִ�н���, ֱ�ӻص���ʼ;


    

   
    /////////////////////////////////////////////////////////////////////////////
    //  
    // (��) ������㲿��:
    //      Q=kP
    //  ���:
    //      BUFQUE[0x80,0x40,0x00;0x81,0x41,0x01;0x02]=[-yR,3xR,xR;-3yR,3yR,yR;k]
    //  ����:
    //      BUFQUE[0..3]=Q(xR,yR,zR,az4R)
    //  ��ʱ��Ԫ:
    //      R[7]: SEG START
    //      R[7]: carry
    //      R[16]:���볤��
    //      R_RowNum: SEG FLAG(1:64λ; 0:288λ)
    //      A:    �ۼ���
    /////////////////////////////////////////////////////////////////////////////
LKP:
    // 1. k=>k_NAF:
    //#######################################
    // modified by yang
    // 2006.01.06    
    R[7]=0;                                         // R[7]: SEG START
    R_RowNum=1;                                     // R_RowNum: SEG FLAG(1:64λ; 0:288λ)
    A=IR_ASDSP_L;
    if(A_bit4) goto LSEG3;
    if(A_bit2) goto LSEG2;
    if(A_bit1) goto LSEG1;
    if(A_bit0) goto LNaf_1;
    R_RowNum=0;
    goto LNaf_1;
LSEG3:
    R[7]=192;
    goto LNaf_1;
LSEG2:
    R[7]=128;
    goto LNaf_1;    
LSEG1:
    R[7]=64;
LNaf_1:
    RA0_EXPRAM=0x02;
    IR_EXPRAM=RAM_RA0_to_E1;                        // k=>E1
    
    // �Ƶ���λ:
    R[7]++;
LNaf_2:
    R[7]--;
    if(Zero) goto LNaf_3;
    set ShiftE1;
    RAMFresh;
    goto LNaf_2;

LNaf_3:
    RA0_EXPRAM=pZero;                                 // 0��ַ
    IR_EXPRAM=RAM_RA0_to_E0;    
    set ClearE0Window;
    set ClearSegLength;
    set SetSegLength;                               // ��ʼ���γ�
    R[16]=64;                                       // R[16]:���볤��
    R[7]=0;                                         // R[7]:carry
                                                    // R_RowNum: SEG FLAG(1:64λ; 0:288λ)
    // ����NAF����:
LNaf_4:
    RAMFresh;
    if(FlagE1Empty) goto LNaf_End;
    A=R[16];
    if(Zero) goto LNaf_5;
    if(!FlagE1_LSB) goto LNaf_5;
    R[7]++;
LNaf_5:
    A=R[7];
    if(A_bit0) goto LNaf_6;
    // ����NAF����0:
    set ShiftE1;
    A=R_RowNum;
    R[16]-=A;
    if(!Zero) goto LNaf_5_1;
    R_RowNum=0;
LNaf_5_1:
    set ShiftE0;
    R[7]>>;
    goto LNaf_4;
LNaf_6:
    set ShiftE1;
    A=R_RowNum;
    R[16]-=A;
    if(!Zero) goto LNaf_6_1;
    R_RowNum=0;
LNaf_6_1:
    if(Zero) goto LNaf_7;
    if(!FlagE1_LSB) goto LNaf_7;
    // ����NAF����11:
    set setE0Window;
    set ShiftE0;
    R[7]=1;
    set ShiftE0;
    A=R_RowNum;
    R[16]-=A;
    if(!Zero) goto LNaf_6_2;
    R_RowNum=0;
LNaf_6_2:
    set ClearE0Window;
    set ShiftE1;
    goto LNaf_4;
LNaf_7:
    // ����NAF����01:
    set ShiftE0;
    R[7]=0;
    set setE0Window;
    set ShiftE0;
    A=R_RowNum;
    R[16]-=A;
    if(!Zero) goto LNaf_7_1;
    R_RowNum=0;
LNaf_7_1:
    set ClearE0Window;
    set ShiftE1;
    goto LNaf_4;
LNaf_End:
    RA0_EXPRAM=0x02;
    IR_EXPRAM=E0_to_RAM_RA0;                        // E0=>0x02
    nop;
    IR_EXPRAM=RAM_RA0_to_E1;                        // 0x02=>E1
    
    //#######################################
    // modified by yang
    // 2006.01.06    
    IR_EXPRAM=RAM_RA0_to_E1;                        // k=>E1
    //#######################################

    // 2. ���յ�(CPT)=>�����(�ǽ��յ�ICPT):
    // 2.1 -yR=>0x04:
    RA1_EXPRAM=0x80;                                // ��Ԫ��Դַ
    RA0_EXPRAM=0x04;                                // ��Ԫ��Ŀַ
    call MovRamRW1Sub;                              // -yR=>0x04
    // 2.2 -3yR=>0x44:
    RA1_EXPRAM=0x81;                                // ��Ԫ��Դַ
    RA0_EXPRAM=0x44;                                // ��Ԫ��Ŀַ
    call MovRamRW1Sub;                              // -3yR=>0x44
    // 2.3 [Rp,3Rp;aRp,3aRp]=>[0x02,0x42;0x03,0x43]:
    R_BlkSrc=pRp3Rp;                                // [Rp,3Rp;aRp,3aRp]��Դַ
    R_BlkDest=0x02;                                 // [Rp,3Rp;aRp,3aRp]��Ŀַ
    R_BlkLen=2;                                     // �鳤2��
    call MovRamRW3incSub;                           // nP=>Q: ��ʼ��Q��
    // 2.4 BUFQUE[0..4].Q=>BUFQUE[0x10..0x14]:
    R_BlkSrc=0x00;                                  // �����ICPT��Դַ
    R_BlkDest=0x10;                                 // �����ICPT��Ŀַ
    R_BlkLen=5;                                     // �鳤5��
    call MovRamRW3incSub;                           // BUFQUE[0..4].Q=>BUFQUE[0x10..0x14]

    // 3. ���öγ�=288:
    set ClearE0Window;                              // E0_Window=0x00
    set ClearSegLength; 
    set SetSegLength;                               // ��ʼ���γ�Ϊ288
    
    //#######################################
    // modified by yang
    // 2006.01.06
    // 4. Ѱ��k����1λ��:
LFindk1st1Pos:
    if(FlagE1_LSB) goto Lk1st1Found;                // E1.LSB==1, �ҵ�k��1λ��
    set ShiftE1;
    RAMFresh;
    if(!FlagE1Empty) goto LFindk1st1Pos;            // E1�ǿռ�����
    
    // E1��,��Q.xR=�߲���1������:
    RA0_EXPRAM=pRp3Rp;                              // Rp��ַ
    IR_EXPRAM=RAM_RA0_to_S0;
    RA0_EXPRAM=pZero;                               // 0��ַ
    IR_EXPRAM=RAM_RA0_to_S1;
    nop;
    IR_Multi=MSubS0;
    nop;
    // �ȴ�ģ�����Ŀɶ��ź�:
LWaitReadFlag0:
    RAMFresh;
    if(!FlagREn) goto LWaitReadFlag0;
    set ReadSwap;                                   // ��ȡ����
    // 2. ��ȡs0��M[RA0_EXPRAM]:
    RA0_EXPRAM=pBUFQUE0;                            // 0��ַ
    IR_EXPRAM = S0S1_to_RAM_RA0;                    // M[RA0]=[s0,s1]
    nop;
    goto LWaitMultiUnit;                            // ASDSP.kPЭ�����
    //#######################################

    // 3. �Ƶ���1(2bits):
Lk1st1Found:
    set ShiftE1;
    nop;
    set ShiftE1;
    RAMFresh;

    // 4. ѭ������kP:
LChkkPEnd:
    // 4.1 kP��������
    if(FlagE1Empty) goto LWaitMultiUnit;            // ��������ִ�н���, ֱ�ӻص���ʼ
    
    // 4.2 Q=2Q:
    R_JumpVec=PNTDBL1;
    goto LCorePntDbl;                               // Q=2Q
LPNTDBL1:

    // 4.3 ��E1.LSB=1, ���Ƴ���λE1����,����������Q=2Q��Q=Q+P��
    //     ��E1.LSB=0, ���Ƴ�E1����һλ,����һ��Q=2Q,��ֱ�ӷ���kP�����ж�:
    if(FlagE1_LSB) goto LCal2QOnce;                 // kh==1
    set ShiftE1;                                    // kh==0
    goto LChkkPEnd;
    
    // 4.4 ����һ�α�������:
    //     Q=2Q;
LCal2QOnce:
    R_JumpVec=PNTDBL2;
    goto LCorePntDbl;                               // Q=2Q
LPNTDBL2:
    
    // 4.4 �Ƴ�2λE1����, Ȼ������1P/3P:
    set ShiftE1;
    R[6]=0;                                         // D1=0:+nP, R[6]=P.y��ƫ����
    if(!FlagE1_LSB) goto LCalPntAdd; 
    R[6]=3;                                         // D1=1:-nP, R[6]=P.-y��ƫ����
    
    // 4.5 Q=Q+nP/(-nP);
LCalPntAdd:
    goto LCorePntAdd;                               // kP�м���Q=Q+P
LPNTADD1:
    set ShiftE1;
    goto LChkkPEnd;



    ///////////////////////////////////////////////////////////////////
    // 5.  �ڲ��ĺ��ı���(Q=Q+Q)�㷨:
    //     (xR,yR,zR,az4R)=2*(x1R,y1R,z1R,az14R)
    //  ���:
    //     BUFQUE[0..3]=Q(x1R,y1R,z1R,az14R)
    //  ����:
    //     BUFQUE[0..3]=Q(x1R,y1R,z1R,az14R)
    //  ��ʱ����:
    //     A:
    //     R[0]..R[5],R[8]..R[10],R[12]
    //     temp1..temp15
    //     RA0_EXPRAM
    //     RA1_EXPRAM
    //     RA2_EXPRAM
    ///////////////////////////////////////////////////////////////////
LCorePntDbl:
    // 5.0 ������ʼ��:
    RA2_EXPRAM=0x05;                                // RA2_EXPRAM: TEMP��˳���ȡָ��,�״�����ʱ,���븳ֵ=0x05;���Ϊ0x0f;
    R[0]=S0AddS1;                                   // R[0]: ģ��ָ������:����ֵ==S0AddS1,�״�����ʱ,���븳ֵ
    R[5]=1;                                         // R[5]: s0��s1�Ƿ�һ��,1:ͬ; 0:��ͬ; ����ֵ==1,�״�����ʱ,���븳ֵ    
    R[8]= U0U1_to_RAM_RA2inc;                       // R[8]:  ȱʡ[u0,u1]дָ��ΪU0U1_to_RAM_RA2inc
    R[10]=S0S1_to_RAM_RA2inc;                       // R[10]: ȱʡ[s0,s1]дָ��ΪS0S1_to_RAM_RA2inc

    // 5.1 y1^2=y1*y1 && 2y1=y1+y1:
    //     [05:*], [06:*]
    R[1]=0x01;                                      // x=y1
    R[2]=0x01;                                      // y=y1
    R[3]=0x01;                                      // s0
    call ModMultiCSub;

    // 5.2 x1^2=x1*x1 && -x1: [06,07]
    //     [05:*], [06:2y1]
    RA2_EXPRAM=0x05;                                // RA2_EXPRAM: TEMP��˳���ȡָ��,�״�����ʱ,���븳ֵ=0x05;���Ϊ0x0f;
    R[0]=MSubS0;                                    // R[0]: ģ��ָ������:����ֵ==S0AddS1,�״�����ʱ,���븳ֵ
    R[1]=0x00;                                      // x=x1
    R[2]=0x00;                                      // y=x1
    R[3]=0x00;                                      // s0
    R[4]=pPminus;                                   // s1=Pminus
    R[5]=0;                                         // R[5]: s0��s1�Ƿ�һ��,1:ͬ; 0:��ͬ; ����ֵ==1,�״�����ʱ,���븳ֵ
    call ModMultiCSub;

    // 5.3 (-x1)*y1^2 && 2y1^2=y1^2+y1^2:
    //     [07:y1^2], [08:-x1]
    R[1]=0x07;                                      // x=y1^2
    R[2]=0x08;                                      // y=-x1
    R[3]=0x07;                                      // s0=y1^2
    call ModMultiCSub;

    // 5.4 (2y1^2)^2 && m=(3x1^2)+(az1^4):
    //     [09:x1^2], [0a:2y1^2]
    R[1]=0x0a;                                      // x=2y1^2
    R[2]=0x0a;                                      // y=2y1^2
    R[3]=0x49;                                      // s0=(3x1^2)
    R[4]=0x03;                                      // s1=(az1^4)
    R[5]=0;                                         // R[5]: s0��s1�Ƿ�һ��,1:ͬ; 0:��ͬ; ����ֵ==1,�״�����ʱ,���븳ֵ
    call ModMultiCSub;

    // 5.5 x3=m^2+(-s)+(-s) && (-s)=(-x1y1^2)+(-3x1y1^2)
    //     [0b:(-x1)*y1^2], [0c:m]
    R[1]=0x0c;                                      // x=m^2
    R[2]=0x0c;                                      // y=m^2
    R[3]=0x0b;                                      // s0=(-x1y1^2)
    R[4]=0x4b;                                      // s1=(-3x1y1^2)
    R[5]=0;                                         // R[5]: s0��s1�Ƿ�һ��,1:ͬ; 0:��ͬ; ����ֵ==1,�״�����ʱ,���븳ֵ
    call ModMultiCSub;

    // 5.6 null multi && (-s)+(-s):
    //     [0d:(2y1^2)^2], [0e:-s]
    R[0]=ModMultiAddS0S1;                           // R[0]: ģ��ָ������:����ֵ==S0AddS1,�״�����ʱ,���븳ֵ
    R[3]=0x0e;                                      // s0=(-s)
    call ModMultiCSub;

    // 5.7 z3=(2y1)*z1 && x3+(-s):
    //     [00:x3], [05:*]
    RA2_EXPRAM=0x05;                                // RA2_EXPRAM: TEMP��˳���ȡָ��,�״�����ʱ,���븳ֵ=0x05;���Ϊ0x0f;
    R[1]=0x06;                                      // x=2y1
    R[2]=0x02;                                      // y=z1
    R[3]=0x00;                                      // s0=x3
    R[4]=0x0e;                                      // s1=(-s)
    R[5]=0;                                         // R[5]: s0��s1�Ƿ�һ��,1:ͬ; 0:��ͬ; ����ֵ==1,�״�����ʱ,���븳ֵ
    R[8]=U0U1_to_RAM_RA0;                           // R[8]: ͨ��RA0_EXPRAMָ��[u0,u1]дQ��
    R[9]=0x00;                                      // u0=x3
    call ModMultiCSub;

    // 5.8 -y3=m*(x3-s)+u/2+u/2 && 2u=u/2 + 3u/2:
    //     [06:*], [07:x3-s]
    R[1]=0x0c;                                      // x=m
    R[2]=0x07;                                      // y=x3-s
    R[3]=0x0d;                                      // s0=u/2
    R[4]=0x4d;                                      // s1=3u/2
    R[5]=0;                                         // R[5]: s0��s1�Ƿ�һ��,1:ͬ; 0:��ͬ; ����ֵ==1,�״�����ʱ,���븳ֵ
    call ModMultiCSub;

    // 5.9 az3^4=(2u)*(az1^4) && u/2+u/2:
    //     [02:z3], [08:2u]
    R[0]=ModMultiAddS0S1;                           // R[0]: ģ��ָ������:����ֵ==S0AddS1,�״�����ʱ,���븳ֵ
    R[1]=0x08;                                      // x=2u
    R[2]=0x03;                                      // y=(az1^4)
    R[3]=0x0d;                                      // s0=u/2
    R[8]=U0U1_to_RAM_RA0;                           // R[8]: ͨ��RA0_EXPRAMָ��[u0,u1]дQ��
    R[9]=0x02;                                      // u0=z3
    call ModMultiCSub;

    // 5.10 null multi && y3=-(-y3):
    //     [09:-y3], [0a:*]
    R[0]=MSubS0;                                    // R[0]: ģ��ָ������:����ֵ==S0AddS1,�״�����ʱ,���븳ֵ
    R[3]=0x09;                                      // s0=-y3
    R[4]=pPminus;                                  // s1=P_Minus
    R[5]=0;                                         // R[5]: s0��s1�Ƿ�һ��,1:ͬ; 0:��ͬ; ����ֵ==1,�״�����ʱ,���븳ֵ
    call ModMultiCSub;

    // 5.11 null multi && null [s0s1]:
    //     [03:az3^4], [01:y3]
    R[8]=U0U1_to_RAM_RA0;                           // R[8]: ͨ��RA0_EXPRAMָ��[u0,u1]дQ��
    R[9]=0x03;                                      // u0=az3^4
    R[10]=S0S1_to_RAM_RA1;                          // R[10]: ͨ��RA1_EXPRAMָ��[s0,s1]дQ��
    R[12]=0x01;                                     // s0=y
    call ModMultiCSub;

    // 5.12 ȷ�����ӽ��ת��:
    A=R_JumpVec;
    if(A_bit0) goto LPNTDBL1;                       // kP��2Q����1
    goto LPNTDBL2;                                  // kP��2Q����2
    // Q+Q ����
    ///////////////////////////////////////////////////////////////////
    



    ///////////////////////////////////////////////////////////////////
    // 4.  �ڲ��ĺ��Ķ�����(Q=Q+P0)�㷨:
    //   (z1R,y1R,z1R,az14R)=(x1R,y1R,z1R,az14R)+(x2R,y2R,z2R,az4R)
    //   ���:
    //      BUFQUE[00..04]=Q(x1R,y1R,z1R,az14R,-y1R)
    //      BUFQUE[10..14]=P(x2R,y2R,z2R,az24R,-y2R)
    //      R[6]: 0/3, �ֱ��ʾ(+/-)P��(+/-)y��ƫ����
    //  ����:
    //      BUFQUE[00..04]=Q(x3R,y3R,z3R,az34R,-y3R)
    //  ��ʱ����:
    //     A:
    //     R[0]-R[5],R[8]-R[10],R[12]
    //     temp1..temp15
    //     RA0_EXPRAM
    //     RA1_EXPRAM
    //     RA2_EXPRAM    
    ////////////////////////////////////////////////////////////////////
LCorePntAdd:
    // 5.0 ������ʼ��:
    RA2_EXPRAM=0x05;                                    // RA2_EXPRAM: TEMP��˳���ȡָ��,�״�����ʱ,���븳ֵ=0x05;���Ϊ0x0f;
    R[0]=S0AddS1;                                       // R[0]: ģ��ָ������:����ֵ==S0AddS1,�״�����ʱ,���븳ֵ
    R[5]=1;                                             // R[5]: s0��s1�Ƿ�һ��,1:ͬ; 0:��ͬ; ����ֵ==1,�״�����ʱ,���븳ֵ    
    R[8]=U0U1_to_RAM_RA2inc;                            // R[8]:  ȱʡ[u0,u1]дָ��ΪU0U1_to_RAM_RA2inc
    R[10]=S0S1_to_RAM_RA2inc;                           // R[10]: ȱʡ[s0,s1]дָ��ΪS0S1_to_RAM_RA2inc

    // 4.1 z1^2=z1*z1:
    //     [05:*], [06:*]
    R[1]=0x02;                                          // x=z1
    R[2]=0x02;                                          // y=z1
    R[3]=0x00;                                          // s0=x1
    call ModMultiCSub;

    // 4.2 null multi:
    //     [05:*], [06:*]
    RA2_EXPRAM=0x05;                                    // RA2_EXPRAM: TEMP��˳���ȡָ��,�״�����ʱ,���븳ֵ=0x05;���Ϊ0x0f;
    call ModMultiCSub;
    
    // 4.3 z1^3=z1^2*z1 && -z1^2:
    //     [07:z1^2], [08:*]
    R[0]=MSubS0;                                        // R[0]: ģ��ָ������:����ֵ==S0AddS1,�״�����ʱ,���븳ֵ
    R[1]=0x07;                                          // x=z1^2
    R[2]=0x02;                                          // y=z1
    R[3]=0x07;                                          // s0=z1^2
    R[4]=pPminus;                                       // s1=Pminus
    R[5]=0;                                             // R[5]: s0��s1�Ƿ�һ��,1:ͬ; 0:��ͬ; ����ֵ==1,�״�����ʱ,���븳ֵ
    call ModMultiCSub;
    
    // 4.4 -h=x2*(-z1^2)+x1 && -x1:
    //     [09:*], [0a:-z1^2]
    R[0]=MSubS0;                                        // R[0]: ģ��ָ������:����ֵ==S0AddS1,�״�����ʱ,���븳ֵ
    R[1]=0x10;                                          // x=x2
    R[2]=0x0a;                                          // y=-z1^2
    R[3]=0x00;                                          // s0=x1
    R[4]=pPminus;                                       // s1=Pminus
    R[5]=0;                                             // R[5]: s0��s1�Ƿ�һ��,1:ͬ; 0:��ͬ; ����ֵ==1,�״�����ʱ,���븳ֵ
    call ModMultiCSub;

    // 4.5 s2=y2*(z1^3) && x1+0�˴���:
    //     [0b:z1^3], [0c:-x1]
    R[0]=ModMultiAddS0S1;                               // R[0]: ģ��ָ������:����ֵ==S0AddS1,�״�����ʱ,���븳ֵ
    R[1]=0x11;                                          // x=y2
    A=R[6];                                             // (+/-)y2��ƫ����(0/3)
    R[1]+=A;                                            // (+/-)y2�ĵĵ�ַ
    R[2]=0x0b;                                          // y=z1^3
    R[3]=0x00;                                          // s0=x1
    R[4]=pZero;                                         // s1=pZero
    R[5]=0;                                             // R[5]: s0��s1�Ƿ�һ��,1:ͬ; 0:��ͬ; ����ֵ==1,�״�����ʱ,���븳ֵ
    call ModMultiCSub;

    // 4.6 h^2=(-h)*(-h)  && -(y1):
    //     [0d:-h], [0e:*]
    R[0]=MSubS0;                                        // R[0]: ģ��ָ������:����ֵ==S0AddS1,�״�����ʱ,���븳ֵ
    R[1]=0x0d;                                          // x=-h
    R[2]=0x0d;                                          // y=-h
    R[3]=0x01;                                          // s0=y1
    R[4]=pPminus;                                       // s1=Pminus
    R[5]=0;                                             // R[5]: s0��s1�Ƿ�һ��,1:ͬ; 0:��ͬ; ����ֵ==1,�״�����ʱ,���븳ֵ
    call ModMultiCSub;

    // 4.7 -z3=z1*(-h) && -(-h):
    //     [05:s2], [06:-y1]
    RA2_EXPRAM=0x05;                                    // RA2_EXPRAM: TEMP��˳���ȡָ��,�״�����ʱ,���븳ֵ=0x05;���Ϊ0x0f;
    R[0]=MSubS0;                                        // R[0]: ģ��ָ������:����ֵ==S0AddS1,�״�����ʱ,���븳ֵ
    R[1]=0x02;                                          // x=z1
    R[2]=0x0d;                                          // y=-h
    R[3]=0x0d;                                          // s0=-h
    R[4]=pPminus;                                       // s1=Pminus
    R[5]=0;                                             // R[5]: s0��s1�Ƿ�һ��,1:ͬ; 0:��ͬ; ����ֵ==1,�״�����ʱ,���븳ֵ
    call ModMultiCSub;

    // 4.8 -x1h^2=h^2*(-x1):
    //     [07:h^2], [08:h]
    R[1]=0x07;                                          // x=h^2
    R[2]=0x0c;                                          // y=-x1
    call ModMultiCSub;

    // 4.9 -h^3=h^2*(-h) && r=s2+(-y1)
    //     [02:-z3], [09:*]
    R[1]=0x07;                                          // x=h^2
    R[2]=0x0d;                                          // y=-h
    R[3]=0x05;                                          // s0=s2
    R[4]=0x06;                                          // s1=-y1
    R[5]=0;                                             // R[5]: s0��s1�Ƿ�һ��,1:ͬ; 0:��ͬ; ����ֵ==1,�״�����ʱ,���븳ֵ
    R[8]=U0U1_to_RAM_RA0;                               // R[8]: ͨ��RA0_EXPRAMָ��[u0,u1]дQ��
    R[9]=0x02;                                          // u0=-z3
    call ModMultiCSub;

    // 4.10 x3=r^2+[-2u1h^2+(-h3)] && 2(-x1h^2)=(-x1h^2)+(-x1h^2):
    //     [0a:-x1h^2], [0b:r]
    R[1]=0x0b;                                          // x=r
    R[2]=0x0b;                                          // y=r
    R[3]=0x0a;                                          // s0=-x1h^2
    call ModMultiCSub;

    // 4.11 z3^2 && -2u1h^2+(-h3)�˴�����
    //     [0c:-h^3], [0d:-2x1h^2]
    R[0]=ModMultiAddS0S1;                               // R[0]: ģ��ָ������:����ֵ==S0AddS1,�״�����ʱ,���븳ֵ
    R[1]=0x02;                                          // x=-z3
    R[2]=0x02;                                          // y=-z3
    R[3]=0x0c;                                          // s0=-h^3
    R[4]=0x0d;                                          // s1=-2x1h^2
    R[5]=0;                                             // R[5]: s0��s1�Ƿ�һ��,1:ͬ; 0:��ͬ; ����ֵ==1,�״�����ʱ,���븳ֵ
    call ModMultiCSub;

    // 4.12 s1h^3=(-s1)*(-h^3) && x3+(-x1h^2):
    //     [00:x3], [0e:*]
    R[1]=0x06;                                          // x=-s1=-y1
    R[2]=0x0c;                                          // y=-h^3
    R[3]=0x00;                                          // s0=x3
    R[4]=0x0a;                                          // s1=-x1h^2
    R[5]=0;                                             // R[5]: s0��s1�Ƿ�һ��,1:ͬ; 0:��ͬ; ����ֵ==1,�״�����ʱ,���븳ֵ
    R[8]=U0U1_to_RAM_RA0;                               // R[8]: ͨ��RA0_EXPRAMָ��[u0,u1]дQ��
    R[9]=0x00;                                          // u0=x3    
    call ModMultiCSub;

    // 4.13 z3^4=(z3^2)^2 && null s0s1:
    //     [05:z3^2], [06:x3+(-x1h^2)]
    RA2_EXPRAM=0x05;                                    // RA2_EXPRAM: TEMP��˳���ȡָ��,�״�����ʱ,���븳ֵ=0x05;���Ϊ0x0f;
    R[1]=0x05;                                          // x=z3^2
    R[2]=0x05;                                          // y=z3^2
    call ModMultiCSub;

    // 4.14 -y3=r(x3-u1h^2)+s1h^3 && z3=-(-z3):
    //     [07:s1h^3], [08:*)]
    R[0]=MSubS0;                                        // R[0]: ģ��ָ������:����ֵ==S0AddS1,�״�����ʱ,���븳ֵ
    R[1]=0x0b;                                          // x=r
    R[2]=0x06;                                          // y=x3-u1h^2
    R[3]=0x02;                                          // s0=-z3
    R[4]=pPminus;                                       // s1=Pminus
    R[5]=0;                                             // R[5]: s0��s1�Ƿ�һ��,1:ͬ; 0:��ͬ; ����ֵ==1,�״�����ʱ,���븳ֵ
    call ModMultiCSub;

    // 4.15 az3^4=z3^4*a && 0+s1h3�˴�����
    //     [09:z3^4], [02:z3)]
    R[0]=ModMultiAddS0S1;                               // R[0]: ģ��ָ������:����ֵ==S0AddS1,�״�����ʱ,���븳ֵ
    R[1]=0x09;                                          // x=z3^4
    R[2]=paRp;                                          // y=aRp
    R[3]=0x07;                                          // s0=s1h^3
    R[4]=pZero;                                         // s1=0
    R[5]=0;                                             // R[5]: s0��s1�Ƿ�һ��,1:ͬ; 0:��ͬ; ����ֵ==1,�״�����ʱ,���븳ֵ
    R[10]=S0S1_to_RAM_RA1;                              // R[10]: ͨ��RA1_EXPRAMָ��[s0,s1]дQ��
    R[12]=0x02;                                         // s0=z3
    call ModMultiCSub;

    // 4.16 null multi && y3=-(-y3):
    //     [0a:-y3], [0b:*)]
    R[0]=MSubS0;                                        // R[0]: ģ��ָ������:����ֵ==S0AddS1,�״�����ʱ,���븳ֵ
    R[3]=0x0a;                                          // s0=-y3
    R[4]=pPminus;                                       // s1=Pminus
    R[5]=0;                                             // R[5]: s0��s1�Ƿ�һ��,1:ͬ; 0:��ͬ; ����ֵ==1,�״�����ʱ,���븳ֵ
    call ModMultiCSub;

    // 4.17 null multi && null [s0s1]:
    //     [03:az3^4], [01:y3]
    R[8]=U0U1_to_RAM_RA0;                               // R[8]: ͨ��RA0_EXPRAMָ��[u0,u1]дQ��
    R[9]=0x03;                                          // u0=az3^4
    R[10]=S0S1_to_RAM_RA1;                              // R[10]: ͨ��RA1_EXPRAMָ��[s0,s1]дQ��
    R[12]=0x01;                                         // s0=y3
    call ModMultiCSub;

    // 4.18 ȷ����ӽ��ת��:
LPntAddRstJump:    
    goto LPNTADD1;                                      // to kP�����е�Q+P
    // Q+P ����
    ///////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////
//  ��������:
//      ModMultiSub;
//  ��������:
//      uP�ĵ���ģ���ӳ���,�ݹ����[xR,3xR]=[xR,3xR]*yR mod M
//  ��ڲ���:
//      R_MultiIR:  ģ��ָ��
//      RA1_EXPRAM: ����y��EXPRAM�еĵ�ַ��
//  ���ڲ���:
//      ����:�ޣ�
///////////////////////////////////////////////////////////////////
sub ModMultiSub;
    
    // 1. uP�ȴ��˷�����������:
LWaitModMulti:
    RAMFresh;
    if(!FlagReqFromMulti) goto LWaitModMulti;

    // 2. y=EXPRAM[RA1_EXPRAM]:
LModMultiWrYReg:
    IR_EXPRAM = RAM_RA1_to_Y;                   // [yreg]=EXPRAM[RA1_EXPRAM],0x95;
    nop;
    
    // 3. ִ�г˷�ָ��:
    IR_Multi = R_MultiIR;
    RAMFresh;                                   // ˢ��EXPRAM

    // 4. ����:
    return;



///////////////////////////////////////////////////////////////////
//  ��������:
//      ReadU0U1Sub;
//  ��������:
//      �ȴ�����ȡ[u0,u1]��RA0_EXPRAM��Ԫ��;
//  ��ڲ���:
//      �ޣ�
//  ���ڲ���:
//      RA0_EXPRAM: [u0,u1]Ŀ���ַ��
///////////////////////////////////////////////////////////////////
sub ReadU0U1Sub;
    // 1. �ȴ�ģ�����Ŀɶ��ź�:
LWaitU0U1:
    RAMFresh;
    if(!FlagREn) goto LWaitU0U1;
    set ReadSwap;                               // ��ȡ����

    // 2. ��ȡ[u0,u1]��M[RA0_EXPRAM]:
    IR_EXPRAM = U0U1_to_RAM_RA0;                // M[RA0]=[u0,u1]
    nop;
    return;


///////////////////////////////////////////////////////////////////
//  ��������:
//      MovRamRW1Sub;
//  ��������:
//      ����RW��ʽ��EXPRAM[RA1_EXPRAM]��1�������Ƶ�RA0_EXPRAM��;
//  ��ڲ���:
//      RA1_EXPRAM: Դ�������е��׵�ַ��
//  ���ڲ���:
//      RA0_EXPRAM: Ŀ���������е��׵�ַ��
///////////////////////////////////////////////////////////////////
sub MovRamRW1Sub;   
LMovRW1Ram:
    IR_EXPRAM = RAM_RA1_to_R7;               // M[RA1]=>DB0
    nop;                                     // ע��:����R/W֮��Ӧ���һ��ָ��
    IR_EXPRAM = R7_to_RAM_RA0;               // DB0=>M[RA0]
    return;



///////////////////////////////////////////////////////////////////
//  ��������:
//      MovRamRW3incSub;
//  ��������:
//      ����RRR/WWW��ʽ��EXPRAM[RA0_EXPRAM]��A�������Ƶ�RA1_EXPRAM��;
//  ��ڲ���:
//      R_BlkSrc: Դ����׵�ַ
//      R_BlkDest: Ŀ�����׵�ַ
//      R_BlkLen: Դ��ĳ���
//  ���ڲ���:
//      R_BlkDest: Ŀ�����׵�ַ
//  �м����:
//      RA1_EXPRAM: Դ������ݵ�ַ��
//      RA0_EXPRAM: Ŀ�������ݵ�ַ��
//      R[11]: ѭ������
///////////////////////////////////////////////////////////////////
sub MovRamRW3incSub;
    // 1. �鳤Ϊ0,ֱ���˳�:
    A=R_BlkLen;                                 // Դ��ĳ���
    if(Zero) goto LMovEnd;                      

    // 2. ����Դ�����0����1�ֱ𵽵�Ŀ���
    //    ��0����1:
    // 2.1 ��ʼ������:
    R[11]=2;                                    // ����
    
    // 2.2 ����Դ���x�е�Ŀ����x��:
LMovNextLine:
    RA1_EXPRAM=R_BlkSrc;                        // Դ��0�е��׵�ַ
    RA0_EXPRAM=R_BlkDest;                       // Ŀ���0�е��׵�ַ
    A=R_BlkLen;                                 // Դ��ĳ���
LMovNextUnit:
    IR_EXPRAM = RAM_RA1inc_to_R7;               // M[RA1++]=>DB0
    nop;
    IR_EXPRAM = R7_to_RAM_RA0inc;               // DB0=>M[RA0++]
    A--;                                        // count--
    if(!Zero) goto LMovNextUnit;

    // 2.3 ������һ����ַ:
    A=0x40;
    R_BlkSrc+=A;
    R_BlkDest+=A;

    // 2.4 ���и�����ϣ�
    R[11]--;
    if(!Zero) goto LMovNextLine;

    // 3. ģ�����:
LMovEnd:
    return;



///////////////////////////////////////////////////////////////////
//  ��������:
//      ModMultiCSub(L:26);
//  ��������:
//      ������ģ��
//  ��ڲ���:
//      R[0]: ģ��ָ������:����ֵ==S0AddS1,�״�����ʱ,���븳ֵ
//      R[1]: x,3x��ַ,��������ֹ�޸�
//      R[2]: y��ַ,��������ֹ�޸�
//      R[3]: s0��ַ,��������ֹ�޸�
//      R[4]: s1��ַ; R[5]==1ʱ,R[4]���Բ���ֵ,��������ֹ�޸�
//      R[5]: s0��s1�Ƿ�һ��,1:ͬ; 0:��ͬ; ����ֵ==1,�״�����ʱ,���븳ֵ
//      R[8]: [u0,u1]дָ������: U0U1_to_RAM_RA2inc / U0U1_to_RAM_RA0;
//            ����ֵ=U0U1_to_RAM_RA2inc,�״�����ʱ,���븳ֵ
//      R[9]: [u0,u1]ָ���ĵ�Ŀ���ַ
//      R[10]:[s0,s1]дָ������:S0S1_to_RAM_RA2inc / S0S1_to_RAM_RA1;
//            ����ֵ=S0S1_to_RAM_RA2inc,�״�����ʱ,���븳ֵ
//      R[12]: [s0,s1]ָ����Ŀ���ַ
//      RA2_EXPRAM: TEMP��˳���ȡָ��,�״�����ʱ,���븳ֵ=0x05;���Ϊ0x0f;
//  ���ڲ���:
//      ��
//  ��ʱ����:
//      RA0_EXPRAM: ��ʱEXPRAM��ַָ��
//      RA1_EXPRAM: ��ʱEXPRAM��ַָ��
//      A:�ۼ���
///////////////////////////////////////////////////////////////////
sub ModMultiCSub;
    // 1. Ԥ��[u0,u1]��Ŀ���ַ:
    RA0_EXPRAM=R[9];                            // R[9]: [u0,u1]ָ���ĵ�Ŀ���ַRA2/RA0

    // 2. Ԥ��[s0,s1]��Ŀ���ַ:
    RA1_EXPRAM=R[12];                           // R[12]: [s0,s1]ָ����Ŀ���ַRA2/RA1
     
    // 3. �ȴ�ģ�����Ŀɶ��ź�:
LWaitReadFlag:
    RAMFresh;
    if(!FlagREn) goto LWaitReadFlag;
    set ReadSwap;                               // ��ȡ����

    // 4. ��ȡ[u0,u1]��TEMP����Q��:
    //    TEMP��:����,to_RA2++;
    //    Q��:   ָ��,to_RA1;
    IR_EXPRAM = R[8];                           // ��[u0,u1]��TEMP��(to_RA2++)��Q��(to_RA0)
    R[8]=U0U1_to_RAM_RA2inc;                    // ȱʡ[u0,u1]дָ��ΪTEMP������(to_RA2++)
    RA0_EXPRAM=R[1];                            // R[1]:x,3x��ַ

    // 5. ��ȡ[s0,s1]��TEMP����Q��:
    //    TEMP��:����,to_RA2++;
    //    Q��:   ָ��,to_RA1;
    IR_EXPRAM = R[10];                          // ��[s0,s1]��TEMP��(to_RA2++)��Q��(to_RA1)
    R[10]=S0S1_to_RAM_RA2inc;                   // ȱʡ[s0,s1]дָ��ΪTEMP������(to_RA2++)
    RA1_EXPRAM=R[2];                            // R[2]:y��ַ

    // 6. װ��[x,y,s0,s1]:
    IR_EXPRAM=RAM_RA1_to_Y;                     // ������װ��[y]�Ĵ���
    RA1_EXPRAM=R[4];                            // R[4]:s1��ַ
    IR_EXPRAM=RAM_RA0_to_X3X;                   // ��������װ��[x,3x]�Ĵ���
    RA0_EXPRAM=R[3];                            // R[3]:s0��ַ
    nop;
    IR_EXPRAM=RAM_RA0_to_S0;                    // װ��s0
    nop;
    IR_EXPRAM=RAM_RA0_to_S1;                    // װ����s0��ͬ��s1
    A=R[5];                                     // R[5]: s0��s1�Ƿ�һ��,1:ͬ; 0:��ͬ
    if(!Zero) goto LExecMulti;
    IR_EXPRAM=RAM_RA1_to_S1;                    // װ��ָ����s1
    R[5]=1;                                     // R[5]=1:ȱʡ��Ϊs0��s1��ͬ

    // 7. ִ�г˷�ָ��:
LExecMulti:
    IR_Multi=R[0];                              // R[0]: ģ��ָ������
    R[0]=S0AddS1;                               // R[0]=S0AddS1: ȱʡָ��x*y  mod m; t1s1+t0s0 mod m
 
    // 8. ����:
    return;


///////////////////////////////////////////////////////////////////
//  ��������:
//      GetRowNum
//  ��������:
//      ����Э��������D10-D9,��ȡe,k���к�0x00-0x80;
//  ��ڲ���:
//      IR_ASDSP_H: Asdspָ��ĸ�8����;
//  ���ڲ���:
//      R_RowNum: e,k���к�0x00-0x80;
//  ��ʱ����:
//      A:�ۼ���;
///////////////////////////////////////////////////////////////////
sub GetRowNum;
    // 1. ����Э��������D10-D9,��ȡe,k�к�0x00-0x80:
    A=IR_ASDSP_H;
    if(A_bit2) goto LROWEQU80;                       // 10: �к�0x80
    if(A_bit1) goto LROWEQU40;                       // 01: �к�0x40
    R_RowNum=0x00;                                   // 00: �к�0x00
    goto LGetRowNumEnd;
LROWEQU80:
    R_RowNum=0x80;                                   // ��ȡe,k���к�0x80
    goto LGetRowNumEnd;
LROWEQU40:
    R_RowNum=0x40;                                   // ��ȡe,k���к�0x40

    // 2. ����:
LGetRowNumEnd:
    return;