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

void wrtInstr(std::string instr, std::string repr)
{
  outb << "\t" << instr << "\t\t;" << repr << std::endl;
}

void wrtLbl(std::string label)
{
  outb << label + ":" << std::endl;
}

struct Expanded
{
  int tt;
  std::string st;
  symbol_t l;
  symbol_t r;
};

std::string tType(int t)
{
  if (t == REAL)
  {
    return "r";
  }
  return "i";
}

void emitIntToReal(symbol_t from, symbol_t to)
{
  wrtInstr(
      "inttoreal.i\t" + format(from) + "," + format(to),
      "inttoreal.i\t" + formatName(from.name) + "," + formatName(to.name));
}

void emitRealToInt(symbol_t from, symbol_t to)
{
  wrtInstr(
      "realtoint.r\t" + format(from) + "," + format(to),
      "realtoint.r\t" + formatName(from.name) + "," + formatName(to.name));
}

// casts right side to match left side
Expanded expandAssign(symbol_t lvar, symbol_t rvar)
{
  std::string stype;
  int ttype;
  if (lvar.type == rvar.type)
  {
    stype = tType(lvar.type);
    ttype = lvar.type;
  }
  else
  {
    if (lvar.type == INT && rvar.type == REAL)
    {
      int temp = newTemp(INT);
      stype = tType(INT);
      ttype = INT;
      emitRealToInt(rvar, symtable[temp]);
      rvar = symtable[temp];
    }
    else if (lvar.type == REAL && rvar.type == INT)
    {
      int temp = newTemp(REAL);
      stype = tType(REAL);
      ttype = REAL;
      emitIntToReal(rvar, symtable[temp]);
      rvar = symtable[temp];
    }
    else
    {
      yyerror(("Types " +
               std::string(token_name(lvar.type)) + " and " +
               std::string(token_name(rvar.type)) + " are incompatible.")
                  .c_str());
    }
  }
  return {ttype, stype, lvar, rvar};
}

void appendAssign(symbol_t lvar, symbol_t rvar)
{
  // all different kinds of checks and casts
  Expanded exp = expandAssign(lvar, rvar);
  wrtInstr(
      "mov." + exp.st + "\t" + format(exp.r) + "," + format(exp.l),
      "mov." + exp.st + "\t" + formatName(exp.r.name) + "," + formatName(exp.l.name));
}

int shouldChange(symbol_t lvar, symbol_t rvar)
{
  int tL = REAL, tR = REAL;
  if (lvar.type == INT)
    tL = INT;
  if (rvar.type == INT)
    tR = INT;

  return tL == tR;
}

Expanded expand(symbol_t lvar, symbol_t rvar)
{
  std::string stype;
  int ttype;
  if (shouldChange(lvar, rvar))
  {
    if (lvar.type != rvar.type)
    {
      stype = tType(INT);
      ttype = INT;
    }
    else
    {
      stype = tType(lvar.type);
      ttype = lvar.type;
    }
  }
  else
  {
    if (lvar.type == INT && rvar.type == REAL)
    {
      int temp = newTemp(REAL);
      stype = tType(REAL);
      ttype = REAL;
      emitIntToReal(lvar, symtable[temp]);
      lvar = symtable[temp];
    }
    else if (lvar.type == REAL && rvar.type == INT)
    {
      int temp = newTemp(REAL);
      stype = tType(REAL);
      ttype = REAL;
      emitIntToReal(rvar, symtable[temp]);
      rvar = symtable[temp];
    }
    else
    {
      std::cout << printS(lvar) << "; " << printS(rvar) << std::endl;
      yyerror(("Types " +
               std::string(token_name(lvar.type)) + " and " +
               std::string(token_name(rvar.type)) + " are incompatible.")
                  .c_str());
    }
  }
  return {ttype, stype, lvar, rvar};
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

int append3O(symbol_t lvar, int op, symbol_t rvar)
{
  Expanded exp = expand(lvar, rvar);
  int result = newTemp(exp.tt);
  wrtInstr(
      addop(op) + exp.st + "\t" + format(exp.l) +
          "," + format(exp.r) + "," + format(symtable[result]),
      addop(op) + exp.st + "\t" + formatName(exp.l.name) +
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

int append2O(symbol_t lvar, int op, symbol_t rvar)
{
  Expanded exp = expand(lvar, rvar);
  int result = newTemp(exp.tt);
  wrtInstr(
      mulop(op) + exp.st + "\t" + format(exp.l) +
          "," + format(exp.r) + "," + format(symtable[result]),
      mulop(op) + exp.st + "\t" + formatName(exp.l.name) +
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

void appendWrite(symbol_t sym)
{
  wrtInstr(
      "write." + tType(sym.type) + "\t" + format(sym),
      "write." + tType(sym.type) + "\t" + formatName(sym.name));
}

void appendRead(symbol_t sym)
{
  wrtInstr(
      "read." + tType(sym.type) + "\t" + format(sym),
      "read." + tType(sym.type) + "\t" + formatName(sym.name));
}

void startFuncEmittion()
{
  freezed = outb.str();
  outb.str(std::string());
}

void endFuncEmittion(std::string enterOffset)
{
  wrtInstr("leave\t", "leave");
  wrtInstr("return\t", "return");

  funcbody = outb.str();
  outb.str(std::string());
  outb << freezed;
  wrtInstr("enter.i\t#" + enterOffset + "\t", "enter.i\t#" + enterOffset);
  outb << funcbody;
}

void exportAsm(std::string fname)
{
  std::ofstream outFile;
  outFile.open(fname);
  outFile << outb.str();
  outFile.close();

  std::cout << outb.str() << std::endl;
}