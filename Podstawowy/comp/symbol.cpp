#include "global.h"

symbol_t EMPTY_SYMBOL;

std::vector<symbol_t> symtable;
int tempCount = 0;
int labelCount = 0;

// manipulation
void initSymtable()
{
  symbol_t read;
  read.name = "read";
  read.token = PROC;
  read.type = NONE;

  symbol_t write;
  write.name = "write";
  write.token = PROC;
  write.type = NONE;

  symbol_t program;
  program.name = "program";
  program.token = LABEL;

  symtable.push_back(read);
  symtable.push_back(write);
}

int lookup(const std::string s)
{
  for (int p = symtable.size() - 1; p > 0; p--)
    if (symtable[p].name == s)
      return p;
  return -1;
}

int lookup(std::string name, int token)
{
  for (int p = symtable.size() - 1; p > 0; p--)
    if (symtable[p].name == name && symtable[p].token == token)
      return p;
  return -1;
}

int insertPlain(symbol_t sym)
{
  symtable.push_back(sym);
  return symtable.size() - 1;
}

int insert(symbol_t sym)
{
  int look = lookup(sym.name);
  if (look >= 0)
    return look;
  return insertPlain(sym);
}

int insert(const std::string s, int tok)
{
  int look = lookup(s);
  if (look >= 0)
    return look;
  symbol_t sym;
  sym.name = s;
  sym.token = tok;
  return insertPlain(sym);
}

int insert(std::string s, int token, int type)
{
  int look = lookup(s);
  if (look >= 0)
    return look;
  symbol_t sym;
  sym.name = s;
  sym.token = token;
  sym.type = type;
  return insertPlain(sym);
}

int newTemp(int type)
{
  symbol_t t;
  t.name = "t" + std::to_string(tempCount);
  t.type = type;
  t.token = VAR;
  t.address = 0;
  int index = insertPlain(t);
  symtable[index].address = getAddress(t.name);
  ++tempCount;
  return index;
}

int newNum(std::string name, int type)
{
  return insert(name, VAL, type);
}

int REFSIZE = 4;
int NONESIZE = 0;
int INTSIZE = 4;
int REALSIZE = 8;

int sizeFromToken(int type)
{
  return type == REAL ? 8 : 4;
}

int getSymbolSize(symbol_t symbol)
{

  if (symbol.token == VAR)
  {
    if (symbol.type == INT)
      return INTSIZE;
    else if (symbol.type == REAL)
      return REALSIZE;
  }
  return NONESIZE;
}

/* look into*/
int getAddress(std::string name)
{
  int address = 0;
  for (auto sym : symtable)
  {

    if (sym.name != name)
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
        << std::setw(lenTok + 2) << token_name(symbol.token) << " "
        << std::setw(lenName + 2) << symbol.name << " "
        << std::setw(LenType + 2) << token_name(symbol.type)
        << ((symbol.type == INT) ? " " : "")
        << ((symbol.token == VAR) ? "\t" + std::to_string(symbol.address) : "")
        << std::endl;
  }
}