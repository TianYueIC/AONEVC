// 1. 宏定义:
// 1.1  寄存器宏定义:
#define R_RnRp              R[23]               // Rn/Rp的地址(0x95/0x15)
#define R_MultiIR           R[22]               // 乘法指令字
#define R_JumpVec           R[21]               // 转移控制向量
#define R_BlkSrc            R[20]               // BLOCK的源地址
#define R_BlkDest           R[19]               // BLOCK的目标地址
#define R_BlkLen            R[18]               // BLOCK的长度
#define R_RowNum            R[17]               // e,k的行号0-2

// 1.2  EXPRAM地址定义:
#define pZero               0x95                // 0的地址
#define pRp3Rp              0x15                // [Rp,3Rp]的列地址
#define pRn3Rn              0x17                // [Rn,3Rn]的列地址
#define pPminus             0x96                // Pminus的地址
#define paRp                0x16                // aRp
#define pBUFQUE0            0x00                // 缓冲队列行0列0地址
#define pBUFQUE1            0x01                // 缓冲队列行0列1地址
#define pBUFQUE2            0x80                // 缓冲队列行2列0地址

// 1.3  转向参数定义:
// 倍加计算的转向参数:
#define PNTDBL1             0x01                // 倍加1
#define PNTDBL2             0x02                // 倍加2
// 点加计算的转向参数:
#define PNTADD1             0x01                // 点加1

// 1.4  内存操作宏定义:
#define RAMFresh            IR_EXPRAM=0xfb      // 刷新EXPRAM
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

// 1.6  模及算术操作宏定义:
#define MSubS0              0x2c                // x*y mod m && m-s0
#define S0AddS1             0x28                // x*y mod m && s0+s1
#define ModMultiGo          0x20                // [u0,u1]=[xreg,3xreg]*yreg mod m && t0s0+t1s1, t0=t1=0
#define ModMultiAddS0S1     0x08                // x*y mod m + t0s0 +t1s1 mod m
#define ModMultiUtoX        0x22                // [u0,u1]=>[x,3x], [u0,u1]=[xreg,3xreg]*yreg mod m
#define ModMultiUtoXY       0x23                // [u0,u1]=>[x,3x], u0=>y, [u0,u1]=[xreg,3xreg]*yreg mod m

#define setE0Window         C14

///////////////////////////////////////////////////////////////////
//
//    一、uP启动(L:11, sum:11):
//
///////////////////////////////////////////////////////////////////
    // 1. uP自检测(暂无):

    // 2. 等待模乘器的请求信号:
	set uPIOEn;
LWaitMultiUnit:
    RAMFresh;
    if(!FlagReqFromMulti) goto LWaitMultiUnit;

    // 3. 置CPU的读写地址:
LSetCPUIOAddr:
    RA0_EXPRAM = pBUFQUE0;                       // uP置CPU从EXPRAM的读取地址
    RA1_EXPRAM = pBUFQUE0;                       // uP置CPU对EXPRAM的写入地址

    // 4. 向CPU发出请求,并等待CPU响应:
    set ReqtoCPU;                               // ASDSP向CPU发出请求
LWaitCPUAck:
    RAMFresh;
    if(!FlagAckFromCPU) goto LWaitCPUAck;

    // 5. 等CPU响应后,uP将对EXPRAM的IO
    //     控制权交给CPU:
    set CPUIOEn;
    
    // 6. 等待CPU读取结果、发送任务数据:
LWaitCPUIO:
    if(FlagAckFromCPU) goto LWaitCPUIO;

    // 7. CPU的IO结束, uP操作EXPRAM使能:
    set uPIOEn;


///////////////////////////////////////////////////////////////////
//
//    二、解析操作数与协议命令字(sum:71):
//
///////////////////////////////////////////////////////////////////

    //////////////////////////////////////////
    //
    // (一): 解析由D11指定NOP属性:
    //
    //////////////////////////////////////////
    A = IR_ASDSP_H;
    if(A_bit3) goto LWaitMultiUnit;                 // d11=1: 本次任务执行结束, 直接回到开始
    
    //////////////////////////////////////////
    //
    // (二): 解析由D3指定的模值属性:
    //
    //////////////////////////////////////////
    A = IR_ASDSP_L;
    if(A_bit3) goto LNeedModN;                      // 需模N
    // 模P预处理:
    R_RnRp = pRp3Rp;                                // Rp的地址
    if(FlagMoAnB) goto LParseProtCmd;               // 当前Mo寄存器为A组:设定P
    goto LMoTrigAB;  
    // 模N预处理:
LNeedModN: 
    R_RnRp = pRn3Rn;                                // Rn的地址
    if(!FlagMoAnB) goto LParseProtCmd;              // 当前Mo寄存器为B组:设定N
LMoTrigAB:
    set MoTrigAB;                                   // 反转Mo寄存器

    ////////////////////////////////////////////////////
    //
    // (三): 解析协议命令字D15-D9,并进行相应处理:
    //
    ////////////////////////////////////////////////////
LParseProtCmd:
    // 分析ASDSP.IR的高8位IR_ASDSP_H:
    A=IR_ASDSP_H;
    if(!A_bit7) goto LIRH0xxx;
    if(A_bit6) goto LWRITEMOX;                      // 1100: to 写MOX协议
    if(A_bit5) goto LKP;                            // 1010: to AFkP协议
    if(A_bit4) goto LSEND;                          // 1001: to AFSend协议
    goto LSETASDSPPARA;                             // 1000: to AFSetAsdspPara协议
LIRH0xxx:
    if(A_bit6) goto LMODPOW;                        // 0100: to AFModPow协议
    goto LWaitMultiUnit;                            // 本次任务执行结束, 直接回到开始


///////////////////////////////////////////////////////////////////
//
//    三、四个协议解析并执行:
//
///////////////////////////////////////////////////////////////////
    ////////////////////////////////
    //  
    // (一) 写MOX部分:
    //  入口:
    //      BUFQUE[0]: Vm16;
    //      BUFQUE[1]: 3Vm16;
    //      m=P/N
    //  出口:
    //      无
    //  临时变量:
    //      无
    ////////////////////////////////    
    // 1. 将BUFQUE[0],BUFQUE[1]处Vm16, 3Vm16
    //    分别写入MoXA/MoXB:
