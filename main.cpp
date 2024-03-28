#include "cx.tab.hh"
#include "lex.hpp"
#include "numbers.hpp"
#include "symbol.hpp"
#include "parseTree.hpp"
#include "utils.hpp"

#include "globals.hpp"

struct Globals g{
  .data = std::vector<char>(),
  .curr_char = 0,
  .yytext = {},
  .parseTree = nullptr,
  .yylineno = 1
};

static void unitTests(void) { Symbol::unitTest(); }

int main(int argc, char **argv) {
  unitTests();
  if ((argc != 2) || argv[1][0] == '-') {
    fatal("Usage: calc <filename>");
  }
  g.data = Readfile(argv[1]);

  
  yy::parser parse;
  //parse.set_debug_level(1);
  int p = parse();
  
  if (p != 0) {
    fatal("Parser error code: %d, line %d\n", p, g.yylineno);
  }

  //Symbol::dumpList();
  printf("-------------------------------------\n");
  g.parseTree->printTree();
  printf("-------------------------------------\n");
  //ParseNode::dumpParseTree();
  printf("-------------------------------------\n");
  
  //ParseNode::evalParseTree();
  return 0;
}
