#ifndef EXP_H_INCLUDED
#define EXP_H_INCLUDED

#include <vector>
#include <string>
#include "..\lexer\lexer_types.h"
#include "..\misc\smart_ptrs.h"
#include "decl.h"
#include "..\generator\asm_program.h"

enum ExprNodeClass {
    EXPR_NODE_CLASS_EXP,
    EXPR_NODE_CLASS_ASSIGNMENT_EXP,
    EXPR_NODE_CLASS_CONDITIONAL_EXP,
    EXPR_NODE_CLASS_BINARY_EXP,
    EXPR_NODE_CLASS_UNARY_EXP,
    EXPR_NODE_CLASS_POSTFIX_EXP,
    EXPR_NODE_CLASS_PRIMARY_EXP
};

struct ExprNode;
struct DeclFunc;

typedef std::auto_ptr<ExprNode> ExprNodeP;

struct ExprNode {
	ExprType expr_type;
	bool is_lvalue;
	bool is_const_exp;
	int const_exp_value;
    virtual ~ExprNode() {}
    virtual ExprNodeClass GetExprNodeClass() const = 0;
	virtual ExprNodeP CreateCopy() const = 0;
    virtual bool IsUnaryExp() const { return false; }
	virtual void Print(int, std::ostream&) const = 0;
	virtual void Generate(AsmProgram&) const = 0;
	virtual AsmSegT GenerateAddr(AsmProgram&) const = 0;
	void PointerGeneration();
};

struct Exp : public ExprNode {
    //exp ::= assignment_exp | assignment_exp ',' exp
    ListP<ExprNode*> assignment_exp_list;
    Exp(ListP<ExprNode*>&);
    ExprNodeClass GetExprNodeClass() const {
        return EXPR_NODE_CLASS_EXP; }
	ExprNodeP CreateCopy() const;
    void Print(int, std::ostream&) const;
	void Generate(AsmProgram&) const;
	AsmSegT GenerateAddr(AsmProgram&) const;
};

struct AssignmentExp : public ExprNode {
    //assignment_exp ::= conditional_exp |
    //                   unary_exp assignment_operator assignment_exp
    ExprNodeP unary_exp;
    ExprNodeP assignment_exp;
    AssignmentExp(ExprNodeP, ExprNodeP);
    ExprNodeClass GetExprNodeClass() const {
        return EXPR_NODE_CLASS_ASSIGNMENT_EXP; }
	ExprNodeP CreateCopy() const;
    void Print(int, std::ostream&) const;
	AsmSegT InternalGenerate(AsmProgram&) const;
	void Generate(AsmProgram&) const;
	AsmSegT GenerateAddr(AsmProgram&) const;
};

struct ConditionalExp : public ExprNode {
    //conditional_exp ::= logical_or_exp |
    //                    logical_or_exp '?' exp ':' conditional_exp
    ExprNodeP logical_or_exp;
    ExprNodeP exp;
    ExprNodeP conditional_exp;
    ConditionalExp(ExprNodeP, ExprNodeP, ExprNodeP);
    ExprNodeClass GetExprNodeClass() const {
        return EXPR_NODE_CLASS_CONDITIONAL_EXP; }
	ExprNodeP CreateCopy() const;
    void Print(int, std::ostream&) const;
	void Generate(AsmProgram&) const;
	AsmSegT GenerateAddr(AsmProgram&) const;
};

enum BinaryExpClass {
    BINARY_EXP_CLASS_LOGICAL_OR,
    BINARY_EXP_CLASS_LOGICAL_AND,
    BINARY_EXP_CLASS_INCLUSIVE_OR,
    BINARY_EXP_CLASS_EXCLUSIVE_OR,
    BINARY_EXP_CLASS_AND,
    BINARY_EXP_CLASS_EQUALITY,
    BINARY_EXP_CLASS_RELATIONAL,
    BINARY_EXP_CLASS_SHIFT,
    BINARY_EXP_CLASS_ADDITIVE,
    BINARY_EXP_CLASS_MULT,
	BINARY_EXP_CLASS_NONE
};

struct BinaryExp : public ExprNode {
    //logical_or_exp ::= logical_and_exp |
    //                   logical_and_exp '||' logical_or_exp
    //logical_and_exp ::= inclusive_or_exp |
    //                    inclusive_or_exp '&&' logical_and_exp
    //inclusive_or_exp ::= exclusive_or_exp |
    //                     exclusive_or_exp '|' inclusive_or_exp
    //exclusive_or_exp ::= and_exp |
    //                     and_exp '^' exclusive_or_exp
    //and_exp ::= equality_exp |
    //            equality_exp '&' and_exp
    //equality_exp ::= relational_exp |
    //                 relational_exp equality_operator equality_exp
    //relational_exp ::= shift_expression |
    //                   shift_expression relational_operator relational_exp
    //shift_expression ::= additive_exp |
    //                     additive_exp shift_operator shift_expression
    //additive_exp ::= mult_exp |
    //                 mult_exp additive_operator additive_exp
    //mult_exp ::= unary_exp |
    //             unary_exp mult_operator mult_exp
    BinaryExpClass binary_exp_class;
    ExprNodeP arg1;
    OperatorT op;
    ExprNodeP arg2;
    BinaryExp(BinaryExpClass, ExprNodeP, OperatorT, ExprNodeP);
    ExprNodeClass GetExprNodeClass() const {
        return EXPR_NODE_CLASS_BINARY_EXP; }
	ExprNodeP CreateCopy() const;
    void Print(int, std::ostream&) const;
	void Generate(AsmProgram&) const;
	AsmSegT GenerateAddr(AsmProgram&) const;
};

