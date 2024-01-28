/**
 * @file symbol.h
 * @author Krzysztof Bortnowski (krzysztof.bortnowski@sesto.pl)
 * @brief
 * @version 0.1
 * @date 2024-01-16
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef SYMBOL_H_
#define SYMBOL_H_

#include <string>
#include <utility>

/**
 * @brief struktura opisująca symbol
 *
 */
struct symbol_t
{
  std::string name;                // Nazwa
  int token;                       // Token
  int type;                        // int/real
  int address;                     // address
  std::vector<symbol_t> arguments; // argumenty wykorzystywane w funkcji
  bool global;                     // Globalne
  bool passed;                     // Otrzymane z innej funkcji (jest argumentem)
};

#endif // SYMBOL_H_