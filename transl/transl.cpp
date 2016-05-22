// transl.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"

#include <stdio.h>
#include <string.h>

#include "defs.h"
#include "Scaner.h"
#include "diagram.h"

#include <fstream>
#include <iostream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");

	TScaner * sc ;
	// ������ ���� � �������� �������:
	if (argc<=1) sc = new TScaner("input.txt");// ���� �� ���������
	else sc = new TScaner(""); // ����� ����
	TDiagram *dg = new TDiagram(sc);
	dg->Progr();
	int type; TypeLex l;
	type=sc->Scaner(l);
	/*if (type==Type_End) printf("�������������� ������ �� ����������. \n");

	else sc->PrintError("������ ����� � ����� ���������.","");

	cout<<"\tL�����:"<<endl<<endl;
	dg -> tr -> print();
	*/

	/*cout << "������: ";
	copy( dg->triads -> begin(),dg -> triads -> end(), ostream_iterator<string>(cout," "));

	*/
	int i =0;

	cout << "������:" << endl;;
	
	for (list<string>::iterator it = dg -> triads -> begin(); it != dg -> triads -> end(); it++)
		cout << ++i << ") " << *it << endl;

	system("pause");
	return 0;
}

