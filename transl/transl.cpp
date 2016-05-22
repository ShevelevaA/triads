// transl.cpp: определяет точку входа для консольного приложения.
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
	// ввести файл с исходным модулем:
	if (argc<=1) sc = new TScaner("input.txt");// файл по умолчанию
	else sc = new TScaner(""); // задан файл
	TDiagram *dg = new TDiagram(sc);
	dg->Progr();
	int type; TypeLex l;
	type=sc->Scaner(l);
	/*if (type==Type_End) printf("—интаксических ошибок не обнаружено. \n");

	else sc->PrintError("Ћишний текст в конце программы.","");

	cout<<"\tLерево:"<<endl<<endl;
	dg -> tr -> print();
	*/

	/*cout << "Список: ";
	copy( dg->triads -> begin(),dg -> triads -> end(), ostream_iterator<string>(cout," "));

	*/
	int i =0;

	cout << "Триады:" << endl;;
	
	for (list<string>::iterator it = dg -> triads -> begin(); it != dg -> triads -> end(); it++)
		cout << ++i << ") " << *it << endl;

	system("pause");
	return 0;
}

