#include "StdAfx.h"
#include "treeSemant.h"
#include "Scaner.h"
#include "defs.h"
#include <iostream>
#include <fstream>
#include <string.h>
#define max(a,b) a<b? b : a
using namespace std;

Tree::Tree(TScaner * s)
{
	n = new Node();
	Up = NULL;
	Left = NULL;
	Right = NULL;
	scaner = s;
}

bool Tree::prived(char * type1, char * type2){
	if(strcmp(type2,"double"))
		return true;
	else
		return false;
}

Tree::Tree(TScaner * s, Tree *u, Tree *l, Tree *r, Node *data)
{
	n = data;
	Up = u;
	Left = l;
	Right = r;
	memcpy(n, data, sizeof(Node));	
	scaner = s;
}

void Tree::setScan(TScaner *sc)
{
	this -> scaner = sc;
}

void Tree::set_Left(Node *data)
{
	Tree *a = new Tree(scaner,this,NULL,NULL,data);
	Left = a;
}

void Tree::set_Right(Node *data)
{
	Tree *a = new Tree(scaner,this,NULL,NULL,data);
	Right = a;
}

Tree *Tree::find_Up(char *id)
{
	Tree *i = this;
	while (i != NULL){
		if (strcmp(i -> n-> id, id) == 0) break;
		i = i -> Up;
	}
	return i;
}

Tree *Tree::find_Right_Left(char *id)
{
	Tree *i = Right;
	while (i != NULL){
		if (strcmp(i->n->id, id) == 0) break;
		i = i->Left;
	}
	return i;
}

bool Tree::sosed(char *id)
{
	Tree *i = this;
	while (i != NULL){
		if (strcmp(i -> n -> id, id) == 0) return true;
		if (i -> Up != NULL && i -> Up -> Left == i) i = i -> Up;
		else break;
	}
	return false;
}

void Tree::print(void)
{
	/*
	cout << "Вершина с данными: " << n -> id << " (" << n -> type << ")" << endl;
	if (Left != NULL)
		cout << "\tслева данные: " << Left -> n -> id << " (" << Left -> n -> type << ")";
	if (Right != NULL)
		cout << "\tсправа данные: " << Right -> n -> id << " (" << Right -> n -> type << ")";
	cout << endl << endl;
	if (Left != NULL)
		Left -> print();
	if (Right != NULL)
		Right -> print(); 
		*/
	cout << "Вершина с данными: ";
	string_type(n);
	cout << endl;
	if (Left != NULL)
	{
		cout << "\tслева данные: ";
		string_type(Left -> n);
	}
	if (Right != NULL)
	{
		cout << "\tсправа данные: ";
		string_type(Right -> n);
	}
	cout << endl << endl;
	if (Left != NULL)
		Left -> print();
	if (Right != NULL)
		Right -> print(); 
}

void Tree::string_type(Node * n)
{
	char * v = new char;
	DataType type = n -> type;
	if (type_int == type)
	{
		cout << n -> id << " (int, " << n -> dataValue.isInt << ")";
	}
	else if (type_double == type)
	{
		cout << n -> id << " (double, " << n -> dataValue.isDouble << ")";
	}
	/*else if (type_char == type)
	{
		itoa(n -> dataValue.isChar, v, 10);	
	}*/
	else 
		cout << n -> id;
}

bool Tree::sem_check_func(char *id)
{
	Tree * tr = find_Up(id);
	if (tr -> n -> is_func)
		return true;
	else 
		return false;
}

bool Tree::sem_get_type(char *id)
{
	Tree *fnUp = NULL;
	fnUp = this -> find_Up(id);
	if (fnUp == NULL){
		this -> scaner -> PrintError("Идентификатор не объявлен -", id);
		return false;
	}else if (fnUp -> n -> is_func == false){
		this -> scaner -> PrintError("Не является функцией!", id);
		return false;
	}
	return true;
}

bool Tree::sem_override(char *id)
{
	if (this -> sosed(id)){
		this -> scaner -> PrintError("Переопределение!", id);
		return true;
	}
	return false;
}

Tree * Tree::sem_var_declared(char *id)
{
	Tree *fnUp = this -> find_Up(id);
	if (fnUp == NULL)
	{
		this -> scaner -> PrintError("Идентификатор не объявлен - ", id);
	}
		return fnUp;
}

Tree *Tree::sem_add_var(char *id, DataType type)
{
	Tree *fnUp = NULL;
	if ((type != type_int) && (type != type_double)){
		fnUp = this->find_Up(id);
		if (fnUp != NULL) type = fnUp->n->type;
	}
	set_Left(new Node(id,type));
	return Left;
}

void Tree::SemControlParam(char *id, int num)
{
	Tree *fnup = this -> find_Up(id);
	if (num != fnup -> n -> param)
		this -> scaner -> PrintError("Количество параметров не совпадает", id);
}

void Tree::SemSetParam(char * id, int num)
{
	Tree *fnup = this -> find_Up(id);
	fnup -> n -> param = num;
}



