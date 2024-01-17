%{
#include "global.h"

int errorno = 0;
std::vector<int> idsList;

// Deklaracje 

bool isType(int);
int yylex();


%}

%token-table

%token PROGRAM
%token VAR

%token BEG
%token END

%token WRITE
%token READ

%token ASSIGN
%token ADDOP
%token MULOP

%token REAL
%token INT
%token VAL
%token ID

%token NONE
%token LABEL
%token DONE

%token PROC

%%
program: 
    PROGRAM ID 
    {
        symtable[$2].token = PROC;
        writeCode("jump.i\t#program", "jump.i program");
    } 
    '(' program_arguments ')' ';'
    vars
    {
        writeLbl("program");
    }
    BEG function_body END
    '.' DONE {
        writeCode("exit\t","exit");
        return 0;
    };
    ;

program_arguments: 
    ID 
    | program_arguments ',' ID;

vars:
    vars VAR vars ':' type ';'
    {
        if(isType($5)) YYERROR;

        for(auto &symTabIdx : idsList) {
            symbol_t* sym = &symtable[symTabIdx];
            sym->type = $5;       
            sym->token = VAR;
            sym->address = getAddress(sym->name);
        }
        idsList.clear();
    }
    | //empty
    ;

type:
    INT | REAL;


vars:
    ID {idsList.push_back($1);}
    | vars ',' ID {idsList.push_back($3);}
    ;


function_body:
    stmts 
    | 
    ;

stmts:
    stmts ';' stmt | stmt ;

stmt:
    ID ASSIGN expression
        {
            appendAssign(symtable[$1], symtable[$3]);
        }
    | read
    | write
    ;

expression:
    term 
    | ADDOP term
    {
        if ($1 == SUB) {
            int zero = newNum("0", symtable[$2].type);
            $$ = append3O(symtable[zero], SUB, symtable[$2]);
        } else {
            $$ = $2;
        }
    }
    | expression ADDOP term
    {
        $$ = append3O(symtable[$1], $2, symtable[$3]);
    }
    ;



term:
    factor 
    | term MULOP factor
    {
        $$ = append2O(symtable[$1], $2, symtable[$3]);
    }
    ;

factor:
    ID 
    | VAL 
    | '(' expression ')'
        {
            $$ = $2;
        }
    ;

 
expression_list:
    expression_list ',' expression 
    {
        idsList.push_back($3);
    }
    | expression
    {
        idsList.push_back($1);
    }
    ;                                                                                                          

read:
    READ '(' expression_list ')' 
    {
        for (auto id : idsList) {
            appendRead(symtable[id]);
        }
        idsList.clear();
    }

write:
    WRITE '(' expression_list ')' 
    {
        for (auto id : idsList) {
            appendWrite(symtable[id]);
        }
        idsList.clear();
    }
%%


bool isType(int type) {
    if(type != INT && type != REAL) {
        yyerror("Nieznany typ");
        return true;
    }
    return false;
}

void yyerror(char const *s){
  printf("Błąd \"%s\" w linii %d\n",s, lineno);
  errorno++;
};


const char *token_name(int token)
{
  return yytname[YYTRANSLATE(token)];
}