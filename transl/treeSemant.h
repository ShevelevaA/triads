#ifndef __SEMAN
#define __SEMAN
#include "defs.h"
#include "Scaner.h"
#include <stdio.h>
#include <string.h>

using namespace std;

enum TYPE
{
	Type_INT = 1,
	Type_UNSIGN = 2,
	Type_FUNC = 3,
	Type_INTorUnsign,
	Type_ConstChar,
	Type_ID,
	Type_UNKNOWN
};


enum ArifmeticOperation
{
	add = 1,
    substract,
    multy,
    divide,
    percent
};

enum ConditionOperation
{
	Less = 6,	//	<
	eqLess,		//	<=
	More,		//	>
	eqMore,		//	>=
	eqeq,		//	==
	neq			//	!=
};

enum DataType
{
	type_unknown = 1,
	type_int,
	type_double,
	type_char,
	type_void
};

union DataValue
{
	int isInt;
	double isDouble;
	char isChar;
	//string ;
};

struct TData
{
	DataType dataType;
	DataValue dataValue;

	TData()
	{
		dataType = type_unknown;
		dataValue.isInt = NULL;		
		dataValue.isDouble = NULL;		
		dataValue.isChar = NULL;
	}
};


struct Node
{
	char id[MAX_LEX];	// идентификатор
	DataType type;			// название типа
	DataValue dataValue;	// значение
	bool is_type;		// признак типа
	bool is_func;		//признак функции
	int param;			//кол-во парар-ров
	int position;

	Node(){
		id[0]='=';
		id[1]='=';
		id[2]='=';
		id[3]='\0';
		//type[0]='\0';
	}
	Node(char *i){
		strcpy_s(id,i);
//		type[0]='\0';
		is_func = false;
	}
	Node(char *i, DataType t){
		strcpy_s(id, i);
		type = t;
		is_func = false;
	}
	Node(char *i, DataType t, bool typ_f){
		strcpy_s(id, i);
		type = t;
		is_func = typ_f;
	}

	Node(char *i, DataType t, int p, bool typ_f){
		strcpy_s(id, i);
		type = t;
		is_func = typ_f;
		param = p;
	}
};


struct TVal{
	int datAsInt;
	double datAsDouble;
	TVal(){}
};

class Tree
{
public:
	Node *n;
	Tree *Up, *Left, *Right;
	TScaner * scaner;
public:
	Tree(TScaner * s);
	Tree(TScaner * s, Tree *u, Tree *l, Tree *r, Node *data);
	void Tree::setScan(TScaner *sc);
	void set_Left(Node *data);
	void set_Right(Node *data);
	Tree * find_Up(char *id);
	Tree * find_Right_Left(char *id);
	bool sosed(char *id);
	void print(void);

	bool sem_get_type(char *id);
	bool sem_override(char *id);
	bool sem_check_func(char *id);
	Tree * sem_var_declared(char *id);

	Tree *sem_add_var(char *id, DataType type);
	Tree *sem_add_func(char *id, DataType type);
	void SemControlParam(char *id, int n);
	void SemSetParam(char * id, int n);

	bool prived(char * type1, char * type2);

	TData * performOperation(TData * op1, TData * op2, ArifmeticOperation arOp);
	TData * performCondition(TData * op1, TData * op2, ConditionOperation conOp);

	void string_type(Node * n);
	Tree * sem_copy_tree_of_func(char *id);
	Tree * sem_get_first_perem_of_func(char *id);

	~Tree(void);	
};
#endif