LWRITEMOX:    
/*
    set MoTrigAB;                               // 确保MoX.X
    A = IR_ASDSP_L;
    if(!A_bit3) goto LExpWriteMoxA;             // D3=0,P=>A; D3=1,N=>B
    // 欲写B组
    if(FlagMoAnB) goto LVm3VmtoMox;             // 使用A组时,方可写B组；
    goto LSetMoTrigAB;
LExpWriteMoxA:
    // 欲写A组
    if(!FlagMoAnB) goto LVm3VmtoMox;            // 使用B组时,方可写A组；
LSetMoTrigAB:
    set MoTrigAB;                               // 反转使用的当前组到目标组
LVm3VmtoMox:
    RA0_EXPRAM = pBUFQUE0;                      // Vm16的地址
    IR_EXPRAM = RAM_RA0_to_R7;                  // R7=EXPARM[RA0_EXPRAM]
    nop;                                        // 单读写指令需要两个执行周期
    set WMoX;                                   // Vm16=>MoX
    set MoTrigX;                                // X=>3X
    RA0_EXPRAM = pBUFQUE1;                      // &3Vm16
    IR_EXPRAM = RAM_RA0_to_R7;                  // R7=EXPARM[RA0_EXPRAM]
    nop;                                        // 单读写指令需要两个执行周期
    set WMoX;                                   // 3Vm16=>MoX
    set MoTrigAB;                               // 设置组转为使用组
*/
    goto LWaitMultiUnit;                        // 本次任务执行结束, 直接回到开始


    ////////////////////////////
    // (二) send协议:
    // 入口:
    //     IR_ASDSP_L
    // 出口:
    //     无
    ////////////////////////////
LSEND:
    // 1. EXPRAM的物理地址:
    A=IR_ASDSP_L;
    R[0]=A;                                         // uP的绝对地址

    // 2. 写/读数据:
    RA1_EXPRAM=pBUFQUE2;                            // 0x80, source
    RA0_EXPRAM=R[0];                                // dest: BUFQUE => EXPRAM
    A=IR_ASDSP_H;
    if(A_bit0) goto LMoveData;                      // d8==1, 写
    // D8==0, 读:
    RA1_EXPRAM=R[0];                                // source
    RA0_EXPRAM=pBUFQUE2;                            // 0x80, dest: BUFQUE <= EXPRAM
LMoveData:
    call MovRamRW1Sub;
    goto LWaitMultiUnit;                            // 返回开始



    ///////////////////////////////////////////////////////////////
    //  
    // (三) 设置ASDSP参数运算部分:
    //      AFSetAsdspPara
    //  入口:
    //      BUFQUE[00..04]:ASDSP的部分参数, 映象如下:
    //                  COL0 COL1 COL2 COL3 COL4
    //          ROW2:   aRp  Td   Ta3  Ta2  R-16n
    //          ROW1:   Rn   3Rp  Ta4  Nmi  3Rn
    //          ROW0:   Rp   3aRp 0    Pmi  Ta1
    //  出口:
    //      Asdsp常数区:ASDSP.const.[0x15..0x17]三列,映像如下:
    //                  COL0 COL1 COL2
    //          ROW2:   0    Pmi  
    //          ROW1:   3Rp  3aRp 3Rn
    //          ROW0:   Rp   aRp  Rn
    ///////////////////////////////////////////////////////////////
LSETASDSPPARA:
    // 1. 选择Asdsp.BUFQUE[0..4]的部分参数按照ASDSP
    //    参数期望映像复制到Asdsp参数区[0x15..0x17]:
    // 1.1 BUFQUE[80].aRp => Const[16]:
    RA1_EXPRAM=0x80;                                // RA1_EXPRAM:BUFQUE.aRp源址
    RA0_EXPRAM=0x16;                                // RA0_EXPRAM:Const.aRp目标地址
    call MovRamRW1Sub;                              // 复制ASDSP单元,破坏0x80;[RA0_EXPRAM]=MovRamRW1Sub(RA1_EXPRAM);RA1_EXPRAM:源(ASDSP)首址,RA0_EXPRAM:目标(ASDSP)首址

    // 1.2 BUFQUE[40].Rn => Const[17]:
    RA1_EXPRAM=0x40;                                // RA1_EXPRAM:BUFQUE.Rn源址
    RA0_EXPRAM=0x17;                                // RA0_EXPRAM:Const.Rn目标地址
    call MovRamRW1Sub;                              // 复制ASDSP单元,破坏0x80;[RA0_EXPRAM]=MovRamRW1Sub(RA1_EXPRAM);RA1_EXPRAM:源(ASDSP)首址,RA0_EXPRAM:目标(ASDSP)首址

    // 1.3 BUFQUE[00].Rp => Const[15]:
    RA1_EXPRAM=0x00;                                // RA1_EXPRAM:BUFQUE.Rp源址
    RA0_EXPRAM=0x15;                                // RA0_EXPRAM:Const.Rp目标地址
    call MovRamRW1Sub;                              // 复制ASDSP单元,破坏0x80;[RA0_EXPRAM]=MovRamRW1Sub(RA1_EXPRAM);RA1_EXPRAM:源(ASDSP)首址,RA0_EXPRAM:目标(ASDSP)首址

    // 1.4 BUFQUE[41].3Rp => Const[55]:
    RA1_EXPRAM=0x41;                                // RA1_EXPRAM:BUFQUE.3Rp源址
    RA0_EXPRAM=0x55;                                // RA0_EXPRAM:Const.3Rp目标地址
    call MovRamRW1Sub;                              // 复制ASDSP单元,破坏0x80;[RA0_EXPRAM]=MovRamRW1Sub(RA1_EXPRAM);RA1_EXPRAM:源(ASDSP)首址,RA0_EXPRAM:目标(ASDSP)首址

    // 1.5 BUFQUE[01].3aRp => Const[56]:
    RA1_EXPRAM=0x01;                                // RA1_EXPRAM:BUFQUE.3aRp源址
    RA0_EXPRAM=0x56;                                // RA0_EXPRAM:Const.3aRp目标地址
    call MovRamRW1Sub;                              // 复制ASDSP单元,破坏0x80;[RA0_EXPRAM]=MovRamRW1Sub(RA1_EXPRAM);RA1_EXPRAM:源(ASDSP)首址,RA0_EXPRAM:目标(ASDSP)首址

    // 1.6 BUFQUE[02].0 => Const[95]:
    RA1_EXPRAM=0x02;                                // RA1_EXPRAM:BUFQUE.0源址
    RA0_EXPRAM=0x95;                                // RA0_EXPRAM:Const.0目标地址
    call MovRamRW1Sub;                              // 复制ASDSP单元,破坏0x80;[RA0_EXPRAM]=MovRamRW1Sub(RA1_EXPRAM);RA1_EXPRAM:源(ASDSP)首址,RA0_EXPRAM:目标(ASDSP)首址

    // 1.7 BUFQUE[03].Pmi => Const[96]:
    RA1_EXPRAM=0x03;                                // RA1_EXPRAM:BUFQUE.Pmi源址
    RA0_EXPRAM=0x96;                                // RA0_EXPRAM:Const.Pmi目标地址
    call MovRamRW1Sub;                              // 复制ASDSP单元,破坏0x80;[RA0_EXPRAM]=MovRamRW1Sub(RA1_EXPRAM);RA1_EXPRAM:源(ASDSP)首址,RA0_EXPRAM:目标(ASDSP)首址

    // 1.8 BUFQUE[44].3Rn => Const[57]:
    RA1_EXPRAM=0x44;                                // RA1_EXPRAM:BUFQUE.3Rn源址
    RA0_EXPRAM=0x57;                                // RA0_EXPRAM:Const.3Rn目标地址
    call MovRamRW1Sub;                              // 复制ASDSP单元,破坏0x80;[RA0_EXPRAM]=MovRamRW1Sub(RA1_EXPRAM);RA1_EXPRAM:源(ASDSP)首址,RA0_EXPRAM:目标(ASDSP)首址

    // 2. 任务结束:
    goto LWaitMultiUnit;                            // 本次任务执行结束, 直接回到开始;




    ////////////////////////////////////////////////////////////////
    // (四) 模幂运算协议:
    // 入口:
    //      BUFQUE[0]: 底数[xR,3xR]的地址;
    //      BUFQUE[1]: 指数E的地址;
    //      R_RowNum:  指数E的行号;
    //      R_RnRp:    [R,3R]的地址
    // 出口:
    //      BUFQUE[0]: 模幂[zR,3zR]的地址;
    // 临时单元: 
    //      R[1]:   主代码段指定的临时单元;
    //      A:      累加器
    // 破坏单元:
    //      R_RowNum:  指数E的绝对地址;
    ////////////////////////////////////////////////////////////////
