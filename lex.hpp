#include "cx.tab.hh"

int lex_next_char(void);
void lex_backtrack(int c);
yy::parser::symbol_type yylex();
