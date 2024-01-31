#include "global.h"

#define returnop(str, ret) \
  if (yytext == str)       \
    return ret;

int getOperationToken(std::string yytext)
{
  returnop("+", ADD);
  returnop("-", SUB);
  returnop("*", MUL);
  returnop("div", DIV);
  returnop("/", DIV);
  returnop("mod", MOD);

  returnop("and", AND);
  returnop("or", OR_tok);

  returnop("=", E);
  returnop(">", G);
  returnop(">=", GE);
  returnop("<", L);
  returnop("<=", LE);

  return -1;
}