LMODPOW:
    // 1. 设定模幂所需临时单元地址:
    R[1]=0x07;                                      // 设定模幂所需临时单元地址
    call GetRowNum;                                 // 根据IR_ASDSP_H.d2d1提取e的行号0x00-0x80; [R_RowNum]=GetRowNum(IR_ASDSP_H)
    A=pBUFQUE1;                                     // 指数E的列号
    R_RowNum+=A;                                    // 指数E的绝对地址

    // 2. 计算幂指数e的段长:
    set ClearE0Window;                              // E0_Window=0x00, mxj,2005.12.14
    set ClearSegLength;
    set SetSegLength;                               // 初始化段长
    RA1_EXPRAM=R_RowNum;                            // R_RowNum:指数E的绝对地址
    IR_EXPRAM=RAM_RA1_to_E0;                        // E0=E
LFindE_1st1:
    //#############################################
    // added by yang
    // 2006.01.05
    if(FlagE0Empty) goto LWaitMultiUnit;            // 返回开始
    //#############################################
    if(FlagE0_MSB) goto LE_1st1Found;               // E0.msb==1, 寻找到幂指数E0的首1位置
    set ShiftE0;
    set ShiftE1;
    goto LFindE_1st1;
LE_1st1Found:
    // E1=E:
    RA1_EXPRAM=R_RowNum;                            // R_RowNum:指数E的绝对地址
    IR_EXPRAM=RAM_RA1_to_E1;                        // E1=M-2
    
    // 3. 模幂计算:
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
    goto LWaitMultiUnit;                            // 本次任务执行结束, 直接回到开始;


    

   
    /////////////////////////////////////////////////////////////////////////////
    //  
    // (五) 点积运算部分:
    //      Q=kP
    //  入口:
    //      BUFQUE[0x80,0x40,0x00;0x81,0x41,0x01;0x02]=[-yR,3xR,xR;-3yR,3yR,yR;k]
    //  出口:
    //      BUFQUE[0..3]=Q(xR,yR,zR,az4R)
    //  临时单元:
    //      R[7]: SEG START
    //      R[7]: carry
    //      R[16]:编码长度
    //      R_RowNum: SEG FLAG(1:64位; 0:288位)
    //      A:    累加器
    /////////////////////////////////////////////////////////////////////////////
LKP:
    // 1. k=>k_NAF:
    //#######################################
    // modified by yang
    // 2006.01.06    
    R[7]=0;                                         // R[7]: SEG START
    R_RowNum=1;                                     // R_RowNum: SEG FLAG(1:64位; 0:288位)
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
    
    // 移掉低位:
    R[7]++;
LNaf_2:
    R[7]--;
    if(Zero) goto LNaf_3;
    set ShiftE1;
    RAMFresh;
    goto LNaf_2;

LNaf_3:
    RA0_EXPRAM=pZero;                                 // 0地址
    IR_EXPRAM=RAM_RA0_to_E0;    
    set ClearE0Window;
    set ClearSegLength;
    set SetSegLength;                               // 初始化段长
    R[16]=64;                                       // R[16]:编码长度
    R[7]=0;                                         // R[7]:carry
                                                    // R_RowNum: SEG FLAG(1:64位; 0:288位)
    // 进入NAF编码:
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
    // 处理NAF编码0:
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
    // 处理NAF编码11:
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
    // 处理NAF编码01:
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

    // 2. 紧凑点(CPT)=>计算点(非紧凑点ICPT):
    // 2.1 -yR=>0x04:
    RA1_EXPRAM=0x80;                                // 单元的源址
    RA0_EXPRAM=0x04;                                // 单元的目址
    call MovRamRW1Sub;                              // -yR=>0x04
    // 2.2 -3yR=>0x44:
    RA1_EXPRAM=0x81;                                // 单元的源址
    RA0_EXPRAM=0x44;                                // 单元的目址
    call MovRamRW1Sub;                              // -3yR=>0x44
    // 2.3 [Rp,3Rp;aRp,3aRp]=>[0x02,0x42;0x03,0x43]:
    R_BlkSrc=pRp3Rp;                                // [Rp,3Rp;aRp,3aRp]块源址
    R_BlkDest=0x02;                                 // [Rp,3Rp;aRp,3aRp]块目址
    R_BlkLen=2;                                     // 块长2列
    call MovRamRW3incSub;                           // nP=>Q: 初始化Q点
    // 2.4 BUFQUE[0..4].Q=>BUFQUE[0x10..0x14]:
    R_BlkSrc=0x00;                                  // 计算点ICPT块源址
    R_BlkDest=0x10;                                 // 计算点ICPT块目址
    R_BlkLen=5;                                     // 块长5列
    call MovRamRW3incSub;                           // BUFQUE[0..4].Q=>BUFQUE[0x10..0x14]

    // 3. 设置段长=288:
    set ClearE0Window;                              // E0_Window=0x00
    set ClearSegLength; 
    set SetSegLength;                               // 初始化段长为288
    
    //#######################################
    // modified by yang
    // 2006.01.06
    // 4. 寻找k的首1位置:
