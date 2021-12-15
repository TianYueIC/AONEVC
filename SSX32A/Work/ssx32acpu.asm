#include "ssx32acpu.def"
base var SelfTestWord;
base const  ALU_Test_Const[62]={ 
      // 1 st input data
      0x0000, 0x0000,  // A[31:16], A[15:0]
      0xffff, 0xffff,  // B[31:16], B[15:0], and Cin = 0
      // 2 nd input data
      0x0000, 0x0000,  // A[31:16], A[15:0]
      0x0000, 0x0000,  // B[31:16], B[15:0], and Cin = 0                          
      // 3 rd input data
      0x85c5, 0xc5c6,  // A[31:16], A[15:0]
      0xbdfd, 0xfdfd,  // B[31:16], B[15:0], and Cin = 0                          
      // 4 th input data
      0x88c8, 0xc8c9,  // A[31:16], A[15:0]
      0xbefe, 0xfefd,  // B[31:16], B[15:0], and Cin = 0
                                
      // 5 th input data
      0x9050, 0x5051,  // A[31:16], A[15:0]
      0xbf7f, 0x7f7d,  // B[31:16], B[15:0], and Cin = 0                                                    
      // 6 th input data
      0xb030, 0x3031,  // A[31:16], A[15:0]
      0xbfbf, 0xbfbd,  // B[31:16], B[15:0], and Cin = 0                                                    
      // 7 th input data
      0x0888, 0x8888,  // A[31:16], A[15:0]
      0xfbbb, 0xbbbb,  // B[31:16], B[15:0], and Cin = 1                                                    
      // 8 th input data
      0x1111, 0x1110,  // A[31:16], A[15:0]
      0xfbbb, 0xbbbb,  // B[31:16], B[15:0], and Cin = 1
                                                          
      // 9 th input data
      0xeeee, 0xeeef,  // A[31:16], A[15:0]
      0xeeee, 0xeeef,  // B[31:16], B[15:0], and Cin = 1                                                    
      //10 th input data
      0xe666, 0x6667,  // A[31:16], A[15:0]
      0xf777, 0x7777,  // B[31:16], B[15:0], and Cin = 1                                                    
      //11 th input data
      0x0000, 0x0000,  // A[31:16], A[15:0]
      0xffff, 0xffff,  // B[31:16], B[15:0], and Cin = 1                                                    
      //12 th input data
      0x5c5c, 0x5c5e,  // A[31:16], A[15:0]
      0x5fdf, 0xdfde,  // B[31:16], B[15:0], and Cin = 1 
                                                         
      //13 th input data
      0x4c8c, 0x8c8e,  // A[31:16], A[15:0]
      0x6fef, 0xefee,  // B[31:16], B[15:0], and Cin = 1                                                    
      //14 th input data
      0x4505, 0x0506,  // A[31:16], A[15:0]
      0x77f7, 0xf7f6,  // B[31:16], B[15:0], and Cin = 1                                                    
      //15 th input data
      0x4303, 0x0302,  // A[31:16], A[15:0]
      0x7bfb, 0xfbfa,  // B[31:16], B[15:0], and Cin = 1  
      0xd1d1, 0xd193
	  };
export SysInitial;
export SelfTestWord;
export SetupFT;

sub SetupFT;
	//定义 FT0  => RotateL24
	RD0 = 0x118;
	BarrelPort = RD0;

	//定义 FT1  => RotateL16
	RD0 = 0x210;
	BarrelPort = RD0;

	//定义 FT2  => RotateL8
	RD0 = 0x408;
	BarrelPort = RD0;

	//定义 FT3  => RotateL4
	RD0 = 0x804;
	BarrelPort = RD0;

	//定义 FT4  => ShiftR1
	RD0 = 0x105f;
	BarrelPort = RD0;

	//定义 FT5  => RotateL1
	RD0 = 0x2001;
	BarrelPort = RD0;	

	//定义 FT6  => ShiftL16
	RD0 = 0x4030;
	BarrelPort = RD0;	
	
	//定义 FT7  => ShiftR16
	RD0 = 0x8050;
	BarrelPort = RD0;	
	return;
//////////////////////////////////////////////////////////////////////
// 系统初始化过程
// 1. FT0～FT7 循环移位定义
// 2. 自检过程
// 3. 建立时间中断，时间间隔参数未确定
// 4. 空读IO缓冲区
//////////////////////////////////////////////////////////////////////
sub SysInitial;

	// 1. FT0～FT4 循环移位定义
	call SetupFT;
	// 2. 自检过程
