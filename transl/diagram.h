// Класс синтаксических диаграмм

#include "scaner.h"
#include "treeSemant.h"
#include <string>
#include <list>

#ifndef __DIAGRAM
#define __DIAGRAM

using namespace std;

class TDiagram
{
private:
	TScaner *sc;
public:
	list <string>* triads;
	Tree *tr;
	Tree *pt;
	Tree * pr;
	bool FlInt;
	TDiagram(void) {pt = tr = new Tree(sc);}
	TDiagram(TScaner * s) {sc=s;pt = tr = new Tree(sc); triads = new list<string>();}
	~TDiagram(){}
	void Progr(); // программа
	void GlavProgr(); // главная программа
	void Block(); // блок
	void BodyBlock(); // тело блока
	void Operat(); // оператор
	//void Operats(); // ператоры
	void OpisPerem(); // описание переменных
	void Spisok(DataType ); // список
	void Perem(DataType ); // переменная
	string Vyrazh(); // выражение
	string Slagaem(); // слагаемое
	string Mnozhit(); // множитель
	string ElemVyrazh(); // элементарное выражение
	void Func(); // функция
	void BodyFunc();
	int SpisokFormPerem(); // список формальных переменных
	/*TData * */ void Prisvaiv(); // присваивание
	void VyzovFunc(); // вызов функции
	int SpisokFactPerem(char []); // список фактических переменных
	void Switch_(); // switch
	void Case_(); // case
	void TipDan(); // тип данных

	void setElemTriads(int numb, string znach)
	{
	int i = 1;

	for (list<string>::iterator it = triads -> begin(); it != triads -> end(); it++)
		if( i++ == numb)
		{
			*it = znach;
		}
	}
};
#endif