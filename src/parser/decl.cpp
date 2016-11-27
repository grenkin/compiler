#include "decl.h"
#include "..\errors\errors.h"

StructDecl* SymTableStruct::FindStructDecl(const std::string& id)
{
	MapP<StructDecl*>::iterator i = scope.find(id);
	if (i != scope.end())
		return i->second;
	else
		return 0;
}

DeclVar::DeclVar(ExprType& type, StorageClass storage_class,
	DeclVarClass decl_var_class)
	: type(type), storage_class(storage_class), decl_var_class(decl_var_class)
{
}

DeclTypedefName::DeclTypedefName(ExprType& type)
	: type(type)
{
}

DeclEnumConst::DeclEnumConst(int value)
	: value(value)
{
}

DeclTypeStruct::DeclTypeStruct()
	: incomplete(true), opened(false), struct_size(0)
{
}

StructDecl::StructDecl(ExprType& type, int offset)
	: type(type), offset(offset)
{
}

void SymTablesStack::PushSymTableBlock(SymTableBlock& sym_table)
{
	stack_block.push_back(&sym_table);
}

void SymTablesStack::PopSymTableBlock()
{
	stack_block.pop_back();
}

void SymTablesStack::PushSymTableStruct(SymTableStruct& sym_table)
{
	stack_struct.push_back(&sym_table);
}

void SymTablesStack::PopSymTableStruct()
{
	stack_struct.pop_back();
}

Decl1* SymTablesStack::FindDecl1(const std::string& id)
{
	for (std::vector<SymTableBlock*>::reverse_iterator j = stack_block.rbegin();
		j != stack_block.rend(); ++j)
	{
		MapP<Decl1*>& scope = (*j)->scope1;
		MapP<Decl1*>::iterator i = scope.find(id);
		if (i != scope.end())
			return i->second;
	}
	return 0;
}

Decl2* SymTablesStack::FindDecl2(const std::string& id,
	bool* current_sym_table = 0)
//≈сли объ¤вление найдено в текущей таблице символов,
//то переменной current_sym_table присваиваетс¤ true,
//в противном случае -- false.
{
	if (current_sym_table)
		*current_sym_table = false;
	bool flag = false;
	for (std::vector<SymTableBlock*>::reverse_iterator j =
		stack_block.rbegin(); j != stack_block.rend(); ++j)
	{
		MapP<Decl2*>& scope = (*j)->scope2;
		MapP<Decl2*>::iterator i = scope.find(id);
		if (i != scope.end()) {
			if (!flag) { //объ¤вление найдено в текущей таблице символов
				if (current_sym_table)
					*current_sym_table = true;
			}
			return i->second;
		}
		flag = true;
	}
	return 0;
}

StructDecl* SymTablesStack::FindStructDecl(const std::string& id)
{
	return stack_struct.back()->FindStructDecl(id);
}

void SymTablesStack::InsertDecl1(const std::string& id,
	std::auto_ptr<Decl1>& decl1)
{
	MapP<Decl1*>& scope = stack_block.back()->scope1;
	try {
		scope.Insert(id, decl1);
	}
	catch (MapPKeyExists) {
		throw IdRedeclarationError();
	}
}

void SymTablesStack::InsertDecl2(
	const std::string& id, std::auto_ptr<Decl2>& decl2)
{
	MapP<Decl2*>& scope = stack_block.back()->scope2;
	try {
		scope.Insert(id, decl2);
	}
	catch (MapPKeyExists) {
		throw IdRedeclarationError();
	}
}

void SymTablesStack::InsertDecl2(std::auto_ptr<Decl2>& decl2)
{
	stack_block.back()->anonymous.PushBack(decl2);
}

void SymTablesStack::InsertStructDecl(
	const std::string& id, std::auto_ptr<StructDecl>& struct_decl)
{
	MapP<StructDecl*>& scope = stack_struct.back()->scope;
	try {
		scope.Insert(id, struct_decl);
	}
	catch (MapPKeyExists) {
		throw IdRedeclarationError();
	}
}