enum UnaryExpClass {
    UNARY_EXP_CLASS_INC_DEC,
    UNARY_EXP_CLASS_UNARY_OPERATOR,
    UNARY_EXP_CLASS_SIZEOF_UNARY_EXP,
    UNARY_EXP_CLASS_SIZEOF_TYPE_NAME
};

struct UnaryExp : public ExprNode {
    //unary_exp ::= postfix_exp |
    //              inc_dec_operator unary_exp |
    //              unary_operator unary_exp
	virtual ~UnaryExp() {}
    ExprNodeClass GetExprNodeClass() const {
        return EXPR_NODE_CLASS_UNARY_EXP; }
    bool IsUnaryExp() const { return true; }
    virtual UnaryExpClass GetUnaryExpClass() const = 0;
};

struct UnaryExpIncDec : public UnaryExp {
    //unary_exp ::= inc_dec_operator unary_exp
    OperatorT inc_dec_operator;
    ExprNodeP unary_exp;
    UnaryExpIncDec(OperatorT, ExprNodeP);
	ExprNodeP CreateCopy() const;
    UnaryExpClass GetUnaryExpClass() const {
        return UNARY_EXP_CLASS_INC_DEC; }
    void Print(int, std::ostream&) const;
	void Generate(AsmProgram&) const;
	AsmSegT GenerateAddr(AsmProgram&) const;
};

struct UnaryExpUnaryOperator : public UnaryExp {
    //unary_exp ::= unary_operator unary_exp
    OperatorT unary_operator;
    ExprNodeP unary_exp;
    UnaryExpUnaryOperator(OperatorT, ExprNodeP);
	ExprNodeP CreateCopy() const;
    UnaryExpClass GetUnaryExpClass() const {
        return UNARY_EXP_CLASS_UNARY_OPERATOR; }
    void Print(int, std::ostream&) const;
	void Generate(AsmProgram&) const;
	AsmSegT GenerateAddr(AsmProgram&) const;
};

enum PostfixExpClass {
    POSTFIX_EXP_CLASS_ARRAY_INDEX,
    POSTFIX_EXP_CLASS_FUNC_CALL,
    POSTFIX_EXP_CLASS_POINT,
    POSTFIX_EXP_CLASS_INC_DEC
};

struct PostfixExp : public ExprNode {
    //postfix_exp ::= primary_exp |
    //                postfix_exp '[' exp ']' |
    //                postfix_exp '(' argument_exp_list ')'
    //                postfix_exp '('	                ')'
    //                postfix_exp point_arrow_operator id
    //                postfix_exp inc_dec_operator
	virtual ~PostfixExp() {}
    ExprNodeP postfix_exp;
    PostfixExp(ExprNodeP);
    ExprNodeClass GetExprNodeClass() const {
        return EXPR_NODE_CLASS_POSTFIX_EXP; }
    bool IsUnaryExp() const { return true; }
    virtual PostfixExpClass GetPostfixExpClass() const = 0;
};

struct PostfixExpArrayIndex : public PostfixExp {
    //postfix_exp ::= postfix_exp '[' exp ']'
    ExprNodeP exp;
    PostfixExpArrayIndex(ExprNodeP, ExprNodeP);
	ExprNodeP CreateCopy() const;
    PostfixExpClass GetPostfixExpClass() const {
        return POSTFIX_EXP_CLASS_ARRAY_INDEX; }
    void Print(int, std::ostream&) const;
	AsmSegT InternalGenerate(AsmProgram&) const;
	void Generate(AsmProgram&) const;
	AsmSegT GenerateAddr(AsmProgram&) const;
};

typedef ListP<ExprNode*> ArgumentExpList;

struct PostfixExpFuncCall : public PostfixExp {
    //postfix_exp ::= postfix_exp '(' argument_exp_list ')' |
    //                postfix_exp '('                   ')'
    //argument_exp_list ::= assignment_exp |
    //                      argument_exp_list ',' assignment_exp
    ArgumentExpList argument_exp_list;
    PostfixExpFuncCall(ExprNodeP, ArgumentExpList&);
	ExprNodeP CreateCopy() const;
    PostfixExpClass GetPostfixExpClass() const {
        return POSTFIX_EXP_CLASS_FUNC_CALL; }
    void Print(int, std::ostream&) const;
	void Generate(AsmProgram&) const;
	AsmSegT GenerateAddr(AsmProgram&) const;
};

