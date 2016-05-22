
#include "stdafx.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include "scaner.h"

int i_mas=0;
int mass_str[100];
int fl=0;
TScaner:: TScaner(char * FileName) {
	GetData(FileName);
	PutUK(0);
	stroka=1;
	simvol=0;
}

TypeLex Keyword[MAX_KEYW]={ "void", "int", "double", "switch", "case",
	"default", "break", "main" };

int IndexKeyword[MAX_KEYW]={Type_Void, Type_Int, Type_Double, Type_Switch,
	Type_Case, Type_Default, Type_Break, Type_Main};



void TScaner::PutUK(int i){ //восстановить указатель
	uk=i;
} 

int TScaner::GetUK(void){ // запомнить указатель
	return uk;
} 

void TScaner::PutSimvol(int i){ //восстановить указатель
	simvol=i;
} 

int TScaner::GetSimvol(void){ // запомнить указатель
	return simvol;
} 

void TScaner::PutStroka (int i){ //восстановить указатель
	stroka =i;
} 

int TScaner::GetStroka (void){ // запомнить указатель
	return stroka ;
} 



void TScaner::PrintError(char * err, char * a) {   // выдать сообщение об ошибке
	int str=i_mas;
	if(i_mas!=0)
		for(int j=0;j<i_mas;j++)
			if(mass_str[j]>uk){
						str=j+1;
							break;
					}
			
				

			
	if (a[0]=='\0')
		printf("Ошибка : %s %s строка %d  %d\n",err,a/*,stroka*/,str+1/*,simvol*/, uk);
	else
		printf("Ошибка : %s. Неверный символ %s строка %d  %d\n",err,a,/*stroka,*/str+1,/*simvol,*/ uk);
	system("pause");
	exit(0);
}


void TScaner::PrintError (char * err, int uk)
{
	for (int i = 0; ; i++)
	{
		if (uk < mass_str[i])
		{
			printf("Ошибка! \n \t", err, "\n");
			printf("\t Строка: ",i+1, "\n");
			system("pause");
			exit(1);		
		}
	}
}

