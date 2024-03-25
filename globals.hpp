//
//  globals.hpp
//

#define TOK(x) yy::parser::token::TOK_##x
#define NumItems(x) ((int)(sizeof(x) / sizeof(*x)))

struct Globals {
  int fd;
  char *data;
  char *dataPtr;
  unsigned int dataSize;
  char yytext[0x100];
	class ParseNode *parseTree;
	// int topParseNodeIndex;
} extern g;

extern int yylineno;
extern char *yytext;

//extern int  parseNode(int operand, int intValue, int left, int right);
//extern void dumpParseTree(void);
//extern void dumpParseList(void);
//extern void evalParseTree(void);