struct PostfixExpPoint : public PostfixExp {
    //postfix_exp ::= postfix_exp '.' id
    StructDecl* struct_decl;
	std::string name;
    PostfixExpPoint(ExprNodeP, std::string);
	ExprNodeP CreateCopy() const;
    PostfixExpClass GetPostfixExpClass() const {
        return POSTFIX_EXP_CLASS_POINT; }
    void Print(int, std::ostream&) const;
	AsmSegT InternalGenerate(AsmProgram&) const;
	void Generate(AsmProgram&) const;
	AsmSegT GenerateAddr(AsmProgram&) const;
};

struct PostfixExpIncDec : public PostfixExp {
    //postfix_exp ::= postfix_exp inc_dec_operator
    OperatorT inc_dec_operator;
    PostfixExpIncDec(ExprNodeP, OperatorT);
	ExprNodeP CreateCopy() const;
    PostfixExpClass GetPostfixExpClass() const {
        return POSTFIX_EXP_CLASS_INC_DEC; }
    void Print(int, std::ostream&) const;
	void Generate(AsmProgram&) const;
	AsmSegT GenerateAddr(AsmProgram&) const;
};

enum PrimaryExpClass {
    PRIMARY_EXP_CLASS_VAR,
    PRIMARY_EXP_CLASS_FUNC,
    PRIMARY_EXP_CLASS_INT_CONST,
    PRIMARY_EXP_CLASS_REAL_CONST,
    PRIMARY_EXP_CLASS_STRING_CONST
};

struct PrimaryExp : public ExprNode {
    //primary_exp ::= id |
    //                int_const |
    //                char_const |
    //                real_const |
    //                string_const |
    //                enumeration_const |
    //                '(' exp ')'
	virtual ~PrimaryExp() {}
    ExprNodeClass GetExprNodeClass() const {
        return EXPR_NODE_CLASS_PRIMARY_EXP; }
    bool IsUnaryExp() const { return true; }
    virtual PrimaryExpClass GetPrimaryExpClass() const = 0;
};

struct PrimaryExpVar : public PrimaryExp {
    //primary_exp ::= id
	DeclVar* decl_var;
    std::string name;
	PrimaryExpVar(DeclVar*, const std::string&);
	ExprNodeP CreateCopy() const;
    PrimaryExpClass GetPrimaryExpClass() const {
        return PRIMARY_EXP_CLASS_VAR; }
    void Print(int, std::ostream&) const;
	void Generate(AsmProgram&) const;
	AsmSegT GenerateAddr(AsmProgram&) const;
};

struct PrimaryExpFunc : public PrimaryExp {
    //primary_exp ::= id
    DeclFunc* decl_func;
    std::string name;
	PrimaryExpFunc(DeclFunc*, const std::string&);
	ExprNodeP CreateCopy() const;
    PrimaryExpClass GetPrimaryExpClass() const {
        return PRIMARY_EXP_CLASS_FUNC; }
    void Print(int, std::ostream&) const;
	void Generate(AsmProgram&) const;
	AsmSegT GenerateAddr(AsmProgram&) const;
};

struct PrimaryExpIntConst : public PrimaryExp {
    //primary_exp ::= int_const
    int const_value;
    PrimaryExpIntConst(int);
	ExprNodeP CreateCopy() const;
    PrimaryExpClass GetPrimaryExpClass() const {
        return PRIMARY_EXP_CLASS_INT_CONST; }
    void Print(int, std::ostream&) const;
	void Generate(AsmProgram&) const;
	AsmSegT GenerateAddr(AsmProgram&) const;
};

struct PrimaryExpRealConst : public PrimaryExp {
    //primary_exp ::= real_const
    double const_value;
    PrimaryExpRealConst(double);
	ExprNodeP CreateCopy() const;
    PrimaryExpClass GetPrimaryExpClass() const {
        return PRIMARY_EXP_CLASS_REAL_CONST; }
    void Print(int, std::ostream&) const;
	void Generate(AsmProgram&) const;
	AsmSegT GenerateAddr(AsmProgram&) const;
};

struct PrimaryExpStringConst : public PrimaryExp {
    //primary_exp ::= string_const
    std::string const_value;
    PrimaryExpStringConst(std::string);
	ExprNodeP CreateCopy() const;
    PrimaryExpClass GetPrimaryExpClass() const {
        return PRIMARY_EXP_CLASS_STRING_CONST; }
    void Print(int, std::ostream&) const;
	void Generate(AsmProgram&) const;
	AsmSegT GenerateAddr(AsmProgram&) const;
};

void GenerateExp(ExprNode*, AsmProgram&);

#endif // EXP_H_INCLUDED
