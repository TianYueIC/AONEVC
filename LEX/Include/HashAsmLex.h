// AsmLex.h: interface for the CAsmLex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__HASHASMLEX_H__)
#define __HASHASMLEX_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Lex.h"
#include "LALR.h"
class CHashAsmLex : public Lex  
{
public:
	CHashAsmLex(const char* filename);
	virtual ~CHashAsmLex();
	virtual	int	Look();
};
class CHashAsmLALR : public LALR  
{
public:
	CHashAsmLALR();
};

# define HASH_IDENTIFIER 257
# define HASH_call 258
# define HASH_goto 259
# define HASH_if 260
# define HASH_return 261
# define HASH_set 262
# define HASH_INTEGER_CONSTANT 263
# define HASH_sub 264
# define HASH_A 265
# define HASH_RA 266
# define HASH_INC 267
# define HASH_InReady 268
# define HASH_OutReady 269
# define HASH_const 270
# define HASH_nop 271
# define HASH_Reverse 272
# define HASH_Sbox 273
# define HASH_R 274
# define HASH_ADDC 275
# define HASH_SHIFTLC 276
# define HASH_operator 277
# define HASH_SHIFTL 278
# define HASH_SHIFTR 279
# define HASH_RSHIFTR 280
# define HASH_RSHIFTL 281
# define HASH_shift 282
# define HASH_Shift 282

#endif
