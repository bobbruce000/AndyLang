%require "3.2"
%language "c++"
%define api.value.type variant
%define api.token.constructor
%define parse.assert
%define parse.error verbose
%debug
%code requires {
#include "parseTree.hpp"	
}
%{
#include <cstdio>
#include <cstdlib>
#include "globals.hpp"
#include "parseTree.hpp"	
#include "lex.hpp"
%}

%start	program

%token	<int>	TOK_INTEGER_LITERAL
%token	<LeafIdentifier>   TOK_IDENTIFIER

%type  <NodeExpressionListAtLeastOne> at_least_one_expression_list
%type  <NodeExpression> expression


%%

program: expression { g.parseTree = new NodeProgramRoot($1); };

expression:
  TOK_IDENTIFIER                        { $$ = NodeExpression($1); }
| TOK_INTEGER_LITERAL                   { $$ = NodeExpression($1); }
| '(' at_least_one_expression_list ')'  { $$ = NodeExpression($2); }

at_least_one_expression_list:
  expression                              { $$ = NodeExpressionListAtLeastOne($1); }
| at_least_one_expression_list expression { $$ = NodeExpressionListAtLeastOne($1, $2); }
	
%%

void yy::parser::error (const std::string& msg)
{
  std::cerr << "error at line " << g.yylineno << " msg: " << msg  << '\n';
}
