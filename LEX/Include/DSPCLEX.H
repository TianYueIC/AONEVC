#ifndef __DSPCLEX_H__
#define __DSPCLEX_H__
#include "Lex.h"
#include "LALR.h"
class CDSPCLex  : public Lex
{
public:
	CDSPCLex(CLexFileSource * source);
	virtual ~CDSPCLex();
virtual	int	Look();
};

class CDSPCLALR : public LALR
{
public:
	CDSPCLALR();
};


# define C_IDENTIFIER 257
# define C_INTEGER_CONSTANT 258
# define C_CHARACTER_CONSTANT 259
# define C_FLOAT_CONSTANT 260
# define C_ENUM_CONSTANT 261
# define C_STRING_LITERAL 262
# define C_sizeof 263
# define C_inline 264
# define C_PTR_OP 265
# define C_INC_OP 266
# define C_DEC_OP 267
# define C_LEFT_OP 268
# define C_RIGHT_OP 269
# define C_LE_OP 270
# define C_GE_OP 271
# define C_EQ_OP 272
# define C_NE_OP 273
# define C_AND_OP 274
# define C_OR_OP 275
# define C_MUL_ASSIGN 276
# define C_DIV_ASSIGN 277
# define C_MOD_ASSIGN 278
# define C_ADD_ASSIGN 279
# define C_ADDC_ASSIGN 280
# define C_SUB_ASSIGN 281
# define C_LEFT_ASSIGN 282
# define C_LEFTC_ASSIGN 283
# define C_RIGHT_ASSIGN 284
# define C_AND_ASSING 285
# define C_XOR_ASSING 286
# define C_OR_ASSING 287
# define C_type_name 288
# define C_typedef 289
# define C_extern 290
# define C_static 291
# define C_auto 292
# define C_register 293
# define C_char 294
# define C_short 295
# define C_int 296
# define C_long 297
# define C_signed 298
# define C_unsigned 299
# define C_float 300
# define C_double 301
# define C_const 302
# define C_volatile 303
# define C_void 304
# define C_struct 305
# define C_union 306
# define C_enum 307
# define C_ELLIPSIS 308
# define C_case 309
# define C_default 310
# define C_if 311
# define C_else 312
# define C_switch 313
# define C_while 314
# define C_do 315
# define C_for 316
# define C_goto 317
# define C_continue 318
# define C_break 319
# define C_return 320

# define C_ERRORID 321
#endif //__DSPCLEX_H__