#include <cassert>
#include <cctype>
#include <cstring>

#include "cx.tab.hh"
#include "globals.hpp"
#include "lex.hpp"
#include "numbers.hpp"
// #include "symbol.hpp"
#include "utils.hpp"

char lex_next_char(void) {
  char out = g.data.at(g.curr_char);
  g.curr_char++;
  return out;
}

int lex_look_ahead(void) { return g.data.at(g.curr_char); }

void lex_backtrack(char c) {
  g.curr_char--;
  assert(g.data.at(g.curr_char) == c);
}

yy::parser::symbol_type lex_symbol(char c) {
  char *s = g.yytext;
  do {
    *s++ = c;
    c = lex_next_char();
  } while (!(isspace(c) || strchr("()", c)));
  lex_backtrack(c);
  *s = 0;
  
  std::string thing(g.yytext);

  return yy::parser::make_TOK_IDENTIFIER(thing);
}

yy::parser::symbol_type yylex(void) {
  char c;
  do {
    c = lex_next_char();
    if ((c == '/') && (lex_look_ahead() == '/')) {
      lex_next_char();
      do {
        c = lex_next_char();
      } while ((c != '\n') && (c != '\0'));
    }
    if (c == '\n') {
      ++g.yylineno;
    }
  } while (isspace(c));

  if (c == '\0') {
    return yy::parser::token::YYEOF;
  }

  if (strchr("()", c)) {
    return c;
  }

  char a = lex_next_char();
  if (isdigit(c) || ((c == '.') && isdigit(a))) {
    lex_backtrack(a);
    return lex_number(c);
  }
  lex_backtrack(a);
  
  return lex_symbol(c);
}
