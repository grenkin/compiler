#ifndef EXPR_TYPE_H_INCLUDED
#define EXPR_TYPE_H_INCLUDED

#include <vector>
#include "..\lexer\lexer_types.h"
#include "..\misc\smart_ptrs.h"

enum BaseTypeT {
	BASE_TYPE_VOID,
	BASE_TYPE_CHAR,
	BASE_TYPE_INT,
	BASE_TYPE_FLOAT
};

const int BASE_TYPES_NUMBER = 4;
const IdentifierOrKeywordT BASE_TYPES_KEYWORDS[BASE_TYPES_NUMBER] = {
	IDENT_OR_KEYWORD_VOID, IDENT_OR_KEYWORD_CHAR,
	IDENT_OR_KEYWORD_INT, IDENT_OR_KEYWORD_FLOAT
};

enum TypeQualifiers {
	TYPE_QUAL_NONE,
	TYPE_QUAL_CONST
};

enum TypeSpecClass {
	TYPE_SPEC_CLASS_BASE,
	TYPE_SPEC_CLASS_STRUCT,
	TYPE_SPEC_CLASS_ENUM
};

struct ExprNode;
typedef std::auto_ptr<ExprNode> ExprNodeP;
struct TypeSpec;
struct AbstractDeclaratorElem;
struct DeclTypeStruct;
struct DeclTypeEnum;

typedef ListP<AbstractDeclaratorElem*> AbstractDeclarator;

struct ExprType {
	std::auto_ptr<TypeSpec> type_spec;
	TypeQualifiers type_qualifiers;
	AbstractDeclarator abstract_declarator;
	ExprType();
	ExprType CreateCopy() const;
	void AddAbstractDeclarator(AbstractDeclarator&); //деструктивное копирование
	bool CheckAbstractDeclaratorCorrectness() const;
	int GetSize() const;
	void Print(const std::string&, int, std::ostream&) const;
	bool operator==(const ExprType&) const;
	bool Incomplete() const;
	bool IsVoid() const;
	bool IsPointer() const;
	bool IsArray() const;
	bool IsFunc() const;
	bool IsIntegral() const;
	bool IsFloat() const;
	bool IsArithmetic() const;
	bool IsStruct() const;
	ExprType GetPointerType() const;
	void SetInt();
	void SetFloat();
	void SetVoid();
	void SetChar();
	void MakePointer();
	void PointerGeneration();
};

struct TypeSpec {
	virtual ~TypeSpec() {}
	virtual TypeSpecClass GetTypeSpecClass() const = 0;
	virtual std::auto_ptr<TypeSpec> CreateCopy() const = 0;
	virtual void Print(int, std::ostream&) const = 0;
};

struct BaseTypeSpec : public TypeSpec {
	BaseTypeT base_type;
	BaseTypeSpec(BaseTypeT);
	TypeSpecClass GetTypeSpecClass() const { return TYPE_SPEC_CLASS_BASE; }
	std::auto_ptr<TypeSpec> CreateCopy() const;
	void Print(int, std::ostream&) const;
};

struct StructSpec : public TypeSpec {
public:
	DeclTypeStruct* decl_type_struct;
	StructSpec(DeclTypeStruct*);
	TypeSpecClass GetTypeSpecClass() const { return TYPE_SPEC_CLASS_STRUCT; }
	std::auto_ptr<TypeSpec> CreateCopy() const;
	void Print(int, std::ostream&) const;
};

class EnumSpec : public TypeSpec {
public:
	DeclTypeEnum* decl_type_enum;
	EnumSpec(DeclTypeEnum*);
	TypeSpecClass GetTypeSpecClass() const { return TYPE_SPEC_CLASS_ENUM; }
	std::auto_ptr<TypeSpec> CreateCopy() const;
	void Print(int, std::ostream&) const;
};

enum AbstractDeclaratorElemClass {
	ABSTRACT_DECLARATOR_ELEM_CLASS_POINTER,
	ABSTRACT_DECLARATOR_ELEM_CLASS_ARRAY,
	ABSTRACT_DECLARATOR_ELEM_CLASS_FUNC
};

struct AbstractDeclaratorElem {
	virtual ~AbstractDeclaratorElem() {}
	virtual AbstractDeclaratorElemClass
		GetAbstractDeclaratorElemClass() const = 0;
	virtual std::auto_ptr<AbstractDeclaratorElem> CreateCopy() const = 0;
	virtual void Print(int, std::ostream&) const = 0;
};

struct AbstractDeclaratorElemPointer : public AbstractDeclaratorElem {
	TypeQualifiers type_qualifiers;
	AbstractDeclaratorElemPointer(TypeQualifiers);
	AbstractDeclaratorElemClass GetAbstractDeclaratorElemClass() const {
		return ABSTRACT_DECLARATOR_ELEM_CLASS_POINTER; }
	std::auto_ptr<AbstractDeclaratorElem> CreateCopy() const;
	void Print(int, std::ostream&) const;
};

struct AbstractDeclaratorElemArray : public AbstractDeclaratorElem {
	//если const_exp отсутствует, то const_exp_value == 0,
	//иначе const_exp_value > 0
	int const_exp_value;
	AbstractDeclaratorElemArray(int);
	AbstractDeclaratorElemClass GetAbstractDeclaratorElemClass() const {
		return ABSTRACT_DECLARATOR_ELEM_CLASS_ARRAY; }
	std::auto_ptr<AbstractDeclaratorElem> CreateCopy() const;
	void Print(int, std::ostream&) const;
};

struct ParamDecl {
	ExprType type;
	std::string name; //если имя параметра отсутствует, то name == ""
	ParamDecl(ExprType&, const std::string& = "");
	std::auto_ptr<ParamDecl> CreateCopy() const;
	void Print(int, std::ostream&) const;
};

typedef ListP<ParamDecl*> ParamList;

struct AbstractDeclaratorElemFunc : public AbstractDeclaratorElem {
	ParamList param_list;
	AbstractDeclaratorElemFunc(ParamList&);
	AbstractDeclaratorElemClass GetAbstractDeclaratorElemClass() const {
		return ABSTRACT_DECLARATOR_ELEM_CLASS_FUNC; }
	std::auto_ptr<AbstractDeclaratorElem> CreateCopy() const;
	void Print(int, std::ostream&) const;
};

void AddPointer(AbstractDeclarator&, std::vector<TypeQualifiers>&);
void AddDeclaratorSuffix(AbstractDeclarator&, AbstractDeclarator&); //деструктивное копирование
bool CompareParamLists(ParamList&, ParamList&);
void PrintParamList(const ParamList&, int, std::ostream&);
void PrintDeclarator(
	const AbstractDeclarator&, const std::string&, int, std::ostream&);

#endif // EXPR_TYPE_H_INCLUDED