///////////////////////////////
//ALU self test
//ROM self test and RAM self test
//ROM test first,then the RAM
///////////////////////////////
///////////////////////////////
// Registers and ROM mapping :
/// ROM[255] : code size of ROM, including the last code which used for check
//  RD0 : initial to 0x5555, used for Sn = Sum( Tn )
//  RD1 : for Tn = Sum( an );
//  RD2 : temp reg
//  RD3 : code size, and used as the return value
//      :  0x8000 for no errors
//      :  0x4000 for errors
//////////////////////////////
//export ROM_SelfTest;
//export RAM_SelfTest;
	clear(INT_EN);
	pop RD0;
	RSP = RD0;
/////////////////////////////////////////		
// ALU self Test
// an = A + B + C, n = 0, 1, 2, ..., 14
// C = 0 for the first 6 an; C = 1 for the last 9 an
// Tn = sum{ a0, a1, ..., an }
// Sn = sum{ T0, T1, ..., Tn }
// S-1 = 0x55555555
/////////////////////////////////////////	
	clear(RA2RAM);                     // RA2 address to ROM
	RD0 = offset ALU_Test_Const[0];    // get the entrance of Const for ALU self test
	RA2 = RD0;
	RD0 = 0x5555;                      //	
	RotateL16(RD0);
	RD1 = 0x5555;
	RD0 ^= RD1;                        // RD0 = 0x55555555
	RD1 = 0;
	RD2 = 9;
	RA1 = RD2;
	RD3 = 15;
ALU_Test_loop1 :   
	RA0 = RD3;         // store RD3
	RD2 = RA1;         // RA1 = 9
	RD2 -= RD3;        // determine the Carry
	RD2 = M[RA2++];    // A[31:16]
	RotateL16(RD2);
	RD2 ^= M[RA2++];   // get A[31:0]
	RD3 = M[RA2++];    // B[31:16]
	RotateL16(RD3);
	RD3 ^= M[RA2++];   // get B[31:0];
	RD2 ^+= RD3;       // A+B+Carry
	RD3 = 0;
	RD1 ^+= RD2;       // Tn = Tn-1 + an;
	RD1 ^+= RD3; 
      
	RD0  += RD1;       // Sn = Sn-1 + Tn
	RD0 ^+= RD3;
	RD3 = RA0;         //restore RD3
	RD3 --;
	if( nZero ) goto ALU_Test_loop1;  // continue to add 

	RD2 = M[RA2++];    // A[31:16]
	RotateL16(RD2);
	RD2 ^= M[RA2++];   // get A[31:0];

	RD3 = 0;
	RD1 ^+= RD2;       // Tn = Tn-1 + an;
	RD1 ^+= RD3; 
  
	RD0  += RD1;       // Sn = Sn-1 + Tn
	RD0 ^+= RD3;

	RD0++;
	if( Zero ) goto ALU_Ind_noerror;
	RD0--;
	if( Zero ) goto ALU_Ind_noerror;
	RD3 = 0x0400;      // ALU self test error
	goto ALU_selfTest_exit;
ALU_Ind_noerror :
	RD3 = 0x0800;      // ALU self test no error
ALU_selfTest_exit:
	set(RA2RAM);            


	RA1 = RD3;
/////////////////////////////////////////
// ROM self Test
/////////////////////////////////////////	
ROM_SelfTest :

	// initial
	RD3 = ROM[255];   // get the code size of ROM, including the last Sum
	RD0 = 0x5555;     // initialization for Sn, to 0x5555
	RD1 = RD0;        // intialization for Tn, to 0x5555
	RD2 = 0;          // for loop counting, initialize to 0
	RA2 = RD2;        // address initialized
	clear(RA2RAM);


ROM_Test_loop1 : 
	RD2 = 0x10000;   
	RD1 += M[RA2++];  // Tn = Tn-1 + an;   
	RD2 &= RD1;
	if( Zero ) goto Sn_count;
	RD1 -= RD2;
	RD1 ++;
Sn_count :
    RD2 = 0x10000; 
    RD0 += RD1;       // Sn = Sn-1 + Tn
    RD2 &= RD0;
    if( Zero ) goto ROM_continue;
    RD0 -= RD2;
    RD0 ++;
