#ifndef TR_UNIT_H_INCLUDED
#define TR_UNIT_H_INCLUDED

#include "stat.h"
#include "..\generator\asm_program.h"

struct TranslationUnit;

struct FunctionDefinition {
	//function_definition ::= spec_qualifier_list declarator compound_stat
	ExprType result_type;
	ParamList param_list;
	CompoundStatP compound_stat;
	std::string name;
	FunctionDefinition(const std::string& name) : name(name) {}
	void Print(int, std::ostream&);
	void Generate(AsmProgram&) const;
};

struct DeclFunc : public Decl1 {
	FunctionDefinition* func_def;
	DeclFunc(FunctionDefinition*);
	Decl1Class GetDecl1Class() const { return DECL1_CLASS_FUNC; }
	void Print(const std::string&, int, std::ostream&) const {}
};

struct GlobalSymTable : public SymTableBlock {
	FunctionDefinition* InsertDeclFunc(const std::string&, ExprType,
		ParamList, TranslationUnit&);
};

struct TranslationUnit {
	//translation_unit ::= external_decl |
	//                     translation_unit external_decl
	//external_decl ::= function_definition |
	//                  decl
	MapP<FunctionDefinition*> func_def;
	GlobalSymTable global_sym_table;
	void Print(int, std::ostream&) const;
	void Generate(AsmProgram&) const;
};

#endif // TR_UNIT_H_INCLUDED
