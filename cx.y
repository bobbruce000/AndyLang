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
%token	<Identifier>   TOK_IDENTIFIER

%type  <Expression> function_application
%type  <Expression> expression


%%
program: expression { g.parseTree = new ProgramRoot($1); };

expression:
  TOK_IDENTIFIER        { $$ = Expression($1); }
| TOK_INTEGER_LITERAL   { $$ = Expression($1); }
| function_application  { $$ = $1; }

function_application:
'(' expression expression ')'  { $$ = Expression(FunctionApplication($2, $3)); }
%%

void yy::parser::error (const std::string& msg)
{
  std::cerr << "error at line " << g.yylineno << " msg: " << msg  << '\n';
}