ROM_continue :    
    RD2 = RA2;
    RD2 -= RD3;
    if( nZero ) goto ROM_Test_loop1;  // continue to add 
    RD0 ++;
	RD2 = 0xffff;   
    RD0 &= RD2;                       // if RD0 = 0xffff, then no errors
    if( Zero ) goto No_Errors_Ind; 
    RD0 --;
	if( Zero ) goto No_Errors_Ind; 
	RD3 = 0x4000;
    goto Exit_loop;
No_Errors_Ind :
    RD3 = 0x8000;
       
Exit_loop : set( RA2RAM );
   
/////////////////////////////////////////////
// RAM self test
// modified March SS algorithm used
// 
/////////////////////////////////////////////
RAM_Self_Test :
    RD0 = RA1;
	RD3 += RD0;
	RA1 = RD3;   // store the result of ROM_test into RA1;
	RD0=0;
	RA2=RD0;
	RA2+=1;
////////////W0_ascend and descend/////////
	RA0=RD0;
	RD3=RAM_SIZE;
W0:	M[RA0++]=RD0;
	RD3 --;
	if(nZero)goto W0;
	RD3 = RAM_SIZE;
W0_A:	M[--RA0] = RD0;
	RD3 --;
	if(nZero)goto W0_A;
///////////////////////////////
lab:    RD1=RA2;
	RD0=0x0001;
	RD0-=RD1;
	if(Zero) goto W1;
	RD0=0x0002;
	RD0-=RD1;
	if(Zero) goto W2;
	RD0=0x0003;
	RD0-=RD1;
	if(Zero) goto W3;
	RD0=0x0004;
	RD0-=RD1;
	if(Zero) goto W4;
	RD0=0x0005;
	RD0-=RD1;
	if(Zero) goto W5;
	RD0=0x0006;
	RD0-=RD1;
	if(Zero) goto W6;
	RD0=0x0007;
	RD0-=RD1;
	if(Zero) goto W7;
	RD0=0x0008;
	RD0-=RD1;
	if(Zero) goto W8;
	RD0=0x0009;
	RD0-=RD1;
	if(Zero) goto W9;
	RD0=0x000a;
	RD0-=RD1;
	if(Zero) goto W10;
	RD0=0x000b;
	RD0-=RD1;
	if(Zero) goto W11;
	RD0=0x000c;
	RD0-=RD1;
	if(Zero) goto W12;
	RD0=0x000d;
	RD0-=RD1;
	if(Zero) goto W13;
	RD0=0x000e;
	RD0-=RD1;
	if(Zero) goto W14;
	RD0=0x000f;
	RD0-=RD1;
	if(Zero) goto W15;
	
////////////////////////
W1:	RD1=0;       // RD1 = 0
	RD2=RD1;     // RD2 = 0
	goto DTest;
W2:	Not(RD2);
    RD1=RD2;     // RD1 = 1, RD2 = 1
	goto DTest;
W3:	Not(RD2);
    RD1=RD2;     // RD1 = 0, RD2 = 0
	goto ATest;
W4:	Not(RD2);
    RD1=RD2;     // RD1 = 1, RD2 = 1
	goto ATest;
W5: Not(RD2);
    RD1=RD2;     // RD1 = 0, RD2 = 0x5555_5555
	RD2=0x5555;
	RD0=RD2;
	RotateL16(RD2);
	RD2^=RD0;
	goto DTest;
W6: Not(RD2);
    RD1=RD2;    //RD1 = 0xaaaa_aaaa, RD2 = 0xaaaa_aaaa
	goto DTest;
W7:	Not(RD2);
    RD1=RD2;    //RD1 = 0x5555_5555, RD2 = 0x3333_3333
	RD2=0x3333;
	RD0=RD2;
	RotateL16(RD2);
	RD2^=RD0;      //32'x3333_3333
	goto ATest;
W8: Not(RD2);
    RD1=RD2;       // RD1 = 0xcccc_cccc, RD2 = 0xcccc_cccc
	goto ATest;
W9: Not(RD2);
    RD1=RD2;      // RD1 = 0x3333_3333, RD2 = 0x0f0f_0f0f 
	RD2=0x0f0f;
	RD0=RD2;
	RotateL16(RD2);
	RD2^=RD0;    //32'x0f0f_0f0f
	goto DTest;
W10:Not(RD2);
    RD1=RD2;    //RD1 = RD2 = 0xf0f0_f0f0
	goto DTest;
W11:Not(RD2);
    RD1=RD2;       //RD1 = RD2 = 0x0f0f_0f0f
	RD2=0x00ff;
	RD0=RD2;
	RotateL16(RD2);
	RD2^=RD0;      //32'x00ff_00ff
	goto ATest;
