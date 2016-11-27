#ifndef DECL_H_INCLUDED
#define DECL_H_INCLUDED

#include "expr_type.h"
#include "..\misc\smart_ptrs.h"

enum StorageClass {
	STOR_CL_NONE,
	STOR_CL_STATIC
};

enum StorageClassSpec {
	STORAGE_CLASS_SPEC_NONE,
	STORAGE_CLASS_SPEC_STATIC,
	STORAGE_CLASS_SPEC_TYPEDEF
};

struct Decl1;
struct Decl2;
struct StructDecl;

struct SymTableBlock {
	MapP<Decl1*> scope1;
	MapP<Decl2*> scope2;
	ListP<Decl2*> anonymous;
	void Print(int, std::ostream&) const;
};

struct SymTableStruct {
	MapP<StructDecl*> scope;
	void Print(int, std::ostream&) const;
	StructDecl* FindStructDecl(const std::string&);
};

enum Decl1Class {
	DECL1_CLASS_VAR,
	DECL1_CLASS_TYPEDEF_NAME,
	DECL1_CLASS_ENUM_CONST,
	DECL1_CLASS_FUNC
};

struct Decl1 {
	virtual ~Decl1() {}
	virtual Decl1Class GetDecl1Class() const = 0;
	virtual void Print(const std::string&, int, std::ostream&) const = 0;
};

enum DeclVarClass {
	DECL_VAR_CLASS_GLOBAL,
	DECL_VAR_CLASS_LOCAL,
	DECL_VAR_CLASS_PARAM
};

struct DeclVar : public Decl1 {
	ExprType type;
	StorageClass storage_class;
	DeclVarClass decl_var_class;
	DeclVar(ExprType&, StorageClass, DeclVarClass);
	Decl1Class GetDecl1Class() const { return DECL1_CLASS_VAR; }
	void Print(const std::string&, int, std::ostream&) const;
};

struct DeclTypedefName : public Decl1 {
	ExprType type;
	DeclTypedefName(ExprType&);
	Decl1Class GetDecl1Class() const { return DECL1_CLASS_TYPEDEF_NAME; }
	void Print(const std::string&, int, std::ostream&) const;
};

struct DeclEnumConst : public Decl1 {
	int value;
	DeclEnumConst(int);
	Decl1Class GetDecl1Class() const { return DECL1_CLASS_ENUM_CONST; }
	void Print(const std::string&, int, std::ostream&) const;
};

enum Decl2Class {
	DECL2_CLASS_STRUCT,
	DECL2_CLASS_ENUM
};

struct Decl2 {
	virtual ~Decl2() {}
	virtual Decl2Class GetDecl2Class() const = 0;
	virtual void Print(int, std::ostream&) const = 0;
};

struct DeclTypeStruct : public Decl2 {
	SymTableStruct sym_table;
	bool incomplete;
	bool opened;
	int struct_size;
	DeclTypeStruct();
	Decl2Class GetDecl2Class() const { return DECL2_CLASS_STRUCT; }
	void Print(int, std::ostream&) const;
};

struct DeclTypeEnum : public Decl2 {
	Decl2Class GetDecl2Class() const { return DECL2_CLASS_ENUM; }
	void Print(int, std::ostream&) const;
};

struct StructDecl {
	ExprType type;
	int offset;
	StructDecl(ExprType&, int);
	void Print(const std::string&, int, std::ostream&) const;
};

class SymTablesStack {
	std::vector<SymTableBlock*> stack_block;
	std::vector<SymTableStruct*> stack_struct;
public:
	void PushSymTableBlock(SymTableBlock&);
	void PopSymTableBlock();
	void PushSymTableStruct(SymTableStruct&);
	void PopSymTableStruct();
	//ѕоиск: если объ¤вление не найдено, возвращаетс¤ 0
	Decl1* FindDecl1(const std::string&);
	Decl2* FindDecl2(const std::string&, bool*);
	StructDecl* FindStructDecl(const std::string&);
	//¬ставка: если объ¤вление с таким именем уже есть, генерируетс¤ исключение
	void InsertDecl1(const std::string&, std::auto_ptr<Decl1>&);
	void InsertDecl2(const std::string&, std::auto_ptr<Decl2>&);
	void InsertDecl2(std::auto_ptr<Decl2>&);
	void InsertStructDecl(const std::string&, std::auto_ptr<StructDecl>&);
};

#endif // DECL_H_INCLUDED
