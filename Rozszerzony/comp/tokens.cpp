#include "global.h"

int getOperationToken(std::string yytext)
{
  if (yytext == "+")
    return ADD;
  else if (yytext == "-")
    return SUB;
  else if (yytext == "*")
    return MUL;
  else if (yytext == "/" || yytext == "div")
    return DIV;
  else if (yytext == "mod")
    return MOD;

  return -1;
}
