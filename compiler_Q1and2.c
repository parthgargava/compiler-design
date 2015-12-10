vi intac.l
%{
 #include "y.tab.h"
 extern char yyval;
%}

NUMBER [0-9]+
LETTER [a-zA-Z]+
%%
{NUMBER} {yylval.sym=(char)yytext[0]; return NUMBER;}
{LETTER} {yylval.sym=(char)yytext[0]; return LETTER;}
\n {return 0;}
. {return yytext[0];}
%%
===========================


vi intac.y
%{
#include<stdio.h>
 #include<string.h>
 #include<stdlib.h>
 void ThreeAddressCode();
 
 char AddToTable(char ,char, char);

int ind=0;
 char temp='A';
 struct incod
 {
 char opd1;
 char opd2;
 char opr;
 };
 %}

%union
 {
 char sym;
 }

%token <sym> LETTER NUMBER
 %type <sym> expr
 %left '-''+'
 %right '*''/'

%%

statement: LETTER '=' expr ';' {AddToTable((char)$1,(char)$3,'=');}
 | expr ';'
 ;

expr: expr '+' expr {$$ = AddToTable((char)$1,(char)$3,'+');}
 | expr '-' expr {$$ = AddToTable((char)$1,(char)$3,'-');}
 | expr '*' expr {$$ = AddToTable((char)$1,(char)$3,'*');}
 | expr '/' expr {$$ = AddToTable((char)$1,(char)$3,'/');}
 | '(' expr ')' {$$ = (char)$2;}
 | NUMBER {$$ = (char)$1;}
 | LETTER {$$ = (char)$1;}
 ;

%%

yyerror(char *s)
 {
 printf("%s",s);
 exit(0);
 }

struct incod code[20];

int id=0;
char AddToTable(char opd1,char opd2,char opr)
 {
 code[ind].opd1=opd1;
 code[ind].opd2=opd2;
 code[ind].opr=opr;
 ind++;
 temp++;
 return temp;
 }

void ThreeAddressCode()
 {
 int cnt=0;
 temp++;
 printf("\n\n\t THREE ADDRESS CODE\n\n");
 while(cnt<ind)
 {
 printf("%c : = \t",temp);
 if(isalpha(code[cnt].opd1))
 printf("%c\t",code[cnt].opd1);
 else
 {printf("%c\t",temp);}

printf("%c\t",code[cnt].opr);

if(isalpha(code[cnt].opd2))
 printf("%c\t",code[cnt].opd2);
 else
 {printf("%c\t",temp);}

printf("\n");
 cnt++;
 temp++;
 }
 }





main()
 {
 printf("\nEnter the Expression:" );
 yyparse();
 temp='A';
 ThreeAddressCode();

 }

yywrap()
 {
 return 1;
 }
 
 
 
 
 question 2
 
 vi inmac.l
%{
 #include<stdio.h>
 #include<string.h>
 #include "y.tab.h"
%}
%%
[a-z][a-z0-9]* {strcpy(yylval.var,yytext);return NAME;}
[+] {strcpy(yylval.var,yytext); return PLUS;}
[=] {strcpy(yylval.var,yytext); return EQUAL;}
[-] {strcpy(yylval.var,yytext);return SUBT;}
[\n\t] {return yytext[0];}
%%

vi inmac.y

%{
#include<stdio.h>
#include<ctype.h>
#include<string.h>
FILE *fout;
%}
 %token<var> NAME PLUS EQUAL MULT DIVI SUBT
 %type<var> exp
 %union
 {
 char var[10];
 }
 %right EQUAL
 %left PLUS SUNT
 %left MULT DIVI
 %%

input:line'\n'input
 |'\n'input
 |/*empty*/
 ;
 line:NAME EQUAL exp {fprintf(fout,"MOV %s,AX\n",$1);}
 ;
 exp:NAME PLUS NAME {fprintf(fout,"MOV AX,%s \n ADD AX,%s\n",$1,$3);}
 |NAME SUBT NAME {fprintf(fout,"MOV AX,%s \n SUB AX,%s\n",$1,$3);}
 |NAME MULT NAME {fprintf(fout,"MOV AX,%s \n MUL AX,%s\n",$1,$3);}
 |NAME DIVI NAME {fprintf(fout,"MOV AX,%s \n DIV AX,%s\n",$1,$3);}
 |NAME {strcpy($$,$1);}
 ;
 %%

extern yylineno;

yyerror()
 {
 printf("\neroor %d",yylineno);
 }
 yywrap()
 {
 return 1;
 }
 extern FILE *yyin;
 main()

{

FILE *fin;
 fin=fopen("input.txt","r");
 fout=fopen("out.txt","w");

yyin=fin;

yyparse();
 fcloseall();
 return 0;
 }
t1=a+b
 t2=b+t1
 c=t2
 
 MOV AX,a
 ADD AX,b
 MOV t1,AX
 MOV AX,b
 ADD AX,t1
 MOV t2,AX
 MOV c,AX