LFindk1st1Pos:
    if(FlagE1_LSB) goto Lk1st1Found;                // E1.LSB==1, 找到k首1位置
    set ShiftE1;
    RAMFresh;
    if(!FlagE1Empty) goto LFindk1st1Pos;            // E1非空继续找
    
    // E1空,置Q.xR=高部置1并结束:
    RA0_EXPRAM=pRp3Rp;                              // Rp地址
    IR_EXPRAM=RAM_RA0_to_S0;
    RA0_EXPRAM=pZero;                               // 0地址
    IR_EXPRAM=RAM_RA0_to_S1;
    nop;
    IR_Multi=MSubS0;
    nop;
    // 等待模乘器的可读信号:
LWaitReadFlag0:
    RAMFresh;
    if(!FlagREn) goto LWaitReadFlag0;
    set ReadSwap;                                   // 读取交换
    // 2. 读取s0到M[RA0_EXPRAM]:
    RA0_EXPRAM=pBUFQUE0;                            // 0地址
    IR_EXPRAM = S0S1_to_RAM_RA0;                    // M[RA0]=[s0,s1]
    nop;
    goto LWaitMultiUnit;                            // ASDSP.kP协议结束
    //#######################################

    // 3. 移掉首1(2bits):
Lk1st1Found:
    set ShiftE1;
    nop;
    set ShiftE1;
    RAMFresh;

    // 4. 循环计算kP:
LChkkPEnd:
    // 4.1 kP结束了吗？
    if(FlagE1Empty) goto LWaitMultiUnit;            // 本次任务执行结束, 直接回到开始
    
    // 4.2 Q=2Q:
    R_JumpVec=PNTDBL1;
    goto LCorePntDbl;                               // Q=2Q
LPNTDBL1:

    // 4.3 若E1.LSB=1, 则移出两位E1窗口,并计算两次Q=2Q及Q=Q+P；
    //     若E1.LSB=0, 则移出E1窗口一位,计算一次Q=2Q,并直接返回kP结束判断:
    if(FlagE1_LSB) goto LCal2QOnce;                 // kh==1
    set ShiftE1;                                    // kh==0
    goto LChkkPEnd;
    
    // 4.4 再做一次倍加运算:
    //     Q=2Q;
LCal2QOnce:
    R_JumpVec=PNTDBL2;
    goto LCorePntDbl;                               // Q=2Q
LPNTDBL2:
    
    // 4.4 移出2位E1窗口, 然后设置1P/3P:
    set ShiftE1;
    R[6]=0;                                         // D1=0:+nP, R[6]=P.y的偏移量
    if(!FlagE1_LSB) goto LCalPntAdd; 
    R[6]=3;                                         // D1=1:-nP, R[6]=P.-y的偏移量
    
    // 4.5 Q=Q+nP/(-nP);
LCalPntAdd:
    goto LCorePntAdd;                               // kP中计算Q=Q+P
LPNTADD1:
    set ShiftE1;
    goto LChkkPEnd;



    ///////////////////////////////////////////////////////////////////
    // 5.  内部的核心倍加(Q=Q+Q)算法:
    //     (xR,yR,zR,az4R)=2*(x1R,y1R,z1R,az14R)
    //  入口:
    //     BUFQUE[0..3]=Q(x1R,y1R,z1R,az14R)
    //  出口:
    //     BUFQUE[0..3]=Q(x1R,y1R,z1R,az14R)
    //  临时变量:
    //     A:
    //     R[0]..R[5],R[8]..R[10],R[12]
    //     temp1..temp15
    //     RA0_EXPRAM
    //     RA1_EXPRAM
    //     RA2_EXPRAM
    ///////////////////////////////////////////////////////////////////
