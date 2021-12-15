// VerilogLex.h: interface for the CVerilogLex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VERILOGLEX_H__9D55E3A9_B91F_48CA_8CD2_BCB935C068CC__INCLUDED_)
#define AFX_VERILOGLEX_H__9D55E3A9_B91F_48CA_8CD2_BCB935C068CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Lex.h"
#include "LALR.h"

class CLexFileSource;
class CVerilogLex : public Lex  
{
public:
	CVerilogLex(CLexFileSource* source);
virtual	int		Look();
};

class CVerilogLALR : public LALR
{
public:
	CVerilogLALR();
};


# define V_always 257
# define V_and 258
# define V_assign 259
# define V_begin 260
# define V_buf 261
# define V_bufif0 262
# define V_bufif1 263
# define V_case 264
# define V_casez 265
# define V_casex 266
# define V_cmos 267
# define V_default 268
# define V_defparam 269
# define V_deassign 270
# define V_disable 271
# define V_else 272
# define V_end 273
# define V_endcase 274
# define V_endfunction 275
# define V_endmodule 276
# define V_endprimitive 277
# define V_endspecify 278
# define V_endtable 279
# define V_endtask 280
# define V_event 281
# define V_for 282
# define V_force 283
# define V_forever 284
# define V_fork 285
# define V_function 286
# define V_highz0 287
# define V_highz1 288
# define V_if 289
# define V_initial 290
# define V_inout 291
# define V_input 292
# define V_integer 293
# define V_join 294
# define V_large 295
# define V_macromodule 296
# define V_medium 297
# define V_module 298
# define V_nand 299
# define V_negedge 300
# define V_nmos 301
# define V_nor 302
# define V_not 303
# define V_notif0 304
# define V_notif1 305
# define V_or 306
# define V_output 307
# define V_parameter 308
# define V_pmos 309
# define V_posedge 310
# define V_primitive 311
# define V_pull0 312
# define V_pull1 313
# define V_pulldown 314
# define V_pullup 315
# define V_rcmos 316
# define V_real 317
# define V_realtime 318
# define V_reg 319
# define V_release 320
# define V_repeat 321
# define V_rnmos 322
# define V_rpmos 323
# define V_rtran 324
# define V_rtranif0 325
# define V_rtranif1 326
# define V_scalared 327
# define V_small 328
# define V_strong0 329
# define V_strong1 330
# define V_supply0 331
# define V_supply1 332
# define V_specify 333
# define V_specparam 334
# define V_table 335
# define V_task 336
# define V_time 337
# define V_tran 338
# define V_tranif0 339
# define V_tranif1 340
# define V_tri 341
# define V_tri0 342
# define V_tri1 343
# define V_triand 344
# define V_trior 345
# define V_trireg 346
# define V_vectored 347
# define V_wait 348
# define V_wand 349
# define V_weak0 350
# define V_weak1 351
# define V_while 352
# define V_wire 353
# define V_wor 354
# define V_xnor 355
# define V_xor 356
# define V_eq_gt 357
# define V__gt 358
# define V_dot_gt 359
# define V_and_and 360
# define V_and_and_and 361
# define V_or_or 362
# define V_ls_eq 363
# define V_ls_ls 364
# define V_gt_eq 365
# define V_gt_gt 366
# define V_not_and 367
# define V_not_or 368
# define V_not_xor 369
# define V_xor_not 370
# define V_eq_eq 371
# define V_eq_eq_eq 372
# define V_not_eq 373
# define V_not_eq_eq 374
# define V_identifier 375
# define V_sys_identifier 376
# define V_uns_number 377
# define V_xbase_number 378
# define V_f_number 379
# define V_xbase 380
# define V_string 381
# define V_esc_identifier 382


#endif // !defined(AFX_VERILOGLEX_H__9D55E3A9_B91F_48CA_8CD2_BCB935C068CC__INCLUDED_)
