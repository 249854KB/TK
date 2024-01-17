#include "global.h"
#include <sstream>
#include <iostream>
#include <fstream>

std::stringstream outb;
std::string freezed;
std::string funcbody;

std::string printS(symbol_t s)
{
  return s.name + ", type=" + token_name(s.type) + ", token=" + token_name(s.token);
}

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

struct Expanded
{
  int tt;
  std::string st; // i or r
  symbol_t l;
  symbol_t r;
};

std::string typeInAsm(int type)
{
  if (type == REAL)
  {
    return "r";
  }
  return "i";
}

void appendIntToReal(symbol_t from, symbol_t to)
{
  writeCode(
      "inttoreal.i\t" + format(from) + "," + format(to),
      "inttoreal.i\t" + formatName(from.name) + "," + formatName(to.name));
}

void appendRealToInt(symbol_t from, symbol_t to)
{
  writeCode(
      "realtoint.r\t" + format(from) + "," + format(to),
      "realtoint.r\t" + formatName(from.name) + "," + formatName(to.name));
}

// casts right side to match left side
Expanded expandAssign(symbol_t left_side, symbol_t right_side)
{
  std::string stype;
  int ttype;
  if (left_side.type == right_side.type)
  {
    stype = typeInAsm(left_side.type);
    ttype = left_side.type;
  }
  else
  {
    if (left_side.type == INT && right_side.type == REAL)
    {
      int temp = newTemp(INT);
      stype = typeInAsm(INT);
      ttype = INT;
      appendRealToInt(right_side, symtable[temp]);
      right_side = symtable[temp];
    }
    else if (left_side.type == REAL && right_side.type == INT)
    {
      int temp = newTemp(REAL);
      stype = typeInAsm(REAL);
      ttype = REAL;
      appendIntToReal(right_side, symtable[temp]);
      right_side = symtable[temp];
    }
    else
    {
      yyerror(("Types " +
               std::string(token_name(left_side.type)) + " and " +
               std::string(token_name(right_side.type)) + " are incompatible.")
                  .c_str());
    }
  }
  return {ttype, stype, left_side, right_side};
}

void appendAssign(symbol_t left_side, symbol_t right_side)
{
  // all different kinds of checks and casts
  Expanded exp = expandAssign(left_side, right_side);
  writeCode(
      "mov." + exp.st + "\t" + format(exp.r) + "," + format(exp.l) + "\t",
      "mov." + exp.st + "\t" + formatName(exp.r.name) + "," + formatName(exp.l.name));
}

int willChange(symbol_t left_side, symbol_t right_side)
{
  if (left_side.type == right_side.type)
    return false;
  else
    return true;
}

/**
 * @brief Tworzy wynik operacji po prawej i lewej stronie
 *
 * @param left_side
 * @param right_side
 * @return Expanded
 */
Expanded expand(symbol_t left_side, symbol_t right_side)
{
  std::string stype;
  int ttype;
  if (willChange(left_side, right_side))
  {

    if (left_side.type == INT && right_side.type == REAL)
    {
      int temp = newTemp(REAL);
      stype = typeInAsm(REAL);
      ttype = REAL;
      appendIntToReal(left_side, symtable[temp]);
      left_side = symtable[temp];
    }
    else if (left_side.type == REAL && right_side.type == INT)
    {
      int temp = newTemp(REAL);
      stype = typeInAsm(REAL);
      ttype = REAL;
      appendIntToReal(right_side, symtable[temp]);
      right_side = symtable[temp];
    }
    else
    {
      std::cout << printS(left_side) << "; " << printS(right_side) << std::endl;
      yyerror(("Typy zmiennych " +
               std::string(token_name(left_side.type)) + " i " +
               std::string(token_name(right_side.type)) + " nie mogą zostać przypisane :=")
                  .c_str());
    }
  }
  else
  {
    stype = typeInAsm(left_side.type);
    ttype = left_side.type;
  }
  return {ttype, stype, left_side, right_side};
}

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

int append3O(symbol_t left_side, int operacja, symbol_t right_side)
{
  Expanded exp = expand(left_side, right_side);
  int result = newTemp(exp.tt);
  writeCode(
      addop(operacja) + exp.st + "\t" + format(exp.l) +
          "," + format(exp.r) + "," + format(symtable[result]) + "\t",
      addop(operacja) + exp.st + "\t" + formatName(exp.l.name) +
          "," + formatName(exp.r.name) + "," + formatName(symtable[result].name));

  return result;
}

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

int append2O(symbol_t left_side, int operacja, symbol_t right_side)
{
  Expanded exp = expand(left_side, right_side);
  int result = newTemp(exp.tt);
  writeCode(
      mulop(operacja) + exp.st + "\t" + format(exp.l) +
          "," + format(exp.r) + "," + format(symtable[result]) + "\t",
      mulop(operacja) + exp.st + "\t" + formatName(exp.l.name) +
          "," + formatName(exp.r.name) + "," + formatName(symtable[result].name));

  return result;
}

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

void appendWrite(symbol_t symbolToWrite)
{
  writeCode(
      "write." + typeInAsm(symbolToWrite.type) + "\t" + format(symbolToWrite) + "\t",
      "write." + typeInAsm(symbolToWrite.type) + "\t" + formatName(symbolToWrite.name));
}

void appendRead(symbol_t symbolToRead)
{
  writeCode(
      "read." + typeInAsm(symbolToRead.type) + "\t" + format(symbolToRead) + "\t",
      "read." + typeInAsm(symbolToRead.type) + "\t" + formatName(symbolToRead.name));
}

void exportAsm(std::string fname)
{
  std::ofstream outFile;
  outFile.open(fname);
  outFile << outb.str();
  outFile.close();

  std::cout << outb.str() << std::endl;
}