%require "3.2"
%language "c++"
%define api.value.type variant
%define api.token.constructor
%{
#include <stdio.h>
#include <stdlib.h>
#include "globals.hpp"
#include "parseNode.hpp"	
#include "lex.hpp"
#define PN ParseNode::node	
%}

/* %union{ */
/*    int		int_val;  */
/*    char *op_val;  */
/* }  */

%start	program

%token	<int>	TOK_INTEGER_LITERAL
%token	<int>	TOK_SYMBOL
%token  TOK_PROGRAM
%token  TOK_PRINT
%token  TOK_ASSERT
%token  TOK_PLUS_EQ
%token  TOK_MINUS_EQ
%token  TOK_MULT_EQ
%token  TOK_DIVIDE_EQ
%token  TOK_MOD_EQ
%token  TOK_AND_EQ
%token  TOK_OR_EQ
%token  TOK_XOR_EQ
%token  TOK_GE
%token  TOK_LE
%token  TOK_EQ_EQ
%token  TOK_NOT_EQ
%token  TOK_LOGICAL_AND
%token  TOK_LOGICAL_OR
%token  TOK_SHIFT_RIGHT
%token  TOK_SHIFT_LEFT
%token  TOK_PLUS_PLUS
%token  TOK_MINUS_MINUS

%type  <int>	program
%type  <int>	statement
%type  <int>	assignment_statement
%type  <int>	print_statement
%type  <int>	assert_statement
%type  <int>	expression
%type  <int>  ternary_exp
%type  <int>  logical_or_exp
%type  <int>  logical_and_exp
%type  <int>  bitwise_or_exp
%type  <int>  bitwise_xor_exp
%type  <int>  bitwise_and_exp
%type  <int>  equality_exp
%type  <int>	compare_exp
%type  <int>  shift_exp
%type  <int>	add_exp
%type  <int>	mult_exp
%type  <int>  prefix_exp
%type  <int>  postfix_exp
%type  <int>	primary_exp
%type  <int>	symbol

%left '+'
%left '-'
%left	'/'
%left	'%'
%left	'*'

%%

program: /* empty */ { $$ = PN(TOK(PROGRAM), 0, 0, 0); }
| statement program  { $$ = PN(TOK(PROGRAM), 0, $1, $2); }
;

statement:
  print_statement       { $$ = $1; }
| assert_statement      { $$ = $1; }
| assignment_statement  { $$ = $1; }
;

print_statement:      TOK_PRINT  '(' expression ')' ';' { $$ = PN(TOK(PRINT), 0, $3, 0); };
assert_statement:     TOK_ASSERT '(' expression ')' ';' { $$ = PN(TOK(ASSERT), yylineno, $3, 0); };
assignment_statement: symbol '='     expression     ';' { $$ = PN('=', 0, $1, $3); };
  
expression: ternary_exp { $$ = $1; };

ternary_exp:  logical_or_exp                            { $$ = $1; }
| logical_or_exp '?' logical_or_exp ':' logical_or_exp  { $$ = PN('?', 0, ($1), PN(':', 0, $3, $5)); }
;

logical_or_exp: logical_and_exp                  { $$ = $1; }
| logical_and_exp TOK_LOGICAL_OR bitwise_xor_exp { $$ = PN(TOK(LOGICAL_OR), 0, $1, $3); }

logical_and_exp: bitwise_or_exp                 { $$ = $1; }
| bitwise_or_exp TOK_LOGICAL_AND bitwise_or_exp { $$ = PN(TOK(LOGICAL_AND), 0, $1, $3); }

bitwise_or_exp: bitwise_xor_exp       { $$ = $1; }
| bitwise_xor_exp '|' bitwise_xor_exp { $$ = PN('|', 0, $1, $3); }
;

bitwise_xor_exp: bitwise_and_exp       { $$ = $1; }
| bitwise_and_exp '^' bitwise_and_exp  { $$ = PN('^', 0, $1, $3); }
;

bitwise_and_exp: equality_exp    { $$ = $1; }
| equality_exp '&' equality_exp	 { $$ = PN('&', 0, $1, $3); }
;

equality_exp: compare_exp  { $$ = $1; }
| shift_exp TOK_EQ_EQ  shift_exp  { $$ = PN(TOK(EQ_EQ), 0, $1, $3); }
| shift_exp TOK_NOT_EQ shift_exp  { $$ = PN(TOK(NOT_EQ), 0, $1, $3); }
;

compare_exp: shift_exp          { $$ = $1; }
| shift_exp '<' shift_exp       { $$ = PN('<', 0, $1, $3); }
| shift_exp '>' shift_exp       { $$ = PN('>', 0, $1, $3); }
|	shift_exp TOK_GE shift_exp    { $$ = PN(TOK(GE), 0, $1, $3); }
| shift_exp TOK_LE shift_exp    { $$ = PN(TOK(LE), 0, $1, $3); }
;

shift_exp: add_exp                { $$ = $1; }
| add_exp TOK_SHIFT_LEFT  add_exp { $$ = PN(TOK(SHIFT_LEFT),  0, $1, $3); }
| add_exp TOK_SHIFT_RIGHT add_exp { $$ = PN(TOK(SHIFT_RIGHT), 0, $1, $3); }
;

add_exp:  mult_exp          { $$ = $1; }
| mult_exp '+' mult_exp     { $$ = PN('+', 0, $1, $3); }
| mult_exp '-' mult_exp     { $$ = PN('-', 0, $1, $3); }
;

mult_exp:  prefix_exp
| prefix_exp '*' prefix_exp	{ $$ = PN('*', 0, $1, $3); }
| prefix_exp '/' prefix_exp	{ $$ = PN('/', 0, $1, $3); }
| prefix_exp '%' prefix_exp	{ $$ = PN('%', 0, $1, $3); }
;

prefix_exp: postfix_exp       { $$ = $1; }
| TOK_PLUS_PLUS   postfix_exp { $$ = PN(TOK(PLUS_PLUS),   0, 0, $2); }
| TOK_MINUS_MINUS postfix_exp { $$ = PN(TOK(MINUS_MINUS), 0, 0, $2); }
| '!' postfix_exp             { $$ = PN('!', 0, 0, $2); }
| '-' postfix_exp             { $$ = PN('-', 0, 0, $2); }
| '~' postfix_exp             { $$ = PN('~', 0, 0, $2); }
;

postfix_exp: primary_exp      { $$ = $1; }
| primary_exp TOK_PLUS_PLUS   { $$ = PN(TOK(PLUS_PLUS), 0, $1, 0); }
| primary_exp TOK_MINUS_MINUS { $$ = PN(TOK(MINUS_MINUS), 0, $1, 0); }
;

primary_exp:
  TOK_INTEGER_LITERAL { $$ = PN(TOK(INTEGER_LITERAL), $1, 0, 0); }
| symbol              { $$ = $1; }
| '(' expression ')'  { $$ = $2; }
;

symbol: TOK_SYMBOL    { $$ = PN(TOK(SYMBOL), $1, 0, 0); };

%%

auto yy::parser::error (const std::string& msg) -> void
{
  std::cerr << "error at line " << yylineno << " msg: " << msg  << '\n';
}
