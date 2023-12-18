/* Odtworzenie regół z pliku lexer.c */
%option noyywrap
%option noinput
%{
#include "global.h"
extern int insert (char s[], int tok);
extern int lookup (char s[]);
int lineno = 1;
int tokenval = NONE;
%}

NUM   [0-9]+
ALPHA   [a-zA-Z][a-zA-Z0-9]*

%%
[ \t]   {
                // Skip whitespaces and tabs
        }

\n      {
                lineno++;
        }

NUM     {
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