LCorePntDbl:
    // 5.0 变量初始化:
    RA2_EXPRAM=0x05;                                // RA2_EXPRAM: TEMP区顺序存取指针,首次运行时,必须赋值=0x05;最大为0x0f;
    R[0]=S0AddS1;                                   // R[0]: 模乘指令类型:隐含值==S0AddS1,首次运行时,必须赋值
    R[5]=1;                                         // R[5]: s0与s1是否一样,1:同; 0:不同; 隐含值==1,首次运行时,必须赋值    
    R[8]= U0U1_to_RAM_RA2inc;                       // R[8]:  缺省[u0,u1]写指令为U0U1_to_RAM_RA2inc
    R[10]=S0S1_to_RAM_RA2inc;                       // R[10]: 缺省[s0,s1]写指令为S0S1_to_RAM_RA2inc

    // 5.1 y1^2=y1*y1 && 2y1=y1+y1:
    //     [05:*], [06:*]
    R[1]=0x01;                                      // x=y1
    R[2]=0x01;                                      // y=y1
    R[3]=0x01;                                      // s0
    call ModMultiCSub;

    // 5.2 x1^2=x1*x1 && -x1: [06,07]
    //     [05:*], [06:2y1]
    RA2_EXPRAM=0x05;                                // RA2_EXPRAM: TEMP区顺序存取指针,首次运行时,必须赋值=0x05;最大为0x0f;
    R[0]=MSubS0;                                    // R[0]: 模乘指令类型:隐含值==S0AddS1,首次运行时,必须赋值
    R[1]=0x00;                                      // x=x1
    R[2]=0x00;                                      // y=x1
    R[3]=0x00;                                      // s0
    R[4]=pPminus;                                   // s1=Pminus
    R[5]=0;                                         // R[5]: s0与s1是否一样,1:同; 0:不同; 隐含值==1,首次运行时,必须赋值
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
    R[5]=0;                                         // R[5]: s0与s1是否一样,1:同; 0:不同; 隐含值==1,首次运行时,必须赋值
    call ModMultiCSub;

    // 5.5 x3=m^2+(-s)+(-s) && (-s)=(-x1y1^2)+(-3x1y1^2)
    //     [0b:(-x1)*y1^2], [0c:m]
    R[1]=0x0c;                                      // x=m^2
    R[2]=0x0c;                                      // y=m^2
    R[3]=0x0b;                                      // s0=(-x1y1^2)
    R[4]=0x4b;                                      // s1=(-3x1y1^2)
    R[5]=0;                                         // R[5]: s0与s1是否一样,1:同; 0:不同; 隐含值==1,首次运行时,必须赋值
    call ModMultiCSub;

    // 5.6 null multi && (-s)+(-s):
    //     [0d:(2y1^2)^2], [0e:-s]
    R[0]=ModMultiAddS0S1;                           // R[0]: 模乘指令类型:隐含值==S0AddS1,首次运行时,必须赋值
    R[3]=0x0e;                                      // s0=(-s)
    call ModMultiCSub;

    // 5.7 z3=(2y1)*z1 && x3+(-s):
    //     [00:x3], [05:*]
    RA2_EXPRAM=0x05;                                // RA2_EXPRAM: TEMP区顺序存取指针,首次运行时,必须赋值=0x05;最大为0x0f;
    R[1]=0x06;                                      // x=2y1
    R[2]=0x02;                                      // y=z1
    R[3]=0x00;                                      // s0=x3
    R[4]=0x0e;                                      // s1=(-s)
    R[5]=0;                                         // R[5]: s0与s1是否一样,1:同; 0:不同; 隐含值==1,首次运行时,必须赋值
    R[8]=U0U1_to_RAM_RA0;                           // R[8]: 通过RA0_EXPRAM指定[u0,u1]写Q区
    R[9]=0x00;                                      // u0=x3
    call ModMultiCSub;

    // 5.8 -y3=m*(x3-s)+u/2+u/2 && 2u=u/2 + 3u/2:
    //     [06:*], [07:x3-s]
    R[1]=0x0c;                                      // x=m
    R[2]=0x07;                                      // y=x3-s
    R[3]=0x0d;                                      // s0=u/2
    R[4]=0x4d;                                      // s1=3u/2
    R[5]=0;                                         // R[5]: s0与s1是否一样,1:同; 0:不同; 隐含值==1,首次运行时,必须赋值
    call ModMultiCSub;

    // 5.9 az3^4=(2u)*(az1^4) && u/2+u/2:
    //     [02:z3], [08:2u]
    R[0]=ModMultiAddS0S1;                           // R[0]: 模乘指令类型:隐含值==S0AddS1,首次运行时,必须赋值
    R[1]=0x08;                                      // x=2u
    R[2]=0x03;                                      // y=(az1^4)
    R[3]=0x0d;                                      // s0=u/2
    R[8]=U0U1_to_RAM_RA0;                           // R[8]: 通过RA0_EXPRAM指定[u0,u1]写Q区
    R[9]=0x02;                                      // u0=z3
    call ModMultiCSub;

    // 5.10 null multi && y3=-(-y3):
    //     [09:-y3], [0a:*]
    R[0]=MSubS0;                                    // R[0]: 模乘指令类型:隐含值==S0AddS1,首次运行时,必须赋值
    R[3]=0x09;                                      // s0=-y3
    R[4]=pPminus;                                  // s1=P_Minus
    R[5]=0;                                         // R[5]: s0与s1是否一样,1:同; 0:不同; 隐含值==1,首次运行时,必须赋值
    call ModMultiCSub;

    // 5.11 null multi && null [s0s1]:
    //     [03:az3^4], [01:y3]
    R[8]=U0U1_to_RAM_RA0;                           // R[8]: 通过RA0_EXPRAM指定[u0,u1]写Q区
    R[9]=0x03;                                      // u0=az3^4
    R[10]=S0S1_to_RAM_RA1;                          // R[10]: 通过RA1_EXPRAM指定[s0,s1]写Q区
    R[12]=0x01;                                     // s0=y
    call ModMultiCSub;

    // 5.12 确定倍加结果转向:
    A=R_JumpVec;
    if(A_bit0) goto LPNTDBL1;                       // kP中2Q计算1
    goto LPNTDBL2;                                  // kP中2Q计算2
    // Q+Q 结束
    ///////////////////////////////////////////////////////////////////
    



    ///////////////////////////////////////////////////////////////////
    // 4.  内部的核心定点点加(Q=Q+P0)算法:
    //   (z1R,y1R,z1R,az14R)=(x1R,y1R,z1R,az14R)+(x2R,y2R,z2R,az4R)
    //   入口:
    //      BUFQUE[00..04]=Q(x1R,y1R,z1R,az14R,-y1R)
    //      BUFQUE[10..14]=P(x2R,y2R,z2R,az24R,-y2R)
    //      R[6]: 0/3, 分别表示(+/-)P点(+/-)y的偏移量
    //  出口:
    //      BUFQUE[00..04]=Q(x3R,y3R,z3R,az34R,-y3R)
    //  临时变量:
    //     A:
    //     R[0]-R[5],R[8]-R[10],R[12]
    //     temp1..temp15
    //     RA0_EXPRAM
    //     RA1_EXPRAM
    //     RA2_EXPRAM    
    ////////////////////////////////////////////////////////////////////
