// ����� �������������� ��������

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
	void Progr(); // ���������
	void GlavProgr(); // ������� ���������
	void Block(); // ����
	void BodyBlock(); // ���� �����
	void Operat(); // ��������
	//void Operats(); // ��������
	void OpisPerem(); // �������� ����������
	void Spisok(DataType ); // ������
	void Perem(DataType ); // ����������
	string Vyrazh(); // ���������
	string Slagaem(); // ���������
	string Mnozhit(); // ���������
	string ElemVyrazh(); // ������������ ���������
	void Func(); // �������
	void BodyFunc();
	int SpisokFormPerem(); // ������ ���������� ����������
	/*TData * */ void Prisvaiv(); // ������������
	void VyzovFunc(); // ����� �������
	int SpisokFactPerem(char []); // ������ ����������� ����������
	void Switch_(); // switch
	void Case_(); // case
	void TipDan(); // ��� ������

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