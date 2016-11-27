#ifndef STAT_H_INCLUDED
#define STAT_H_INCLUDED

#include "exp.h"
#include "decl.h"
#include "..\generator\asm_program.h"

struct Stat {
	//stat ::= exp_stat |
	//         compound_stat |
	//         selection_stat |
	//         iteration_stat |
	//         jump_stat
	virtual ~Stat() {}
	virtual void Print(int, std::ostream&) const = 0;
	virtual void Generate(AsmProgram&) const = 0;
};

typedef std::auto_ptr<Stat> StatP;
typedef ListP<Stat*> StatList;

struct ExpStat : public Stat {
	//exp_stat ::= exp ';' |
	//                 ';'
	ExprNodeP exp; //может быть 0
	void Print(int, std::ostream&) const;
	void Generate(AsmProgram&) const;
};

struct CompoundStat : public Stat {
	//compound_stat ::= '{' decl_list stat_list '}' |
	//                  '{'           stat_list '}' |
	//                  '{' decl_list           '}' |
	//                  '{'                     '}'
	SymTableBlock sym_table;
	StatList stat_list;
	void Print(int, std::ostream&) const;
	void Generate(AsmProgram&) const;
	void Generate(bool, AsmProgram&) const;
};

typedef std::auto_ptr<CompoundStat> CompoundStatP;

struct SelectionStat : public Stat {
	//selection_stat ::= 'if' '(' exp ')' stat |
	//                   'if' '(' exp ')' stat 'else' stat
	ExprNodeP exp;
	StatP stat1;
	StatP stat2; //может быть 0
	void Print(int, std::ostream&) const;
	void Generate(AsmProgram&) const;
};

struct IterationStatWhile : public Stat {
	//'while' '(' exp ')' stat
	ExprNodeP exp;
	StatP stat;
	void Print(int, std::ostream&) const;
	void Generate(AsmProgram&) const;
};

struct IterationStatDoWhile : public Stat {
	//'do' stat 'while' '(' exp ')' ';'
	StatP stat;
	ExprNodeP exp;
	void Print(int, std::ostream&) const;
	void Generate(AsmProgram&) const;
};

struct IterationStatFor : public Stat {
	//'for' '(' exp ';' exp ';' exp ')' stat |
	//'for' '(' exp ';' exp ';'     ')' stat |
	//'for' '(' exp ';'     ';' exp ')' stat |
	//'for' '(' exp ';'     ';'     ')' stat |
	//'for' '('     ';' exp ';' exp ')' stat |
	//'for' '('     ';' exp ';'     ')' stat |
	//'for' '('     ';'     ';' exp ')' stat |
	//'for' '('     ';'     ';'     ')' stat
	ExprNodeP exp1; //может быть 0
	ExprNodeP exp2; //может быть 0
	ExprNodeP exp3; //может быть 0
	StatP stat;
	void Print(int, std::ostream&) const;
	void Generate(AsmProgram&) const;
};

struct JumpStatContinue : public Stat {
	//'continue' ';'
	void Print(int, std::ostream&) const;
	void Generate(AsmProgram&) const;
};

struct JumpStatBreak : public Stat {
	//'break' ';'
	void Print(int, std::ostream&) const;
	void Generate(AsmProgram&) const;
};

struct JumpStatReturn : public Stat {
	//'return' exp ';' |
	//'return'     ';'
	ExprNodeP exp; //может быть 0
	void Print(int, std::ostream&) const;
	void Generate(AsmProgram&) const;
};

#endif // STAT_H_INCLUDED
