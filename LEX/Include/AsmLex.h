// AsmLex.h: interface for the CAsmLex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASMLEX_H__96DCEDD5_5672_4A21_B2E1_4001FA88B682__INCLUDED_)
#define AFX_ASMLEX_H__96DCEDD5_5672_4A21_B2E1_4001FA88B682__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////
//
//该类不用做任何添加即可完成词法分析
//
//////////////////////////////////////
#include "Lex.h"
class CAsmLex : public Lex  
{
public:
	CAsmLex(const char* filename);
	virtual ~CAsmLex();
	virtual	int	Look();
};

#include "LALR.h"

class CAsmLALR : public LALR
{
public:
	CAsmLALR();
};


# define ASM_IDENTIFIER 257
# define ASM_far 258
# define ASM_near 259
# define ASM_extern 260
# define ASM_export 261
# define ASM_base 262
# define ASM_offset 263
# define ASM_if 264
# define ASM_goto 265
# define ASM_call 266
# define ASM_sub 267
# define ASM_var 268
# define ASM_label 269
# define ASM_push 270
# define ASM_pop 271
# define ASM_return 272
# define ASM_subentry 273
# define ASM_const 274
# define ASM_nop 275
# define ASM_RA 276
# define ASM_RD 277
# define ASM_RSP 278
# define ASM_FRP 279
# define ASM_RAM 280
# define ASM_ROM 281
# define ASM_MEM 282
# define ASM_INTEGER_CONSTANT 283
# define ASM_INC 284
# define ASM_DEC 285
# define ASM_SHIFT 286
# define ASM_SHIFTC 287
# define ASM_ADD 288
# define ASM_ADDC 289
# define ASM_SUB 290
# define ASM_AND 291
# define ASM_XOR 292
# define ASM_RF 293
# define ASM_RP 294
# define ASM_RM 295
# define ASM_FT 296
# define ASM_SHIFTR 297
# define ASM_set 298
# define ASM_clear 299
# define ASM_entry 300
# define ASM_intv 301

#endif
