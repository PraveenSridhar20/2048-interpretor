%option noyywrap
%{
#define YYSTYPE char*
#include "parser.tab.hh"    
#include "pl.h"
using namespace std;
%}



%%
"ADD" {return ADD;}
"SUBTRACT" {return SUBTRACT;}
"MULTIPLY" {return MULTIPLY;}
"DIVIDE" {return DIVIDE;}
"LEFT" {return LEFT;}
"RIGHT" {return RIGHT;}
"UP" {return UP;}
"DOWN" {return DOWN;}
"ASSIGN" {return ASSIGN;}
"TO" {return TO;}
"VAR" {return VAR;}
"IS" {return IS;}
"VALUE" {return VALUE;}
"IN" {return IN;}
"EXIT" {return EXIT;}
"," {return COMMA;}
"." {return END;}
"\n" {return NEWLINE;}
[1-9][0-9]* {yylval=(yytext);return NUMBER;}
[0] {yylval=(yytext);return NUMBER;}
[0-9]+[a-zA-z0-9_]+ {cout<<"\nInvalid token\n"; return END; }
[a-zA-Z_][a-zA-Z0-9_]* {yylval=yytext;return VARIABLE;}
[' ']+ {}
. {cout<<"\nInvalid token\n";}
%%