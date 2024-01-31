#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string.h>
#include "tokens.h"
#include "symbol.h"
#include "parser.hpp"

#define GLOBAL_CONTEXT true
#define LOCAL_CONTEXT false

// Zliczanie + tabla symboli na extern

extern bool context;
extern int errorno;
extern int lineno;
extern std::vector<symbol_t> symtable;
extern symbol_t EMPTY_SYMBOL;
// Czyszczenie pamięci

int yylex_destroy();

// Dodawanie i usuwanie z tablicy symboli

/**
 * @brief Tworzy i wstawia nowy symbol do listy symboli
 *
 * @param name nazwa
 * @param token token
 * @param type int/real
 * @return int id nowo powstałego symblu
 */
int insert(std::string name, int token, int type);

/**
 * @brief Wstawia nowy symbol do listy symboli
 *
 * @param sym symbol do wstawienia
 * @return int id nowo powstałego symbolu
 */
int insert(symbol_t sym);

/**
 * @brief Zwaraca id na podstawie nazwy
 *
 * @param name nazwa
 * @return int id /-1 jeśli nie znalezione
 *
 */
int lookup(std::string name);

/**
 * @brief Zwaraca id na podstawie nazwy
 *
 * @param name nazwa
 * @param token Token w jakiej grupie się znajduje. jeżeli będzie on inny niż podany zwróci -1
 * @return int id /-1 jeśli nie znalezione
 *
 */
int lookup(std::string name, int token);
/**
 * @brief Inicjalizacja tablicy smboli
 *
 */
void initSymtable();

/**
 * @brief Zwraca adres po nazwie
 *
 * @param name nazwa
 * @return int adres/ 0 domyślnie
 *
 */
int getAddress(std::string name);

/**
 * @brief Tworzy nową zmienną tymczasową o danym typu
 *
 * @return int type
 */
int newTemp(int type);

/**
 * @brief Wstawia nową stałą tymczasową inset(VAL)
 *
 * @param name liczba
 * @param type typ (int/real)
 * @return int id
 */
int newNum(std::string name, int type);

/**
 * @brief Wstawia nowy Label
 *
 * @return int
 */
int newLabel();

// parser
int yyparse();
// Musi być globalna
void yyerror(char const *);
const char *token_name(int);

/**
 * @brief Zwraca dokładny token operacji ogólnej (mul, add)
 *
 * @return int dokładny token
 */
int getOperationToken(std::string);

/**
 * @brief Wypluwa pełny kod do cmd
 *
 */
void printSymtable();

/**
 * @brief Usuwa wszystkie zmienne lokalne z tablicy symboli
 *
 */
void clearLocal();

/**
 * @brief quick_save for symtable
 *
 */
void startFuncEmittion();
/**
 * @brief Continues symtable
 *
 * @param enterOffset
 */
void endFuncEmittion(std::string enterOffset);

/**
 * @brief Zwraca adress ostatniej zmiennej na stosie
 *
 * @return int
 */
int getStackSize();

// Funkcje formatujące do wypluwania

/**
 * @brief Formatowanie symbolu pod assembler
 *
 * @param s symbol
 * @return std::string postać w assemblerze
 */
std::string format(symbol_t s);

/**
 * @brief Dodaje $ do nazwy
 *
 * @param name nazwa
 * @return std::string $nazwa
 */
std::string formatName(std::string name);

/**
 * @brief Wyrzuca linie kodu
 *
 * @param line Linia kodu
 * @param additional_info wiadomość po średniku
 */
void writeCode(std::string line, std::string additional_info);

/**
 * @brief Wypisuje Label programu/funkcji w postaci label :
 *
 * @param label nazwa do wypisania
 */
void writeLbl(std::string label);

/**
 * @brief Dodaje nowy argument
 *
 * @param type typ
 * @return argument
 */
symbol_t newArgument(int type);
// Appendowanie - pisanie write code

int appendIntToReal(symbol_t from, symbol_t to);
int appendRealToInt(symbol_t from, symbol_t to);
void appendAssign(symbol_t left_side, symbol_t right_side);
int append2O(symbol_t, int, symbol_t);
int append3O(symbol_t, int, symbol_t);
void appendWrite(symbol_t symbolToWrite);
void appendRead(symbol_t symbolToRead);
void appendPush(symbol_t arg, symbol_t expected);
int appendCall(std::string var);
void appendIncsp(int incsp);
void appendJump(int rel_op, symbol_t left_side, symbol_t right_side, symbol_t new_section);

void exportAsm(std::string);
