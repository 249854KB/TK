#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string.h>
#include "tokens.h"
#include "symbol.h"
#include "parser.hpp"

// Sizes
extern int NONESIZE;
extern int INTSIZE;
extern int REALSIZE;

// Zliczanie
extern int errorno;
extern int lineno;

extern std::vector<symbol_t> symtable;
extern symbol_t EMPTY_SYMBOL;

int yylex_destroy();

// symbol
int insert(std::string, int, int);
int insert(std::string, int);
int insert(symbol_t);
int lookup(std::string);
int lookup(std::string name, int token);

void initSymtable();
void printSymtable();
int getAddress(std::string);
int newTemp(int);
int newNum(std::string, int);

// lexer

// parser
int yyparse();
// Musi być globalna
void yyerror(char const *);
const char *token_name(int);

// tokens
int maptoopttoken(std::string);

std::string format(symbol_t);
std::string formatName(std::string);
void wrtInstr(std::string, std::string);
void wrtLbl(std::string);
void emitIntToReal(symbol_t, symbol_t);
void emitRealToInt(symbol_t, symbol_t);

void appendAssign(symbol_t, symbol_t);
int append2O(symbol_t, int, symbol_t);
int append3O(symbol_t, int, symbol_t);
void appendWrite(symbol_t);
void appendRead(symbol_t);

void exportAsm(std::string);