TData * Tree::performOperation(TData * op1, TData * op2, ArifmeticOperation arOp)
{
	TData * result = new TData();
	if (op1 -> dataType == type_double) 
	{
		double value1 = op1 -> dataValue.isDouble, value2;
		if (op2 ->dataType == type_int)
			value2 = op2 -> dataValue.isInt;
		else
		value2 = op2 -> dataValue.isDouble;
		switch (arOp) 
		{
		case add:
			value1 += value2;
			break;
		case divide:
			value1 /= value2;
			break;
		case multy:
			value1 *= value2;
			break;
		/*case percent:
			value1 %= value2;
			break;*/
		case substract:
			value1 -= value2;
			break;
		default:
			break;
		}
		result -> dataType = type_double;
		result -> dataValue.isDouble = value1;
	} 
	else
	{	
			if (op2 -> dataType == type_double) 
			{
			//this -> scaner -> PrintError("Несовместимость типов: double не может быть приведен к int!", scaner -> uk);
			op2 -> dataValue.isInt = op2 -> dataValue.isDouble;
			} 
			if (op1 -> dataValue.isInt == NULL) 
			{
				this -> scaner -> PrintError("Первая переменная не инициализирована!", scaner -> uk);				
				return NULL;
			}
			if (op2 -> dataValue.isInt == NULL) 
			{
				this -> scaner -> PrintError("Вторая переменная не инициализирована!", scaner -> uk);
				return NULL;
			}
			int value1 = op1 -> dataValue.isInt;
			int value2 = op2 -> dataValue.isInt;
			switch (arOp)
			{
			case add:
				value1 += value2;
				break;
			case divide:
				value1 /= value2;
				break;
			case multy:
				value1 *= value2;
				break;
			case percent:
				value1 %= value2;
				break;
			case substract:
				value1 -= value2;
				break;
			default:
				break;
			}
			result -> dataType = type_int;
			result -> dataValue.isInt = value1;
			//result -> dataValue.isDouble = value1;		
	}
	return result;
}

TData * Tree::performCondition(TData * op1, TData * op2, ConditionOperation conOp)
{
	TData * result = new TData();
	int is = 0;
	if (op1 -> dataType == type_double) 
	{
		double value1 = op1 -> dataValue.isDouble;
		double value2 = op2 -> dataValue.isDouble;
		switch (conOp) 
		{
		case Less:
			if (value1 < value2)
				is = 1;
			break;
		case eqLess:
			if (value1 <= value2)
				is = 1;
			break;
		case More:
			if (value1 > value2)
				is = 1;
			break;
		case eqMore:
			if (value1 >= value2)
				is = 1;
			break;
		case eqeq:
			if (value1 == value2)
				is = 1;
			break;
		case neq:
			if (value1 != value2)
				is = 1;
			break;
		default:
			is = 0;
			break;
		}
		result -> dataType = type_int;
		result -> dataValue.isInt = is;
	} 
	else
	{
		if (op2 -> dataType == type_double) 
		{
			this -> scaner -> PrintError("Несовместимость типов: double не может быть приведен к int!", scaner -> uk);
		} 
		else 
		{
			if (op1 -> dataValue.isInt == NULL) 
			{
				this -> scaner -> PrintError("Первая переменная не инициализирована!", scaner -> uk);
				if (op2 -> dataValue.isInt == NULL) 
				{
					this -> scaner -> PrintError("Вторая переменная не инициализирована!", scaner -> uk);
				}
				return NULL;
			}
			int value1 = op1 -> dataValue.isInt;
			int value2 = op2 -> dataValue.isInt;
			switch (conOp) 
		{
		case Less:
			if (value1 < value2)
				is = 1;
			break;
		case eqLess:
			if (value1 <= value2)
				is = 1;
			break;
		case More:
			if (value1 > value2)
				is = 1;
			break;
		case eqMore:
			if (value1 >= value2)
				is = 1;
			break;
		case eqeq:
			if (value1 == value2)
				is = 1;
			break;
		case neq:
			if (value1 != value2)
				is = 1;
			break;
		default:
			is = 0;
			break;
		}
		result -> dataType = type_int;
		result -> dataValue.isInt = is;
		}
	}
	return result;
}


Tree * Tree::sem_copy_tree_of_func(char *id)
{
	Tree * fnUp = this -> find_Up(id);
	if (fnUp -> n -> is_func)
	{
		fnUp = fnUp -> Right;
		do{
			fnUp = fnUp -> Left;
		}while(!fnUp -> Right);
		//fnUp = (((((fnUp -> Right) -> Left) -> Left) -> Left) -> Right);
		fnUp = fnUp -> Right;
		return fnUp;
	}
	else
		this -> scaner -> PrintError("Это не функция!", scaner -> uk);
}

Tree * Tree::sem_get_first_perem_of_func(char *id)
{
	Tree * fnUp = this -> find_Up(id);
	if (fnUp -> n -> is_func)
	{
		fnUp = ((fnUp -> Right));
		return fnUp;
	}
	else
		this -> scaner -> PrintError("Это не функция!", scaner -> uk);
}



Tree::~Tree(void){}