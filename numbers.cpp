#include <cctype>
#include <cstdlib>

#include "cx.tab.hh"
#include "globals.hpp"
#include "lex.hpp"
#include "numbers.hpp"
#include "utils.hpp"

yy::parser::symbol_type
lex_hex_number(void) {
  char *s = g.yytext;
  for (;;) {
    int c = lex_next_char();
    if (isdigit(c) || (islower(c) && (c <= 'f')) || (isupper(c) && (c < 'G'))) {
      *s++ = c;
      continue;
    }
    if (isalnum(c)) {
      fatal("Bad hex digit: (%c)");
    }
    lex_backtrack(c);
    *s = '\0';
    // yylval.int_val = strtol(yytext, NULL, 16);
    return yy::parser::make_TOK_INTEGER_LITERAL(strtol(yytext, NULL, 16));
  }
}

yy::parser::symbol_type lex_octal_number(void) {
  char *s = g.yytext;
  for (;;) {
    int c = lex_next_char();
    if (isdigit(c)) {
      if (c <= '7') {
        fatal("Bad octal digit: (%c)", c);
      }
      *s++ = c;
      continue;
    }
    lex_backtrack(c);
    *s = '\0';
    return yy::parser::make_TOK_INTEGER_LITERAL(strtol(yytext, NULL, 8));
  }
}

yy::parser::symbol_type lex_number(int c) {
  // int is_float = 0;
  char *s = g.yytext;
  *s++ = c;
  if (c == '.') {
    fatal("Floats not supported yet.");
  }
  if (c == '0') {
    int b = lex_next_char();
    switch (b) {
    case 'x':
      return lex_hex_number();
    case 'o':
      return lex_octal_number();
    default:
      break;
    }
    lex_backtrack(b);
  }
  for (;;) {
    c = lex_next_char();
    if (isdigit(c)) {
      *s++ = c;
    } else {
      if (c == '.') {
        fatal("Floats not supported yet.");
      }
      lex_backtrack(c);
      *s = '\0';
      return yy::parser::make_TOK_INTEGER_LITERAL(atoi(yytext));
    }
  }
}
#if 0
	char *s = scan_buf;
	if (c == '0') {
		int b = get_next_char();
		switch (b) {
		case 'x': return scan_hex_number();
		case 'o': return scan_octal_number();
		default: break;
		}
		backtrack(b);
	}
	do {
		*s++ = c;
		c = get_next_char();
	} while (isdigit(c));
	if (c != '.') {
		backtrack(c);
		*s = 0;
		return TOK_INTEGER;
	}
	do {
		*s++ = c;
		c = get_next_char();
	} while (isdigit(c));
	*s = 0;
	return TOK_FLOAT;
#endif
