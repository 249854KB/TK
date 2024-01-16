#include "global.h"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char **argv)
{

  initSymtable();
  yyparse();

  if (errorno == 0)
  {
    cout << endl
         << "Kompilacja udana!!" << endl;
    cout << "Tabela symboli:" << endl;
    printSymtable();
    string outfname = "program.asm";

    cout << endl
         << "Kod w assemblerze:" << endl
         << endl;

    exportAsm(outfname);
  }
  else
  {
    cout << endl
         << "\nZnaleziono błąd!!";
  }

  yylex_destroy();
};