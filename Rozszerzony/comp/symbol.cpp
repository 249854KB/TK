#include "global.h"

std::vector<symbol_t> symtable;
int tempCount = 0;
int labelCount = 0;

int lookup(std::string name, int token)
{
  for (int p = symtable.size() - 1; p > 0; p--)
    if (symtable[p].name == name && symtable[p].token == token)
      return p;
  return -1;
}

// manipulation
void initSymtable()
{
  symbol_t read;
  read.name = "read";
  read.token = PROCEDURE;
  read.type = NONE;

  symbol_t write;
  write.name = "write";
  write.token = PROCEDURE;
  write.type = NONE;

  symbol_t program;
  program.name = "program";
  program.token = LABEL;

  symtable.push_back(read);
  symtable.push_back(write);
}

int lookup(const std::string name)
{
  for (int p = symtable.size() - 1; p > 0; p--)
    if (symtable[p].name == name)
      return p;
  return -1;
}

/**
 * @brief Wstawia symbol do tablicy symboli bez dodatkowej logiki
 * @warning Bezpośrednie wstawienie
 * @param sym
 * @return int
 */
int insertPlain(symbol_t sym)
{
  symtable.push_back(sym);
  return symtable.size() - 1;
}

int insert(std::string name, int token, int type)
{
  int found = lookup(name);
  if (found >= 0 && context == symtable[found].global)
    return found;
  symbol_t sym;
  sym.name = name;
  sym.token = token;
  sym.type = type;
  sym.global = context;
  return insertPlain(sym);
}

int newTemp(int type)
{
  symbol_t t;
  t.name = "$t" + std::to_string(tempCount);
  t.type = type;
  t.token = VAR;
  t.address = 0;
  t.global = context;
  int index = insertPlain(t);
  symtable[index].address = getAddress(t.name);
  ++tempCount;
  return index;
}

int newNum(std::string name, int type)
{
  return insert(name, VAL, type);
}

int sizeFromToken(int type)
{
  return type == REAL ? 8 : 4;
}

int getSymbolSize(symbol_t symbol)
{

  if (symbol.token == VAR)
  {
    if (symbol.type == REAL)
      return 8;
    else if (symbol.type == INT)
      return 4;
  }
  return 0;
}

/* look into*/
int getAddress(std::string name)
{
  int address = 0;
  for (auto sym : symtable)
  {
    if (context == LOCAL_CONTEXT)
    {
      if (context == sym.global && sym.address <= 0)
        address -= getSymbolSize(sym);
    }
    else if (sym.name != name)
    {
      address += getSymbolSize(sym);
    }
  }
  return address;
}

void printSymtable()
{
  int lenName = 0, lenTok = 0, LenType = 0;
  for (auto symbol : symtable)
  {
    if (lenName < (int)symbol.name.length())
      lenName = symbol.name.length();
    std::string tok = std::string(token_name(symbol.token));
    if (lenTok < (int)tok.length())
      lenTok = tok.length();
    std::string type = std::string(token_name(symbol.type));
    if (lenTok < (int)type.length())
      lenTok = type.length();
  }

  int i = 0;
  for (auto symbol : symtable)
  {
    std::cout
        << std::setw(std::to_string(symtable.size()).length()) << i++ << " "
        << std::setw(8) << (symbol.global ? "global" : "local")
        << std::setw(5) << (symbol.passed ? "ref" : "")
        << std::setw(lenTok + 2) << token_name(symbol.token) << " "
        << std::setw(lenName + 2) << symbol.name << " "
        << std::setw(LenType + 2) << token_name(symbol.type)
        << ((symbol.type == INT) ? " " : "")
        << ((symbol.token == VAR) ? "\t" + std::to_string(symbol.address) : "")
        << std::endl;
  }
}

symbol_t newArgument(int type)
{
  symbol_t sym;
  sym.name = "argument";
  sym.type = type;
  sym.token = NONE;
  sym.passed = false;
  sym.global = context;
  sym.address = 0xFFFF;
  return sym;
}

int insert(symbol_t sym)
{
  int look = lookup(sym.name);
  // Sprawdzenie czy nie ma takiej zmiennej globalnej
  if (look >= 0 && sym.global == symtable[look].global)
    return look;
  return insertPlain(sym);
}

void clearLocal()
{
  for (int i = symtable.size() - 1; i > 0 && !symtable[i].global; --i, symtable.pop_back())
    ;
}

int getStackSize()
{
  int lastSym = -1;
  for (int i = 0; i < (int)symtable.size(); ++i)
  {
    symbol_t sym = symtable[i];
    if (!sym.global && sym.token == VAR)
    {
      lastSym = i;
    }
  }
  return symtable[lastSym].address > 0 ? 0 : abs(symtable[lastSym].address);
}