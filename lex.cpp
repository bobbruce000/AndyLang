#include <cassert>
#include <cctype>
#include <cstring>

#include "cx.tab.hh"
#include "globals.hpp"
#include "lex.hpp"
#include "numbers.hpp"
#include "symbol.hpp"
#include "utils.hpp"

int lex_next_char(void) {
  char out = g.data.at(g.curr_char);
  g.curr_char++;
  return out;
}

static int lex_look_ahead(void) { return g.data.at(g.curr_char); }

void lex_backtrack(int c) {
  g.curr_char--;
  assert(g.data.at(g.curr_char) == c);
}

yy::parser::symbol_type lex_symbol(int c) {
  struct {
    const char *keyword;
    yy::parser::token::token_kind_type token;
  } keywords[] = {
      {"if", TOK(IF)},
      {"else", TOK(ELSE)},
      {"Assert", TOK(ASSERT)},
      {"Print", TOK(PRINT)},
  };
  char *s = g.yytext;
  do {
    *s++ = c;
    c = lex_next_char();
  } while ((c == '_') || isalnum(c));
  lex_backtrack(c);
  *s = 0;
  for (int i = 0; i < NumItems(keywords); ++i) {
    if (strcmp(g.yytext, keywords[i].keyword) == 0) {
      return keywords[i].token;
    }
  }
  int n = Symbol::newIndex(g.yytext);
  return yy::parser::make_TOK_SYMBOL(n);
}

yy::parser::symbol_type yylex(void) {
  int c;
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

  int a = lex_next_char();

  if (a == '=') {
    switch (c) {
    case '=':
      return TOK(EQ_EQ);
    case '!':
      return TOK(NOT_EQ);
    case '+':
      return TOK(PLUS_EQ);
    case '-':
      return TOK(MINUS_EQ);
    case '*':
      return TOK(MULT_EQ);
    case '/':
      return TOK(DIVIDE_EQ);
    case '%':
      return TOK(MOD_EQ);
    case '&':
      return TOK(AND_EQ);
    case '|':
      return TOK(OR_EQ);
    case '^':
      return TOK(XOR_EQ);
    case '>':
      return TOK(GE);
    case '<':
      return TOK(LE);
    default:
      break;
    }
  }

  if (a == c) {
    switch (c) {
    case '=':
      return TOK(EQ_EQ);
    case '+':
      return TOK(PLUS_PLUS);
    case '-':
      return TOK(MINUS_MINUS);
    case '&':
      return TOK(LOGICAL_AND);
    case '|':
      return TOK(LOGICAL_OR);
    case '>':
      return TOK(SHIFT_RIGHT);
    case '<':
      return TOK(SHIFT_LEFT);
    default:
      break;
    }
  }
  lex_backtrack(a);
  if (strchr("!<>(){}[];=+-*/%~&|:?", c)) {
    return c;
  }
  if (isdigit(c) || ((c == '.') && isdigit(a))) {
    return lex_number(c);
  }
  if ((c == '_') || isalpha(c)) {
    return lex_symbol(c);
  }

  return yy::parser::token::YYerror;
}
