%option noyywrap

digit   [0-9]
nndigit [1-9]
letter  [a-zA-Z_]
number  {digit}|{nndigit}{digit}*
letterAndDigit  {digit}|{letter}

%%

#include<iostream>      {printf("#include<iostream> - cuvant cheie\n");}

using                   {printf("using - cuvant cheie\n");}

namespace               {printf("namespace - cuvant cheie\n");}

std                     {printf("std - cuvant cheie\n");}

main                    {printf("main - cuvant cheie\n");}

int                     {printf("int - cuvant cheie\n");}

double                  {printf("double - cuvant cheie\n");}

struct                  {printf("struct - cuvant cheie\n");}

cin>>                   {printf("cin>> - cuvant cheie\n");}

cout<<                  {printf("cout<< - cuvant cheie\n");}

if                      {printf("if - cuvant cheie\n");}

then                    {printf("then - cuvant cheie\n");}

endif                   {printf("endif - cuvant cheie\n");}

while                   {printf("while - cuvant cheie\n");}

">="                    {printf(">= - operator\n");}

"<="                    {printf("<= - operator\n");}

"!="                    {printf("!= - operator\n");}

"="                     {printf("= - operator\n");}

"<"                     {printf("< - operator\n ");}

">"                     {printf("> - operator\n");}

"*"                     {printf("* - operator\n ");}

"/"                     {printf("/ - operator\n");}

"%"                     {printf("\% - operator\n");}

"+"                     {printf("+ - operator\n");}

"-"                     {printf("- - operator\n");}

"("                     {printf("( - separator\n");}

")"                     {printf(") - separator\n");}

"{"                     {printf("{ - separator\n");}

"}"                     {printf("} - separator\n");}

";"                     {printf("; - separator\n");}

","                     {printf(", - separator\n");}

([+-]?{number}([.]{number})?)|(["][^"]*["])     {printf("Constanta\n");}

{letter}({letter}|{digit})*                     {printf("Identificator\n");}

(^{letter})*({letter}|{digit}|[@])*             {printf("Eroare lexicala\n");}


[ \n\t]                                                                                                 ;

.                                                                                                               {printf("?token ");}

%%
int main(){

        yylex();
}
