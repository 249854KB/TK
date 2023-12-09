/* Odtworzenie regół z pliku lexer.c */
%{
#include "global.h"
int p=0;
int lineno = 1;
int tokenval = NONE;
%}
 
%option noyywrap

NUM   [0-9]+
ALPHA   [a-zA-Z][a-zA-Z0-9]*

%%
[ \t]   {
                ;// Skip whitespaces and tabs
        }

\n      {
                lineno++;
        }

NUM   {
                sscanf(yytext, "%d", &tokenval);
                return NUM;
        }

ALPHA   {
                int p = lookup(yytext); 
                if (p == 0)
                        p = insert (yytext, ID); 
                tokenval = p; 
                return symtable[p].token;
        }


<<EOF>> {
            return DONE;
        }

.       {
            tokenval = NONE;
            return yytext[0];
        }
%%
int lexan() { return yylex(); }