vi lex1.l

%{
#include "y.tab.h"
%}
%%
\*                      {return('*'); }
\+                      {return('+'); }
\(                      {return('('); }
\)                      {return(')'); }
[0-9]+          { yylval.type=1;  return(NUMBER);}
\;              {return(en);}
.               ;
%%


vi  yacc1.y

%{
#include<stdio.h>
%}

%union
{
 int type;
}

%token <type>  NUMBER
%token en
%type <type> line
%type <type> expr
%type <type> term
%type <type> factor
%%
suc         :   line{printf("Answer=%d",$1);} suc;

line        :   expr en {$$=$1;}        ;

expr        :   expr '+' term {if ($1==$3) printf("type correct"); else printf("type error");}
             |  term    ;

term        :   term '*' factor  { $$=$1*$3;}
             |  factor  ;

factor      :   '(' expr ')' {$$=$2;}
             |  NUMBER{$$=$1;}  ;
%%
main()
{return(yyparse());}
yyerror(s)
char *s;
{fprintf(stderr,"%s\n",s); }
yywrap()
{ return(1);}