LCorePntAdd:
    // 5.0 变量初始化:
    RA2_EXPRAM=0x05;                                    // RA2_EXPRAM: TEMP区顺序存取指针,首次运行时,必须赋值=0x05;最大为0x0f;
    R[0]=S0AddS1;                                       // R[0]: 模乘指令类型:隐含值==S0AddS1,首次运行时,必须赋值
    R[5]=1;                                             // R[5]: s0与s1是否一样,1:同; 0:不同; 隐含值==1,首次运行时,必须赋值    
    R[8]=U0U1_to_RAM_RA2inc;                            // R[8]:  缺省[u0,u1]写指令为U0U1_to_RAM_RA2inc
    R[10]=S0S1_to_RAM_RA2inc;                           // R[10]: 缺省[s0,s1]写指令为S0S1_to_RAM_RA2inc

    // 4.1 z1^2=z1*z1:
    //     [05:*], [06:*]
    R[1]=0x02;                                          // x=z1
    R[2]=0x02;                                          // y=z1
    R[3]=0x00;                                          // s0=x1
    call ModMultiCSub;

    // 4.2 null multi:
    //     [05:*], [06:*]
    RA2_EXPRAM=0x05;                                    // RA2_EXPRAM: TEMP区顺序存取指针,首次运行时,必须赋值=0x05;最大为0x0f;
    call ModMultiCSub;
    
    // 4.3 z1^3=z1^2*z1 && -z1^2:
    //     [07:z1^2], [08:*]
    R[0]=MSubS0;                                        // R[0]: 模乘指令类型:隐含值==S0AddS1,首次运行时,必须赋值
    R[1]=0x07;                                          // x=z1^2
    R[2]=0x02;                                          // y=z1
    R[3]=0x07;                                          // s0=z1^2
    R[4]=pPminus;                                       // s1=Pminus
    R[5]=0;                                             // R[5]: s0与s1是否一样,1:同; 0:不同; 隐含值==1,首次运行时,必须赋值
    call ModMultiCSub;
    
    // 4.4 -h=x2*(-z1^2)+x1 && -x1:
    //     [09:*], [0a:-z1^2]
    R[0]=MSubS0;                                        // R[0]: 模乘指令类型:隐含值==S0AddS1,首次运行时,必须赋值
    R[1]=0x10;                                          // x=x2
    R[2]=0x0a;                                          // y=-z1^2
    R[3]=0x00;                                          // s0=x1
    R[4]=pPminus;                                       // s1=Pminus
    R[5]=0;                                             // R[5]: s0与s1是否一样,1:同; 0:不同; 隐含值==1,首次运行时,必须赋值
    call ModMultiCSub;

    // 4.5 s2=y2*(z1^3) && x1+0此处给:
    //     [0b:z1^3], [0c:-x1]
    R[0]=ModMultiAddS0S1;                               // R[0]: 模乘指令类型:隐含值==S0AddS1,首次运行时,必须赋值
    R[1]=0x11;                                          // x=y2
    A=R[6];                                             // (+/-)y2的偏移量(0/3)
    R[1]+=A;                                            // (+/-)y2的的地址
    R[2]=0x0b;                                          // y=z1^3
    R[3]=0x00;                                          // s0=x1
    R[4]=pZero;                                         // s1=pZero
    R[5]=0;                                             // R[5]: s0与s1是否一样,1:同; 0:不同; 隐含值==1,首次运行时,必须赋值
    call ModMultiCSub;

    // 4.6 h^2=(-h)*(-h)  && -(y1):
    //     [0d:-h], [0e:*]
    R[0]=MSubS0;                                        // R[0]: 模乘指令类型:隐含值==S0AddS1,首次运行时,必须赋值
    R[1]=0x0d;                                          // x=-h
    R[2]=0x0d;                                          // y=-h
    R[3]=0x01;                                          // s0=y1
    R[4]=pPminus;                                       // s1=Pminus
    R[5]=0;                                             // R[5]: s0与s1是否一样,1:同; 0:不同; 隐含值==1,首次运行时,必须赋值
    call ModMultiCSub;

    // 4.7 -z3=z1*(-h) && -(-h):
    //     [05:s2], [06:-y1]
    RA2_EXPRAM=0x05;                                    // RA2_EXPRAM: TEMP区顺序存取指针,首次运行时,必须赋值=0x05;最大为0x0f;
    R[0]=MSubS0;                                        // R[0]: 模乘指令类型:隐含值==S0AddS1,首次运行时,必须赋值
    R[1]=0x02;                                          // x=z1
    R[2]=0x0d;                                          // y=-h
    R[3]=0x0d;                                          // s0=-h
    R[4]=pPminus;                                       // s1=Pminus
    R[5]=0;                                             // R[5]: s0与s1是否一样,1:同; 0:不同; 隐含值==1,首次运行时,必须赋值
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
    R[5]=0;                                             // R[5]: s0与s1是否一样,1:同; 0:不同; 隐含值==1,首次运行时,必须赋值
    R[8]=U0U1_to_RAM_RA0;                               // R[8]: 通过RA0_EXPRAM指定[u0,u1]写Q区
    R[9]=0x02;                                          // u0=-z3
    call ModMultiCSub;

    // 4.10 x3=r^2+[-2u1h^2+(-h3)] && 2(-x1h^2)=(-x1h^2)+(-x1h^2):
    //     [0a:-x1h^2], [0b:r]
    R[1]=0x0b;                                          // x=r
    R[2]=0x0b;                                          // y=r
    R[3]=0x0a;                                          // s0=-x1h^2
    call ModMultiCSub;

    // 4.11 z3^2 && -2u1h^2+(-h3)此处给出
    //     [0c:-h^3], [0d:-2x1h^2]
    R[0]=ModMultiAddS0S1;                               // R[0]: 模乘指令类型:隐含值==S0AddS1,首次运行时,必须赋值
    R[1]=0x02;                                          // x=-z3
    R[2]=0x02;                                          // y=-z3
    R[3]=0x0c;                                          // s0=-h^3
    R[4]=0x0d;                                          // s1=-2x1h^2
    R[5]=0;                                             // R[5]: s0与s1是否一样,1:同; 0:不同; 隐含值==1,首次运行时,必须赋值
    call ModMultiCSub;

    // 4.12 s1h^3=(-s1)*(-h^3) && x3+(-x1h^2):
    //     [00:x3], [0e:*]
    R[1]=0x06;                                          // x=-s1=-y1
    R[2]=0x0c;                                          // y=-h^3
    R[3]=0x00;                                          // s0=x3
    R[4]=0x0a;                                          // s1=-x1h^2
    R[5]=0;                                             // R[5]: s0与s1是否一样,1:同; 0:不同; 隐含值==1,首次运行时,必须赋值
    R[8]=U0U1_to_RAM_RA0;                               // R[8]: 通过RA0_EXPRAM指定[u0,u1]写Q区
    R[9]=0x00;                                          // u0=x3    
    call ModMultiCSub;

    // 4.13 z3^4=(z3^2)^2 && null s0s1:
    //     [05:z3^2], [06:x3+(-x1h^2)]
    RA2_EXPRAM=0x05;                                    // RA2_EXPRAM: TEMP区顺序存取指针,首次运行时,必须赋值=0x05;最大为0x0f;
    R[1]=0x05;                                          // x=z3^2
    R[2]=0x05;                                          // y=z3^2
    call ModMultiCSub;

    // 4.14 -y3=r(x3-u1h^2)+s1h^3 && z3=-(-z3):
    //     [07:s1h^3], [08:*)]
    R[0]=MSubS0;                                        // R[0]: 模乘指令类型:隐含值==S0AddS1,首次运行时,必须赋值
    R[1]=0x0b;                                          // x=r
    R[2]=0x06;                                          // y=x3-u1h^2
    R[3]=0x02;                                          // s0=-z3
    R[4]=pPminus;                                       // s1=Pminus
    R[5]=0;                                             // R[5]: s0与s1是否一样,1:同; 0:不同; 隐含值==1,首次运行时,必须赋值
    call ModMultiCSub;

    // 4.15 az3^4=z3^4*a && 0+s1h3此处给出
    //     [09:z3^4], [02:z3)]
    R[0]=ModMultiAddS0S1;                               // R[0]: 模乘指令类型:隐含值==S0AddS1,首次运行时,必须赋值
    R[1]=0x09;                                          // x=z3^4
    R[2]=paRp;                                          // y=aRp
    R[3]=0x07;                                          // s0=s1h^3
    R[4]=pZero;                                         // s1=0
    R[5]=0;                                             // R[5]: s0与s1是否一样,1:同; 0:不同; 隐含值==1,首次运行时,必须赋值
    R[10]=S0S1_to_RAM_RA1;                              // R[10]: 通过RA1_EXPRAM指定[s0,s1]写Q区
    R[12]=0x02;                                         // s0=z3
    call ModMultiCSub;

    // 4.16 null multi && y3=-(-y3):
    //     [0a:-y3], [0b:*)]
    R[0]=MSubS0;                                        // R[0]: 模乘指令类型:隐含值==S0AddS1,首次运行时,必须赋值
    R[3]=0x0a;                                          // s0=-y3
    R[4]=pPminus;                                       // s1=Pminus
    R[5]=0;                                             // R[5]: s0与s1是否一样,1:同; 0:不同; 隐含值==1,首次运行时,必须赋值
    call ModMultiCSub;

    // 4.17 null multi && null [s0s1]:
    //     [03:az3^4], [01:y3]
    R[8]=U0U1_to_RAM_RA0;                               // R[8]: 通过RA0_EXPRAM指定[u0,u1]写Q区
    R[9]=0x03;                                          // u0=az3^4
    R[10]=S0S1_to_RAM_RA1;                              // R[10]: 通过RA1_EXPRAM指定[s0,s1]写Q区
    R[12]=0x01;                                         // s0=y3
    call ModMultiCSub;

    // 4.18 确定点加结果转向:
