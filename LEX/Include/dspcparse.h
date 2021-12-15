#ifndef __DSPCPARSE_H__
#define __DSPCPARSE_H__

//仅在类型描述中使用的宏定义
// _2, _3, _4, 置入m_iType
// _1, _12, _20 将属性串起来
// MergeDeclaration 函数中将个属性合并
// _0 : _1
// _26: _1
// _50: _1
// _12: _12
// _36: _12
// _20: _4 注意：此处与EXP_   共用
// _0 最后作为头节点出现在 _, _51, _25, _50
// _12 最后作为头节点出现在 _11, _36
// _20 最后作为中间节点出现在类型声明链_18中
#define STORAGE_TYPEDEF				0X1	
#define STORAGE_EXTERN				0X2
#define STORAGE_STATIC			    0X3
#define STORAGE_AUTO			    0X4
#define STORAGE_REGISTER		    0X5
#define STORAGE_INLINE			    0X6
#define STORAGE_SPEC			    0XF
#define STORAGE_SPEC_NUM(x)			(x&STORAGE_SPEC)
#define IS_STORAGE_SPEC(x,y)		((x&STORAGE_SPEC)==y)
#define ISNOT_STORAGE_SPEC(x,y)		((x&STORAGE_SPEC)!=y)
#define CLEAR_STORAGE_SPEC(x)		x &= ~STORAGE_SPEC
#define SET_STORAGE_SPEC(x,y)		x = (x & ~STORAGE_SPEC) | y

#define TYPE_SPEC_CHAR			0x10
#define TYPE_SPEC_UCHAR			0x20
#define TYPE_SPEC_SINT			0x30
#define TYPE_SPEC_USINT			0x40
#define TYPE_SPEC_INT			0x50
#define TYPE_SPEC_UINT			0x60
#define TYPE_SPEC_FLOAT			0x70
#define TYPE_SPEC_DOUBLE		0x80
#define TYPE_SPEC_VOID		    0xA0
#define TYPE_SPEC_STRUCT	    0xB0
#define TYPE_SPEC_UNION		    0xC0
#define TYPE_SPEC_ENUM		    0xD0
#define TYPE_SPEC_NAME		    0xE0
#define TYPE_SPEC			    0xF0
#define TYPE_SPEC_NUM(x)		((x&TYPE_SPEC)>>4)
#define IS_TYPE_SPEC(x,y)		((x&TYPE_SPEC)==y)
#define ISNOT_TYPE_SPEC(x,y)	((x&TYPE_SPEC)!=y)
#define CLEAR_TYPE_SPEC(x)		x &= ~TYPE_SPEC
#define SET_TYPE_SPEC(x,y)		x = (x & ~TYPE_SPEC) | y
#define IS_TYPE_STRUCT_UNION(x)						\
			(((x&TYPE_SPEC)==TYPE_SPEC_STRUCT) ||	\
			 ((x&TYPE_SPEC)==TYPE_SPEC_UNION))
#define ISNOT_TYPE_COMPLEX(x)	((!IS_TYPE_STRUCT_UNION(x)) && ISNOT_TYPE_SPEC(x,TYPE_SPEC_NAME))
#define IS_ARITHMETICAL(x)		(x < 9)
#define IS_POINTER(x)		    (x == 9)
#define IS_INTEGER(x)			(x < 7)

#define TYPE_Q_CONST			0x100
#define TYPE_Q_VOLATILE			0x200
#define TYPE_Q					0x300

#define TYPE_LEN_LONG		    0x400
#define TYPE_LEN_SHORT		    0x800
#define TYPE_LEN			    0xc00

#define TYPE_SIGN_UNSIGNED	   0x1000
#define TYPE_SIGN_SIGNED	   0x2000
#define TYPE_SIGN			   0x3000

//变量存储时在描述节点增加定义
#define TYPE_ENUM_CONST	      0x800000
#define TYPE_LVALUE			 0x1000000

