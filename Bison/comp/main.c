#include "global.h"
#include "parser.h"
int main()
{
  yyparse();
  yylex_destroy();
  exit(0);
}