LPntAddRstJump:    
    goto LPNTADD1;                                      // to kP计算中的Q+P
    // Q+P 结束
    ///////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////
//  函数名称:
//      ModMultiSub;
//  函数功能:
//      uP的迭代模乘子程序,递归计算[xR,3xR]=[xR,3xR]*yR mod M
//  入口参数:
//      R_MultiIR:  模乘指令
//      RA1_EXPRAM: 乘数y在EXPRAM中的地址；
//  出口参数:
//      出口:无；
///////////////////////////////////////////////////////////////////
sub ModMultiSub;
    
    // 1. uP等待乘法器发出请求:
LWaitModMulti:
    RAMFresh;
    if(!FlagReqFromMulti) goto LWaitModMulti;

    // 2. y=EXPRAM[RA1_EXPRAM]:
LModMultiWrYReg:
    IR_EXPRAM = RAM_RA1_to_Y;                   // [yreg]=EXPRAM[RA1_EXPRAM],0x95;
    nop;
    
    // 3. 执行乘法指令:
    IR_Multi = R_MultiIR;
    RAMFresh;                                   // 刷新EXPRAM

    // 4. 返回:
    return;



///////////////////////////////////////////////////////////////////
//  函数名称:
//      ReadU0U1Sub;
//  函数功能:
//      等待并读取[u0,u1]到RA0_EXPRAM单元中;
//  入口参数:
//      无；
//  出口参数:
//      RA0_EXPRAM: [u0,u1]目标地址；
///////////////////////////////////////////////////////////////////
sub ReadU0U1Sub;
    // 1. 等待模乘器的可读信号:
LWaitU0U1:
    RAMFresh;
    if(!FlagREn) goto LWaitU0U1;
    set ReadSwap;                               // 读取交换

    // 2. 读取[u0,u1]到M[RA0_EXPRAM]:
    IR_EXPRAM = U0U1_to_RAM_RA0;                // M[RA0]=[u0,u1]
    nop;
    return;


///////////////////////////////////////////////////////////////////
//  函数名称:
//      MovRamRW1Sub;
//  函数功能:
//      根据RW方式将EXPRAM[RA1_EXPRAM]的1个数据移到RA0_EXPRAM中;
//  入口参数:
//      RA1_EXPRAM: 源数据序列的首地址；
//  出口参数:
//      RA0_EXPRAM: 目标数据序列的首地址；
///////////////////////////////////////////////////////////////////
sub MovRamRW1Sub;   
LMovRW1Ram:
    IR_EXPRAM = RAM_RA1_to_R7;               // M[RA1]=>DB0
    nop;                                     // 注意:两次R/W之间应间隔一条指令
    IR_EXPRAM = R7_to_RAM_RA0;               // DB0=>M[RA0]
    return;



///////////////////////////////////////////////////////////////////
//  函数名称:
//      MovRamRW3incSub;
//  函数功能:
//      根据RRR/WWW方式将EXPRAM[RA0_EXPRAM]的A个数据移到RA1_EXPRAM中;
//  入口参数:
//      R_BlkSrc: 源块的首地址
//      R_BlkDest: 目标块的首地址
//      R_BlkLen: 源块的长度
//  出口参数:
//      R_BlkDest: 目标块的首地址
//  中间变量:
//      RA1_EXPRAM: 源块的数据地址；
//      RA0_EXPRAM: 目标块的数据地址；
//      R[11]: 循环变量
///////////////////////////////////////////////////////////////////
sub MovRamRW3incSub;
    // 1. 块长为0,直接退出:
    A=R_BlkLen;                                 // 源块的长度
    if(Zero) goto LMovEnd;                      

    // 2. 复制源块的行0、行1分别到到目标块
    //    行0、行1:
    // 2.1 初始化行数:
    R[11]=2;                                    // 两行
    
    // 2.2 复制源块的x行到目标块的x行:
