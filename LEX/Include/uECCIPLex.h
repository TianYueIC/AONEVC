// AsmLex.h: interface for the CAsmLex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_UECCIPLEX_H_)
#define _UECCIPLEX_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Lex.h"
#include "LALR.h"

class CuECCIPLex : public Lex  
{
public:
	CuECCIPLex(const char* filename);
	virtual ~CuECCIPLex();
	virtual	int	Look();
};

class CuECCIPLALR : public LALR
{
public:
	CuECCIPLALR();
};

# define ECCIP_A 257
# define ECCIP_R 258
# define ECCIP_return 259
# define ECCIP_sub 260
# define ECCIP_goto 261
# define ECCIP_if 262
# define ECCIP_call 263
# define ECCIP_nop 264
# define ECCIP_set 265
# define ECCIP_C 266
# define ECCIP_F 267
# define ECCIP_IDENTIFIER 268
# define ECCIP_INTEGER_CONSTANT 269
# define ECCIP_DEC 270
# define ECCIP_INC 271
# define ECCIP_SHIFTL 272
# define ECCIP_SHIFTR 273
# define ECCIP_ADD 274
# define ECCIP_SUB 275
# define ECCIP_AND 276
# define ECCIP_OR 277
# define ECCIP_XOR 278

#endif // !defined(_UPLEX_H_)
