// TODO ??? what is this ??
// #define YY_NO_UNPUT

#include "cx.tab.hh"
#include "lex.hpp"
#include "numbers.hpp"
#include "parseNode.hpp"
#include "symbol.hpp"
#include "utils.hpp"

#include "globals.hpp"

struct Globals g;

static void unitTests(void) { Symbol::unitTest(); }

int main(int argc, char **argv) {
  g.yylineno = 1;
  unitTests();
  if ((argc != 2) || argv[1][0] == '-') {
    fatal("Usage: calc <filename>");
  }
  g.data = Readfile(argv[1]);
  g.curr_char = 0;

  yy::parser parse;
  int p = parse();
  if (p != 0) {
    fatal("Parser error code: %d, line %d\n", p, g.yylineno);
  }
  if (0) {
    printf("-------------------------------------\n");
    Symbol::dumpList();
    printf("-------------------------------------\n");
    ParseNode::dumpParseList();
    printf("-------------------------------------\n");
    ParseNode::dumpParseTree();
    printf("-------------------------------------\n");
  }
  ParseNode::evalParseTree();
  return 0;
}