int TScaner::Scaner(TypeLex l) {
	int i; // текущая длина лексемы
	for (i=0;i<MAX_LEX;i++) l[i]=0; //очистили поле лексемы
	i=0;                   // лексема заполняется с позиции i
   // stroka=1;
	//simvol=1;
start:                   // все игнорируемые элементы:
	while((t[uk]==' ') || (t[uk]=='\n') || (t[uk]=='\t')){
		//if (t[uk]==' '){
			//simvol++;
		//}
		//////////////////////
		if (t[uk]=='\n'){
			if(i_mas==0){
				mass_str[i_mas++]=uk;
			}
			else{
				for(int j=0;j<i_mas;j++)
					if(mass_str[j]==uk){
						fl=1;
							break;
					}
				if(!fl){
					mass_str[i_mas++]=uk;
				}
				fl=0;

			}

			stroka++;
			simvol=1;
		}
		/////////////////
		uk++;                // пропуск незначащих элементов
	}
	if ( (t[uk]=='/') && (t[uk+1]=='/') ){    // начался комментарий, надо пропустить текст до '\n'
		uk=uk+2;
		while ( (t[uk]!='\n')/*&&(t[uk]!='#')&& (t[uk]!='\0')*/) 
			uk++;
		///////////////////
		if (t[uk]=='\n'){

			if(i_mas==0){
				mass_str[i_mas++]=uk;
			}
			else{
				for(int j=0;j<i_mas;j++)
					if(mass_str[j]==uk){
						fl=1;
							break;
					}
				if(!fl){
					mass_str[i_mas++]=uk;
				}
				fl=0;

			}

		//stroka++;
			simvol=1;
		}
		//////////////////
		goto start;
	}


	int fl=0;
	if ( (t[uk]=='/') && (t[uk+1]=='*') ){    // начался комментарий, надо пропустить текст до '*/'
		uk=uk+2;
		while ( (t[uk]!='*')||(t[uk+1]!='/')) {
			if(t[uk]=='#'||t[uk]=='\0') {fl=1; break;}
			uk++;
		}
		
		if(fl){
			//uk--;
			
			PrintError("Неоконченный комментарий",l);
			return Type_Error;
		}
		else{ uk=uk+2;}

		goto start;
	}
	



	if (t[uk]=='\0') {
		l[0]='#'; 
		return Type_End;
	}

	int fl_ch_const=0;
	if ( (t[uk]<='9')&&(t[uk]>='0')){
		l[i++]=t[uk++];
		while ( (t[uk]<='9')&&(t[uk]>='0'))
			if (i<MAX_CH_CONST){
				l[i++]=t[uk++];
				simvol++;       ///////////////////////////
			}
			else { 
				fl_ch_const = 1;
				if (i<MAX_LEX-1){
					l[i++]=t[uk++]; 
					simvol++;       ///////////////////////////
				}
				else
					uk++;
			}
			
        if(!fl_ch_const){
		if (t[uk]=='.') {
			
			l[i++]=t[uk++];
			l[i-1] = ','; ////////////////////////////////////////////////////////////////////////////////////
			simvol++;       ///////////////////////////
			goto N1;
		}
		
		if( (t[uk]=='E')||(t[uk]=='e') ) { 
			l[i++]=t[uk++]; 
			simvol++;       ///////////////////////////
			goto N2; 
		}
		
		return Type_Const;
		}
		else{
			simvol=simvol-i+1;
			PrintError("Неверная числовая константа",l);
			return Type_Error;
		}
	}

	else if ( (t[uk]>='a') &&( t[uk]<='z') ||
		( t[uk]>='A') && (t[uk]<='Z') ){ // начинается идентификатор
			l[i++]=t[uk++];
			simvol++;       ///////////////////////////
			while ( (t[uk]<='9')&&(t[uk]>='0') ||
				(t[uk]>='a')&&(t[uk]<='z') ||
				(t[uk]>='A')&&(t[uk]<='Z') )
				if (i<MAX_LEX-1){
					l[i++]=t[uk++];
					simvol++;       ///////////////////////////
				}
				else uk++;  // длинный идентификатор обрезали
			
			int j; // проверка на ключевое слово:
			for (j=0; j<MAX_KEYW; j++)
				if (strcmp(l,Keyword[j])==0) return IndexKeyword[j];
			return Type_Id;
	}
	
	else if (t[uk]=='.'){
		l[i++]=t[uk++];
		simvol++;       ///////////////////////////
		if( (t[uk]<='9')&& (t[uk]>='0') ) { 
			l[i++]=t[uk++];
			simvol++;       ///////////////////////////
			goto N1;
		}
		simvol=simvol-i+1;
		PrintError("Неверная экспоненциальная константа",l);
		return Type_Error;
	}

	else if (t[uk]=='\'') { 
		uk++; // не будем включать кавычки  константу 
		if (t[uk+1]!='\'') { 
			while( (t[uk]!='\'')&& (t[uk]!='\n')&& (t[uk]!='\0') && (t[uk]!='#') ){ 
				if (i<MAX_LEX-1) {
					l[i++]=t[uk++];
					simvol++;       ///////////////////////////
				}
				else uk++;  // длинный идентификатор обрезали
			} 
			/////////////////////
			if (t[uk]=='\n'){
				if(i_mas==0){
				mass_str[i_mas++]=uk;
			}
			else{
				for(int j=0;j<i_mas;j++)
					if(mass_str[j]==uk){
						fl=1;
							break;
					}
				if(!fl){
					mass_str[i_mas++]=uk;
				}
				fl=0;

			}
				//stroka++;
				simvol=1;
			}
			///////////////////////

			if(t[uk]=='\'')
				uk++;
			simvol=simvol-i+1;
			PrintError("Неверная символьная константа",l); 
			//uk++; 
			return Type_Error; 
		} 
		else { 
			if (t[uk]!='\n'&&t[uk]!='\0'){
				l[i++]=t[uk++];
				uk++; // закрывающая кавычка
				return Type_Const_Simb;
			}
			else { 
				simvol=simvol-i+1;
				if(t[uk]=='\n'){

					if(i_mas==0){
				mass_str[i_mas++]=uk;
			}
			else{
				for(int j=0;j<i_mas;j++)
					if(mass_str[j]==uk){
						fl=1;
							break;
					}
				if(!fl){
					mass_str[i_mas++]=uk;
				}

			}

					simvol=1;
					//stroka++;
				}
				PrintError("Неверная символьная константа",l); 
				return Type_Error;
			}
		}
	}
	


	else if (t[uk]=='{'){
		l[i++]=t[uk++];
		simvol++;       ///////////////////////////
		return Type_Open_Blok;
	}
	else if (t[uk]=='}') {
		l[i++]=t[uk++]; 
		simvol++;       ///////////////////////////
		return Type_Close_Blok; 
	}

	else if (t[uk]=='('){
		l[i++]=t[uk++]; 
		simvol++;       ///////////////////////////
		return Type_Skobka_Op; 
	}
	else if (t[uk]==')'){
		l[i++]=t[uk++];
		simvol++;       ///////////////////////////
		return Type_Skobka_Cl;
	}

	else if (t[uk]==',') {
		l[i++]=t[uk++]; 
		simvol++;       ///////////////////////////
		return Type_Zapyat;
	}
	
	else if (t[uk]==';'){
		l[i++]=t[uk++];
		simvol++;       ///////////////////////////
		return Type_End_Oper; 
	}

	else if (t[uk]==':'){
		l[i++]=t[uk++];
		simvol++;       ///////////////////////////
		return Type_2_Point; 
	}

	else if (t[uk]=='+') {
		l[i++]=t[uk++]; 
		simvol++;       ///////////////////////////
		return Type_Plus; 
	}

	else if (t[uk]=='-') {
		l[i++]=t[uk++]; 
		simvol++;       ///////////////////////////
		return Type_Minus; 
	}

	else if (t[uk]=='*') {
		l[i++]=t[uk++]; 
		simvol++;       ///////////////////////////
		return Type_Multiplic; 
	}

	else if (t[uk]=='/') {
		l[i++]=t[uk++]; 
		simvol++;       ///////////////////////////
		return Type_Div; 
	}

	else if (t[uk]=='%') {
		l[i++]=t[uk++]; 
		simvol++;       ///////////////////////////
		return Type_Mod; 
	}

	else if (t[uk]=='>') {
		l[i++]=t[uk++];
		simvol++;       ///////////////////////////
		if (t[uk]=='=') {
			l[i++]=t[uk++];
			simvol++;       ///////////////////////////
			return Type_More_Eq;
		}
		else return Type_More;
	}

	else if (t[uk]=='<') {
		l[i++]=t[uk++];
		simvol++;       ///////////////////////////
		if (t[uk]=='=') {
			l[i++]=t[uk++];
			simvol++;       ///////////////////////////
			return Type_Little_Eq;
		}
		else return Type_Little;
	}

	else if (t[uk]=='<') {
		l[i++]=t[uk++];
		simvol++;       ///////////////////////////
		if (t[uk]=='=') {
			l[i++]=t[uk++];
			simvol++;       ///////////////////////////
			return Type_Little_Eq;
		}
		else return Type_Little;
	}

	else if (t[uk]=='=') {
		l[i++]=t[uk++];
		simvol++;       ///////////////////////////
		if (t[uk]=='=') {
			l[i++]=t[uk++];
			simvol++;       ///////////////////////////
			return Type_Eq_Eq;
		}
		else return Type_Equall;
	}

	else if (t[uk]=='!') {
		l[i++]=t[uk++];
		simvol++;       ///////////////////////////
		if (t[uk]=='=') { 
			l[i++]=t[uk++];
			simvol++;       ///////////////////////////
			return Type_No_Eq; 
		}
		else {
			simvol=simvol-i+1;
			PrintError("Неизвестный символ",l); // ошибка
			return Type_Error;

		}
	}


N1: // продолжение числовой константы после точки
	while ( (t[uk]<='9')&&(t[uk]>='0'))
		if (i<MAX_CH_CONST) {
			l[i++]=t[uk++];
			simvol++;       ///////////////////////////
		}
		else uk++;
	if ((t[uk]=='e')||(t[uk]=='E')) {
		l[i++]=t[uk++];
		simvol++;       ///////////////////////////
		goto N2; 
	}
	else{
		simvol=simvol-i+1;
		PrintError("Неверная экспоненциальная константа",l);
		return Type_Error;
	}

N2: // продолжение числовой константы после "E"
	if ( (t[uk]=='+') || (t[uk]=='-') ) {
		l[i++]=t[uk++];
		simvol++;       ///////////////////////////
		if ( (t[uk]<='9') && (t[uk]>='0') )	{
			if (i<MAX_LEX-1){
				l[i++]=t[uk++];
				simvol++;       ///////////////////////////
			} 
			else uk++;
			goto N3;
		}
		else {
			simvol=simvol-i+1;
			PrintError("Неверная экспоненциальная константа",l); // ошибка
			return Type_Error;
		}
	}

N3: // продолжение порядка числовой константы
	while ( (t[uk]<='9') && (t[uk]>='0') )
	{
		if (i<MAX_LEX-1){
			l[i++]=t[uk++];
			simvol++;       ///////////////////////////
		}
		else uk++;
	}
	return Type_Const_E;

}


void TScaner::GetData(char * FileName) {  // ввод файла FileName, который содержит текст исходного модуля
	char aa;
	

	FILE * in ;
	fopen_s( & in, FileName,"r");

	if (in==NULL) {
		PrintError("Отсутствует входной файл","");
		exit(1);
	}

	int i=0;

	while(!feof(in)) {
		fscanf_s(in,"%c",&aa);
		if (!feof(in)) t[i++]=aa;
		if (i>=MAX_TEXT-1) {
			PrintError("Слишком большой размер исходного модуля","");
			break;
		}
	}
	
	t[i]='\0'; // приписываем знак ’\0’ в конец текста
	fclose(in);


} 