#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT 10000 // максимальная длина текста
#define MAX_LEX 100 // максимальная длина лексемы
#define MAX_KEYW 8 // число ключевых слов
#define MAX_CH_CONST 9

typedef char TypeLex[MAX_LEX];
typedef char TypeMod[MAX_TEXT];

// ключевые слова
#define Type_Void 0
#define Type_Int 1
#define Type_Double 2
#define Type_Switch 3
#define Type_Case 4
#define Type_Default 5
#define Type_Break 6
#define Type_Main 41

// идентификаторы и константы
#define Type_Id 7
#define Type_Const 8
#define Type_Const_E 9
#define Type_Const_Simb 10

// специальные знаки
#define Type_Open_Blok 11
#define Type_Close_Blok 12
#define Type_Skobka_Op 13
#define Type_Skobka_Cl 14
#define Type_Zapyat 15
#define Type_End_Oper 16
#define Type_2_Point 17

// знаки операций
#define Type_Plus 18
#define Type_Minus 19
#define Type_Multiplic 20
#define Type_Div 21
#define Type_Mod 22
#define Type_Equall 23
#define Type_More 24
#define Type_Little 25
#define Type_More_Eq 26
#define Type_Little_Eq 27
#define Type_Eq_Eq 28
#define Type_No_Eq 29

// конец исходного модуля
#define Type_End 200

// ошибочный символ
#define Type_Error 100
