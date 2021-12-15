// AsmLex.h: interface for the CAsmLex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_UPLEX_H_)
#define _UPLEX_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Lex.h"
#include "LALR.h"

class CUpLex : public Lex  
{
public:
	CUpLex(const char* filename);
	virtual ~CUpLex();
	virtual	int	Look();
};

class CUpLALR : public LALR
{
public:
	CUpLALR();
};

# define UP_IDENTIFIER 257
# define UP_call 258
# define UP_goto 259
# define UP_if 260
# define UP_return 261
# define UP_set 262
# define UP_subentry 263
# define UP_C 264
# define UP_F 265
# define UP_SHIFT 266
# define UP_SHIFTR 267
# define UP_R 268
# define UP_RAM 269
# define UP_INTEGER_CONSTANT 270

#endif // !defined(_UPLEX_H_)
