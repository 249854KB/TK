/* Odtworzenie regół z pliku lexer.c */
%option noyywrap
%option noinput
%{
#include "global.h"

int lineno = 1;
int tokenval = NONE;
%}
 

%%
[ \t]   {
                // Skip whitespaces and tabs
        }

\n      {
                lineno++;
        }

[0-9]+  {
                sscanf(yytext, "%d", &tokenval);
                return NUM;
        }

[a-zA-Z][a-zA-Z0-9]*   {
                                int p = lookup(yytext); 
                                if (p == 0)
                                p = insert (yytext, ID); 
                                tokenval = p; 
                                return symtable[p].token;
                        }

div     { 
                tokenval=NONE; 
                return DIV; 
        }

mod     {       tokenval=NONE; 
                return MOD; 
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