W12:Not(RD2);
    RD1=RD2;       //RD1=RD2=0xff00_ff00
	goto ATest;
W13:Not(RD2);
    RD1=RD2;      //RD1=00ff_00ff, RD2 = 0x0000_ffff
	RD2=0xffff;
	RD0=0;
	RD2^=RD0;    //RD2 = 0x0000_ffff
	goto DTest;
W14:Not(RD2);
    RD1=RD2;    //RD1 = RD2 = 0xffff_0000
	goto DTest;
W15:
	RD0=0;
	RA0=RD0;
	RD3=RAM_SIZE;
	Not(RD2);
read:
	RD0=M[RA0];
	RD0-=RD2;
	if(nZero)goto error_exit;
    RD0=M[RA0++];
	RD0-=RD2;
	if(nZero)goto error_exit;
	--RD3;
	if(nZero)goto read;
    goto RAM_noerror_exit;

////////////ascend r1/r2/w3/r4/w5 process /////////////
// RD1 for r1 and r2, RD2 for w3 and r4 , ~RD2 for w5
///////////////////////////////////////////////////////
ATest:
	RD0=0;
	RA0=RD0;
	RD3=RAM_SIZE;
ascend:	
	RD0=M[RA0];   // r
	RD0-=RD1;
	if(nZero)goto error_exit;
	RD0=M[RA0];   // r
	RD0-=RD1;
	if(nZero)goto error_exit;
	M[RA0]=RD2;   // w
	RD0=M[RA0];   // r
	RD0-=RD2;
	if(nZero)goto error_exit;
	Not(RD2);
    M[RA0++]=RD2;//w, 32'b	
	Not(RD2);
	--RD3;
	if(nZero) goto ascend;
	goto count;
////////////descend  r1/r2/w3/r4/w5 process//////////
// RD1 for r1 and r2, RD2 for w3 and r4 , ~RD2 for w5
//////////////////////////////////////////////////////
DTest:  
	RD3=RAM_SIZE;
	RA0=RD3;
descend:	
	RD0=M[--RA0];
	RD0-=RD1;
	if(nZero)goto error_exit;
	RD0=M[RA0];
	RD0-=RD1;
	if(nZero)goto error_exit;
	M[RA0]=RD2;
	RD0=M[RA0];
	RD0-=RD2;
	if(nZero)goto error_exit;
	Not(RD2);
	M[RA0]=RD2;//32'x 
	Not(RD2);   
	--RD3;
	if(nZero) goto descend;	
	goto count;	
//////////////////////////////
count:
	RA2+=1;
	RD0=0x0010;
	RD1=RA2;
	RD0-=RD1;
	if(nZero) goto lab;        
RAM_noerror_exit : 
	RD1 = 0x2000;             // RD1 : 0x2000, RAM no error
	goto ROM_RAM_test_exit;
error_exit :
	RD1 = 0x1000;             // RD1 : 0x1000, RAM error 
ROM_RAM_test_exit :
	RD3 = RA1;
	RD3 += RD1;      //  RD3 : 0xa800 : ALU & ROM & RAM no error
					 //      : 0x9000 : ROM no error, RAM error
					 //      : 0x6000 : ROM error, RAM no error
					 //      : 0x5000 : ROM & RAM error
					 //		 : 0x?400 : ALU error
					 // bit 15: ROM ok
					 // bit 14: ROM error
					 // bit 13: RAM ok
					 // bit 12: RAM error
					 // bit 11: ALU ok
					 // bit 10: ALU error
	SelfTestWord = RD3;
	RD0 = RAM_SIZE;
	RD1 = RSP;
	RSP = RD0;
	push RD1;
	set(INT_EN);
	// 3. 建立时间中断
	set(TimerReset);			// 向时钟写入初始值
	SET_RD1_DATA(0x1d9d3b3a);	// 参数待定 ASSERT
	TimerData = RD1;
	set(IntTimer);

	return;

//////////////////////////////////////////////////////////////////////
// 时间中断服务程序
//   在该中断服务程序中，要求复位Timer并重置初始值
//   时钟处理程序待定 ASSERT
//////////////////////////////////////////////////////////////////////
intv IntTimer entry:
	set(INT_EN);
	push RD0;
	push RD1;
	set(TimerReset);			// 向时钟写入初始值，清中断
	SET_RD1_DATA(0x1d9d3b3a);	// 参数待定 ASSERT
	TimerData = RD1;
	pop	 RD1;
	pop  RD0;
	ireturn;
