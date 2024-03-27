#include <vector>

#define TOK(x) yy::parser::token::TOK_##x
#define NumItems(x) ((int)(sizeof(x) / sizeof(*x)))

struct Globals {
  int fd;
  std::vector<char> data;
  int curr_char;
  char yytext[0x100];
  class ParseNode *parseTree;
  int yylineno;
} extern g;
