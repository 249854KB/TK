/* Odtworzenie regół z pliku lexer.c */
%option noinput
%{
#include "global.h"
#include "parser.h"
%}
 

%%
[ \t]   {
                // Skip whitespaces and tabs
        }

\n      {
                lineno++;
        }

[0-9]+  {
                sscanf(yytext, "%d", &yylval);
                return NUM;
        }

div     { 
                yylval=NONE; 
                return DIV; 
        }

mod     {       yylval=NONE; 
                return MOD; 
        }

[a-zA-Z][a-zA-Z0-9]*   {
                                int p = lookup(yytext); 
                                if (p == 0)
                                p = insert (yytext, ID); 
                                yylval = p; 
                                return symtable[p].token;
                        }



<<EOF>> {
            return DONE;
        }

.       {
            yylval = NONE;
            return yytext[0];
        }
%%
int lexan() { return yylex(); }