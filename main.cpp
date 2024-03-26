// TODO ??? what is this ??
// #define YY_NO_UNPUT

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include "cx.tab.hh"
#include "lex.hpp"
#include "numbers.hpp"
#include "symbol.hpp"
#include "parseNode.hpp"
#include "utils.hpp"

#include "globals.hpp"

struct Globals g;

int yylineno = 1;
char *yytext;

static void
unitTests(void)
{
	Symbol::unitTest();
}

int
main(int argc, char **argv)
{
	unitTests();
  if ((argc != 2) || argv[1][0] == '-') {
    fatal("Usage: calc <filename>");
  }
  g.data = Readfile(argv[1], &g.dataSize);
  g.dataPtr = g.data;
  yytext = g.yytext;

  yy::parser parse;
	int p = parse();
	if (p != 0) {
		fatal("Parser error code: %d, line %d\n", p, yylineno);
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
