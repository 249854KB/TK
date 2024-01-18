#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string.h>
#include "tokens.h"
#include "symbol.h"
#include "parser.hpp"

// Zliczanie + tabla symboli na extern

extern int errorno;
extern int lineno;
extern std::vector<symbol_t> symtable;

// Czyszczenie pamięci

int yylex_destroy();

// Dodawanie i usuwanie z tablicy symboli

/**
 * @brief Wstawia nowy symbol do listy symboli
 *
 * @param name nazwa
 * @param token token
 * @param type int/real
 * @return int id nowo powstałego symblu
 */
int insert(std::string name, int token, int type);

/**
 * @brief Zwaraca id na podstawie nazwy
 *
 * @param name nazwa
 * @return int id /-1 jeśli nie znalezione
 *
 */
int lookup(std::string name);

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

int newTemp(int);
int newNum(std::string, int);

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

// Appendowanie - pisanie write code

void appendIntToReal(symbol_t from, symbol_t to);
void appendRealToInt(symbol_t from, symbol_t to);
void appendAssign(symbol_t left_side, symbol_t right_side);
int append2O(symbol_t, int, symbol_t);
int append3O(symbol_t, int, symbol_t);
void appendWrite(symbol_t symbolToWrite);
void appendRead(symbol_t symbolToRead);

void exportAsm(std::string);