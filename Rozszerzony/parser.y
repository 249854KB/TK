%{
#include "global.h"

int errorno = 0;
std::vector<int> idsList;
std::vector<int> argsList;
// Deklaracje 

bool isType(int);
int yylex();
int functionOffset = 8; // FUNCTION = 12; 
int procedureOffset = 8; //PROCEDURE = 8;
bool context = GLOBAL_CONTEXT;
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

%token PROCEDURE
%token FUNCTION

%%
program: 
    PROGRAM ID 
    {
        symtable[$2].token = PROCEDURE;
        symtable[$2].global = true;
        writeCode("jump.i\t#program", "jump.i program");
    } 
    '(' identifier_list ')' ';'
    global_variables
    subprogram_declarations 
    {
        // After subprogram we start program:
        writeLbl("program");
    } 
    body
    '.' DONE {
        writeCode("exit\t\t","exit");
        return 0;
    }
    

subprogram_declarations:
    subprogram_declarations subprogram_declaration ';'
    |  //empty 
    ;


subprogram_declaration:
    subprogram_head local_variables body
    {
        context = GLOBAL_CONTEXT;
    }

subprogram_head:
    FUNCTION ID
    {
        writeLbl(symtable[$2].name);
        context = LOCAL_CONTEXT;
    } 
    arguments ':' type ';'
    {
        
        symbol_t* function = &symtable[$2];
        function->token = FUNCTION;
        function->type = $5;
        std::vector<symbol_t>args;
        for(auto id : argsList) {
            symbol_t idS = symtable[id];
            args.push_back(newArgument(idS.type));
            
        }
        
        function->arguments = args;
        argsList.clear();
        // TO do append argsList in different places
        functionOffset = 8;
        symbol_t returnVar;
        returnVar.name = function->name;
        returnVar.token = VAR;
        returnVar.type = $5;
        // Ponieważ miejsce zostało z góry przeznaczone
        returnVar.passed = true;
        returnVar.global = false;
        returnVar.address = functionOffset;
        insert(returnVar);
    }
    
    | PROCEDURE ID arguments ';'
    

arguments:
    '(' parameter_list  ')'
     {
        std::vector<int>::iterator arg;
        for (arg = argsList.end() - 1; arg >= argsList.begin(); arg--) {
            functionOffset += 4; // Size of reference
            symtable[*arg].address = functionOffset;
        }
    }
    | //empty
    ; 

parameter_list:
    variables ':' type
    {
        if(isType($3)) YYERROR;

        for(auto &symTabIdx : idsList) {
            symbol_t* sym = &symtable[symTabIdx];
            sym->type = $3;
            sym->token = VAR;
            sym->global = false;
            sym->passed = true;
        }
        argsList.insert(argsList.end(), idsList.begin(), idsList.end());
        idsList.clear();
    }
    | parameter_list ';' variables ':' type
    {
        if(isType($5)) YYERROR;
        std::cout << "Left bitch";
        for(auto &symTabIdx : idsList) {
            symbol_t* sym = &symtable[symTabIdx];
            sym->type = $5;
            sym->token = VAR;
            sym->global = false;
            sym->passed = true;
    
        }
        argsList.insert(argsList.end(), idsList.begin(), idsList.end());
        idsList.clear();
    }

body:
    BEG function_body END

identifier_list: 
    ID 
    | variables ',' ID;

global_variables:
    global_variables VAR variables ':' type ';'
    {
        if(isType($5)) YYERROR;

        for(auto &symTabIdx : idsList) {
            symbol_t* sym = &symtable[symTabIdx];
            sym->type = $5;       
            sym->token = VAR;
            sym->global = true;
            sym->address = getAddress(sym->name);
        }
        idsList.clear();
    }
    | //empty
    ;

local_variables:
    local_variables VAR variables ':' type ';' 
    {
        if(isType($5)) YYERROR;

        for(auto &symTabIdx : idsList) {
            symbol_t* sym = &symtable[symTabIdx];
            sym->type = $5;       
            sym->token = VAR;
            sym->global = false;
            sym->address = getAddress(sym->name);
        }
        idsList.clear();
    }
    | // empty
    ;

type:
    INT | REAL


variables:
    ID {idsList.push_back($1);}
    | variables ',' ID {idsList.push_back($3);}
    


function_body:
    stmts 
    | //empty
    ;

stmts:
    stmts ';' stmt | stmt 

stmt:
    ID ASSIGN expression
        {
            appendAssign(symtable[$1], symtable[$3]);
        }
    | ID ASSIGN call
    | read
    | write
    | call

call:
    ID '(' expression_list ')'
    {
        int id = lookup(symtable[$1].name, FUNCTION);
        if ( id == -1 ) {
            yyerror((symtable[$1].name + " is not callable.").c_str());
            YYERROR;
        }

        symbol_t function = symtable[id];
        if(function.arguments.size() < idsList.size()) {
            yyerror("Podano za dużo argumentów do funkcji");
            YYERROR;
        } else if (function.arguments.size() > idsList.size()) {
            yyerror("Podano za mało argumentów do funkcji");
            YYERROR;
        }

        int incsp = 0; //increase stack pointer
        for(int id = 0; id < (int)(idsList.size()); ++id, incsp += 4) {
            symbol_t given = symtable[idsList[id]];
            symbol_t expectedType = function.arguments[id];
            appendPush(given, expectedType);
            
        }
        idsList.clear();
        
        if(function.token == FUNCTION) {
            // pushing place for the wynik
            int result = newTemp(function.type);
            appendPush(symtable[result], newArgument(function.type));
            incsp += 4;
            $$ = result;
        }

        appendCall(function.name);
        
        newNum(std::to_string(incsp), INT);
        appendIncsp(incsp);
    }
    

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
    



term:
    factor 
    | term MULOP factor
    {
        $$ = append2O(symtable[$1], $2, symtable[$3]);
    }
    

factor:
    ID 
    | VAL 
    | '(' expression ')'
        {
            $$ = $2;
        }
    

 
expression_list:
    expression_list ',' expression 
    {
        idsList.push_back($3);
    }
    | expression
    {
        idsList.push_back($1);
    }
                                                                                                             

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

local_variables:
    | //empty
    ;
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