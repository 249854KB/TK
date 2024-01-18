/**
 * @file emitter.cpp
 * @author Krzysztof Bortnowski (krzysztof.bortnowski@sesto.pl)
 * @brief
 * @version 0.1
 * @date 2024-01-18
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "global.h"
#include <sstream>
#include <iostream>
#include <fstream>

// Local
// Output stream for generated assembly code
std::stringstream outb;
/**
 * @brief Zwraca string operatora
 *
 * @param op
 * @return std::string
 */
std::string addop(int op)
{
  switch (op)
  {
  case ADD:
    return "add.";
  case SUB:
    return "sub.";
  default:
    return "ERROR";
  }
}

/**
 * @brief Zwraca string operatora
 *
 * @param op
 * @return std::string
 */
std::string mulop(int op)
{
  switch (op)
  {
  case MUL:
    return "mul.";
  case DIV:
    return "div.";
  case MOD:
    return "mod.";
  default:
    return "ERROR";
  }
}

/**
 * @brief Zwraca znak liczby
 *
 * @param a numer
 * @return std::string +/-
 */
std::string sign(int a)
{
  return a < 0 ? "-" : "+";
}

std::string format(symbol_t s)
{
  if (s.token == VAL || s.token == LABEL)
  {
    return "#" + s.name;
  }
  else if (s.token == VAR)
  {
    return std::to_string(abs(s.address));
  }
  return "";
}

std::string formatName(std::string name)
{
  return "$" + name;
}

void writeCode(std::string line, std::string additional_info)
{
  outb << "\t" << line << "\t\t;" << additional_info << std::endl;
}

void writeLbl(std::string label)
{
  outb << label + ":" << std::endl;
}

// Convert a data type to its corresponding assembly type
std::string typeInAsm(int type)
{
  return (type == REAL) ? "r" : "i";
}

// Convert integer to real and vice versa in assembly code
void appendIntToReal(symbol_t from, symbol_t to)
{
  writeCode("inttoreal.i\t" + format(from) + "," + format(to),
            "inttoreal.i\t" + formatName(from.name) + "," + formatName(to.name));
}

void appendRealToInt(symbol_t from, symbol_t to)
{
  writeCode("realtoint.r\t" + format(from) + "," + format(to),
            "realtoint.r\t" + formatName(from.name) + "," + formatName(to.name));
}

// Expand and cast the right side to match the left side for assignment
void appendAssign(symbol_t left_side, symbol_t right_side)
{
  if (left_side.type != right_side.type)
  {
    // Handle type conversion
    if (left_side.type == INT && right_side.type == REAL)
      appendRealToInt(right_side, left_side);
    else if (left_side.type == REAL && right_side.type == INT)
      appendIntToReal(right_side, left_side);
    else
      yyerror(("Types " +
               std::string(token_name(left_side.type)) + " and " +
               std::string(token_name(right_side.type)) + " are incompatible.")
                  .c_str());
  }

  writeCode("mov." + typeInAsm(left_side.type) + "\t" + format(right_side) + "," + format(left_side) + "\t",
            "mov." + typeInAsm(left_side.type) + "\t" + formatName(right_side.name) + "," + formatName(left_side.name));
}

// Check if the types of two symbols are different
int willChange(symbol_t left_side, symbol_t right_side)
{
  return left_side.type != right_side.type;
}

// Expand and cast for arithmetic operations with three operands
int append3O(symbol_t left_side, int operacja, symbol_t right_side)
{
  if (willChange(left_side, right_side))
    appendAssign(left_side, right_side);

  int result = newTemp(left_side.type);
  writeCode(addop(operacja) + typeInAsm(left_side.type) + "\t" + format(left_side) + "," + format(right_side) + "," + format(symtable[result]) + "\t",
            addop(operacja) + typeInAsm(left_side.type) + "\t" + formatName(left_side.name) + "," + formatName(right_side.name) + "," + formatName(symtable[result].name));

  return result;
}

// Expand and cast for arithmetic operations with two operands
int append2O(symbol_t left_side, int operacja, symbol_t right_side)
{
  if (willChange(left_side, right_side))
    appendAssign(left_side, right_side);

  int result = newTemp(left_side.type);
  writeCode(mulop(operacja) + typeInAsm(left_side.type) + "\t" + format(left_side) + "," + format(right_side) + "," + format(symtable[result]) + "\t",
            mulop(operacja) + typeInAsm(left_side.type) + "\t" + formatName(left_side.name) + "," + formatName(right_side.name) + "," + formatName(symtable[result].name));

  return result;
}

// Format a symbol for reference in assembly code
std::string formatRef(symbol_t s)
{
  if (s.token == VAL || s.token == LABEL)
  {
    return "#" + s.name;
  }
  else if (s.token == VAR)
  {
    return std::to_string(abs(s.address));
  }
  return "";
}

// Write assembly code for write operation
void appendWrite(symbol_t symbolToWrite)
{
  writeCode("write." + typeInAsm(symbolToWrite.type) + "\t" + format(symbolToWrite) + "\t",
            "write." + typeInAsm(symbolToWrite.type) + "\t" + formatName(symbolToWrite.name));
}

// Write assembly code for read operation
void appendRead(symbol_t symbolToRead)
{
  writeCode("read." + typeInAsm(symbolToRead.type) + "\t" + format(symbolToRead) + "\t",
            "read." + typeInAsm(symbolToRead.type) + "\t" + formatName(symbolToRead.name));
}

// Export the generated assembly code to a file
void exportAsm(std::string fname)
{
  std::ofstream outFile(fname);
  outFile << outb.str();
  outFile.close();

  std::cout << outb.str() << std::endl;
}