//类型声明链中使用的宏定义
//前两项与类型描述中相同，因为 const volatile 同时出现在描述和定义之中
//声明链中 
// NODE_EQUAL 可以是声明链的头一项 Branch 为声明链 Next为初始化链
// TYPE_NODE_ARRAY 的Branch为 EXP_ 链
// TYPE_NODE_FUNC 的Branch为类型链 和 NODE_COMMA
#define TYPE_NODE_CONST		 0x1
#define TYPE_NODE_VOLATIL	 0x2
#define TYPE_NODE_FUNC		 0x3
#define TYPE_NODE_ARRAY		 0x4
#define TYPE_NODE_IDSTR		 0x5
#define TYPE_NODE_POINTER	 0x6
#define TYPE_NODE_INCLUDE    0x7
#define TYPE_NODE_COLON	 	 0x8

#define TYPE_ERROR		   0x80000000

#define EXP_CONSTANT	        0x0
#define EXP_LOGIC_OP			0x4
#define EXP_LOGIC_OP_POST		0xa
#define EXP_IDSTRING	        0x5
#define EXP_INCLUDE				0x7
#define EXP_QUERY				0x8
#define EXP_QUERY_TF			0x9

#define EXP_CALL_FUNC			0xB

#define EXP_POSTFIX				0x200
#define EXP_POSTFIX_DOT			0x201
#define EXP_POSTFIX_ARROW		0x202
#define EXP_POSTFIX_FUNC		0x203
#define EXP_POSTFIX_ARRAY		0x204
#define EXP_POSTFIX_INC			0x205
#define EXP_POSTFIX_DEC			0x206

#define EXP_PREFIX				0x400
#define EXP_PREFIX_INC			0x401
#define EXP_PREFIX_DEC			0x402
#define EXP_PREFIX_SIZEOF		0x403
#define EXP_PREFIX_AND			0x404
#define EXP_PREFIX_PLUS			0x405
#define EXP_PREFIX_STAR			0x406
#define EXP_PREFIX_MINUS		0x407
#define EXP_PREFIX_INV			0x408
#define EXP_PREFIX_NOT			0x409

#define EXP_ASSIGN				0x800
#define EXP_MUL_ASSIGN  		0x801
#define EXP_DIV_ASSIGN  		0x802
#define EXP_MOD_ASSIGN  		0x803
#define EXP_ADD_ASSIGN  		0x804
#define EXP_SUB_ASSIGN  		0x805
#define EXP_LEFT_ASSIGN 		0x806
#define EXP_RIGHT_ASSIGN		0x807
#define EXP_AND_ASSING  		0x808
#define EXP_XOR_ASSING  		0x809
#define EXP_OR_ASSING   		0x80A
#define EXP_ADDC_ASSIGN 		0x80B
#define EXP_LEFTC_ASSIGN		0x80C

#define EXP_CAST			   0x1000

#define NODE_ELLIPSIS			0x10000000
#define NODE_EQUAL				0x20000000
#define NODE_COMMA				0x40000000
#define EXP_ERROR				0x80000000

class CDSPCParse : public LALR
{
public:
	CDefGroup	m_Defs;
	int			m_iNameTamp;
	CDSPCParse(Lex* lex);
	~CDSPCParse();
	virtual ValPoint CurrentValue();	
	virtual ValPoint Reduction(int num,int len);
	virtual int	CheckTypeName();

	virtual void action(int i1 = 0, int i2 = 0);

	void	GenCompileName(CString &str);

	void	GetTypeDef();

	void	MergeDeclaration();
	void	Operation(int type);
	void	DirectDeclarator(int i1);
	void	DirAbsDeclarator(int i1);
	void	PostfixExpression(int i1);
	void	CastExpress(int num);
	void	UnaryExpress(int num);
	void	ConstantCheck();
	void	Declaration();
	void	DeclareStructBit(int i1);
	void	EndField();//结束当前作用域
	void	DeclareFunction(int num);//开始函数声明
	void	StartCompound();//开始新的作用域
	//开始结构、枚举声明 type  0:不完整定义, 1:完整定义 2:无类型名的定义
	void	DeclareStruct(int type);
	void	ParamDeclare();
	void	IDList(int num);

	void	Expression();
	void	ConditionnalExp();
	void	Statement();
	void	PerformConst(ValPoint pV);
	
	int		CheckComplexType(ValPoint pV);

	static  CString m_strOut;
	CString &TRACEVar(){m_Defs.TRACEVar(m_strOut); return m_strOut;};
};
#endif //__DSPCPARSE_H__