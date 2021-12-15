#if !defined(__CCONSTLEX_H__)
#define __CCONSTLEX_H__
#if _MSCP_VER > 1000
#pragma once
#endif // _MSCP_VER > 1000
#include "Lex.h"
#include "LALR.h"
class CLexFileSource;
class CConstLex : public Lex
{
public:
	CConstLex(CLexSource* source);
virtual	int		Look();
};

class CConstLALR : public LALR
{
public:
	CConstLALR();
};

# define CP_IDENTIFIER 257
# define CP_INTEGER_CONSTANT 258
# define CP_CHARACTER_CONSTANT 259
# define CP_LEFT_OP 260
# define CP_AND_OP 261
# define CP_OR_OP 262
# define CP_RIGHT_OP 263
# define CP_LE_OP 264
# define CP_GE_OP 265
# define CP_EQ_OP 266
# define CP_NE_OP 267


#endif
