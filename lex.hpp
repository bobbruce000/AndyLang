#include "cx.tab.hh"

char lex_next_char(void);
void lex_backtrack(char c);
yy::parser::symbol_type yylex();