LMovNextLine:
    RA1_EXPRAM=R_BlkSrc;                        // 源块0行的首地址
    RA0_EXPRAM=R_BlkDest;                       // 目标块0行的首地址
    A=R_BlkLen;                                 // 源块的长度
LMovNextUnit:
    IR_EXPRAM = RAM_RA1inc_to_R7;               // M[RA1++]=>DB0
    nop;
    IR_EXPRAM = R7_to_RAM_RA0inc;               // DB0=>M[RA0++]
    A--;                                        // count--
    if(!Zero) goto LMovNextUnit;

    // 2.3 生成下一行首址:
    A=0x40;
    R_BlkSrc+=A;
    R_BlkDest+=A;

    // 2.4 两行复制完毕？
    R[11]--;
    if(!Zero) goto LMovNextLine;

    // 3. 模块结束:
LMovEnd:
    return;



///////////////////////////////////////////////////////////////////
//  函数名称:
//      ModMultiCSub(L:26);
//  函数功能:
//      参数化模乘
//  入口参数:
//      R[0]: 模乘指令类型:隐含值==S0AddS1,首次运行时,必须赋值
//      R[1]: x,3x地址,本函数禁止修改
//      R[2]: y地址,本函数禁止修改
//      R[3]: s0地址,本函数禁止修改
//      R[4]: s1地址; R[5]==1时,R[4]可以不赋值,本函数禁止修改
//      R[5]: s0与s1是否一样,1:同; 0:不同; 隐含值==1,首次运行时,必须赋值
//      R[8]: [u0,u1]写指令类型: U0U1_to_RAM_RA2inc / U0U1_to_RAM_RA0;
//            隐含值=U0U1_to_RAM_RA2inc,首次运行时,必须赋值
//      R[9]: [u0,u1]指定的的目标地址
//      R[10]:[s0,s1]写指令类型:S0S1_to_RAM_RA2inc / S0S1_to_RAM_RA1;
//            隐含值=S0S1_to_RAM_RA2inc,首次运行时,必须赋值
//      R[12]: [s0,s1]指定的目标地址
//      RA2_EXPRAM: TEMP区顺序存取指针,首次运行时,必须赋值=0x05;最大为0x0f;
//  出口参数:
//      无
//  临时变量:
//      RA0_EXPRAM: 临时EXPRAM地址指针
//      RA1_EXPRAM: 临时EXPRAM地址指针
//      A:累加器
///////////////////////////////////////////////////////////////////
sub ModMultiCSub;
    // 1. 预置[u0,u1]的目标地址:
    RA0_EXPRAM=R[9];                            // R[9]: [u0,u1]指定的的目标地址RA2/RA0

    // 2. 预置[s0,s1]的目标地址:
    RA1_EXPRAM=R[12];                           // R[12]: [s0,s1]指定的目标地址RA2/RA1
     
    // 3. 等待模乘器的可读信号:
LWaitReadFlag:
    RAMFresh;
    if(!FlagREn) goto LWaitReadFlag;
    set ReadSwap;                               // 读取交换

    // 4. 读取[u0,u1]到TEMP区或Q区:
    //    TEMP区:滚存,to_RA2++;
    //    Q区:   指定,to_RA1;
    IR_EXPRAM = R[8];                           // 读[u0,u1]到TEMP区(to_RA2++)或Q区(to_RA0)
    R[8]=U0U1_to_RAM_RA2inc;                    // 缺省[u0,u1]写指令为TEMP区滚存(to_RA2++)
    RA0_EXPRAM=R[1];                            // R[1]:x,3x地址

    // 5. 读取[s0,s1]到TEMP区或Q区:
    //    TEMP区:滚存,to_RA2++;
    //    Q区:   指定,to_RA1;
    IR_EXPRAM = R[10];                          // 读[s0,s1]到TEMP区(to_RA2++)或Q区(to_RA1)
    R[10]=S0S1_to_RAM_RA2inc;                   // 缺省[s0,s1]写指令为TEMP区滚存(to_RA2++)
    RA1_EXPRAM=R[2];                            // R[2]:y地址

    // 6. 装入[x,y,s0,s1]:
    IR_EXPRAM=RAM_RA1_to_Y;                     // 将乘数装入[y]寄存器
    RA1_EXPRAM=R[4];                            // R[4]:s1地址
    IR_EXPRAM=RAM_RA0_to_X3X;                   // 将被乘数装入[x,3x]寄存器
    RA0_EXPRAM=R[3];                            // R[3]:s0地址
    nop;
    IR_EXPRAM=RAM_RA0_to_S0;                    // 装入s0
    nop;
    IR_EXPRAM=RAM_RA0_to_S1;                    // 装入与s0相同的s1
    A=R[5];                                     // R[5]: s0与s1是否一样,1:同; 0:不同
    if(!Zero) goto LExecMulti;
    IR_EXPRAM=RAM_RA1_to_S1;                    // 装入指定的s1
    R[5]=1;                                     // R[5]=1:缺省认为s0与s1相同

    // 7. 执行乘法指令:
LExecMulti:
    IR_Multi=R[0];                              // R[0]: 模乘指令类型
    R[0]=S0AddS1;                               // R[0]=S0AddS1: 缺省指定x*y  mod m; t1s1+t0s0 mod m
 
    // 8. 返回:
    return;


///////////////////////////////////////////////////////////////////
//  函数名称:
//      GetRowNum
//  函数功能:
//      解析协议命令字D10-D9,提取e,k的行号0x00-0x80;
//  入口参数:
//      IR_ASDSP_H: Asdsp指令的高8比特;
//  出口参数:
//      R_RowNum: e,k的行号0x00-0x80;
//  临时变量:
//      A:累加器;
///////////////////////////////////////////////////////////////////
sub GetRowNum;
    // 1. 解析协议命令字D10-D9,提取e,k行号0x00-0x80:
    A=IR_ASDSP_H;
    if(A_bit2) goto LROWEQU80;                       // 10: 行号0x80
    if(A_bit1) goto LROWEQU40;                       // 01: 行号0x40
    R_RowNum=0x00;                                   // 00: 行号0x00
    goto LGetRowNumEnd;
LROWEQU80:
    R_RowNum=0x80;                                   // 提取e,k的行号0x80
    goto LGetRowNumEnd;
LROWEQU40:
    R_RowNum=0x40;                                   // 提取e,k的行号0x40

    // 2. 返回:
LGetRowNumEnd:
    return;