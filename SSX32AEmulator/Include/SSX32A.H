#ifndef __SSX32A_h__
#define __SSX32A_h__
////////////以下宏定义和 ssx32acpu.def 文件共同维护/////////
#define RF_INTERRUPT   30
#define RF_ZERO     29
#define RF_NZERO    28
#define RF_CARRY    27
#define RF_NCARRY   26
#define RF_OVER	    25
#define RF_OVERUP   24
#define RF_BITZERO  23
#define RF_NBITZERO 22
#define RF_EXFLAG	21
#define RF_NEXFLAG	20
#define RF_T1		19
#define RF_NT1		18
#define RF_T0		17
#define RF_NT0		16

///////////////////////////////
// test by  xianjun
#define RF_XIANJUN	10
///////////////////////////////

#define RF_ECCACCFLAG	5
#define RF_ASDSPFLAG	4
#define RF_MOANB	3
//					2
#define RF_TXFLAG	1
#define RF_RXFLAG	0

#define RM_MASK      0
#define RM_BITPOS    1
#define RM_EXPRAMDATA		27

#define RT_TRACE_EXIT		0x400000
#define RT_TRACE_OUT		0x200000
#define RT_TRACE_DUMP		0x100000

#define RP_TIMERDATA		0
#define RP_TXRDATA			1
#define RP_TXRDATA_LEN		2
//							3
#define RP_LSHIFTDATA		4
#define RP_ACCIR			5
#define RP_EXPRAMIR			6


///////////////////////////////
// test by  xianjun
#define RP_XIANJUN		    7
#define RP_TEMP1		    8
#define RP_TEMP2		    9
///////////////////////////////


#define RP_DB1REG			10
#define RP_ASDSP			11
#define RP_ECCACC			12

#define RP_TASK_SEL			17
#define RP_RES_ENABLE		18
#define RP_RES_STATE		19
#define RP_RES_SEL			20
#define RP_RES_FLAG			21
#define RP_TRACE			23

#define RP_BITMASK			24
#define RP_BITINDEX			25
#define RP_BARRELPORT		26
#define RP_INTVECTOR		27

#define RP_CPUTIME			22


#define RB_INT_EN			0x10
#define RB_RA2ROM			0x11
#define RB_EXPRAMEN0		0x12
#define RB_ACK				0x18
#define RB_OUTERIOEN		0x19
#define RB_EXPRAMEN1		0x1a

#define RB_MOTRIGAB			0x29
#define RB_MOTRIGX			0x2a
#define RB_WMOX				0x2b
#define RB_DB1TOLSHIFT		0x31
#define RB_LSHIFTTODB1		0x32
#define RB_TIMERRESET		0x33

#define RES_INPUT			0x00000001
#define RES_OUTPUT			0x80000000
#define RES_ASDSP0			0x00000002
#define RES_ASDSP			0x007ffffe
#define RES_ASDSPn			0x00800000
#define RES_ECCACC0			0x00800000
#define RES_ECCACC			0x01800000
#define RES_ECCACCn			0x02000000

#define IOBUFFER_MAX_SIZE (4*1024)
// 私有空间
#define PRIVATE_RAM_SIZE 256
#define PRIVATE_EXPRAM_SIZE 64
// 系统空间
#define SYSTEM_RAM_SIZE 256
#define SYSTEM_EXPRAM_SIZE 64*4
// 任务数量
#define TASK_NUM	8
#define ASSDSP_NUM	20

#endif //__SSX32A_h__

//////////////////////////////////////////////////////////
