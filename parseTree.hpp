#pragma once
#include <memory>
#include <string>
#include <variant>
#include <vector>

class FunctionApplication;

class Identifier {
public:
  Identifier();
  Identifier(std::string ident_name);
  std::string name;
  
};

class Expression {
public:
  Expression();
  Expression(Identifier &ident);
  Expression(int integer_literal);
  Expression(FunctionApplication const& func);
  void printExpression(void) const;
  Expression(Expression const& copy);
  Expression& operator=(const Expression& other);
private:
  std::variant<Identifier, int, std::unique_ptr<const FunctionApplication>> value;
  //static void dump(int depth, int n);
  //static int eval(int depth, int n);
};

class FunctionApplication {
public:
  FunctionApplication();
  //FunctionApplication(FunctionApplication& copy);
  FunctionApplication(Expression &function_expr, Expression &object_expr);
  void printFunctionApplication(void) const;
private:
  Expression function;
  Expression argument;
};

class ProgramRoot {
public:
  ProgramRoot();
  ProgramRoot(Expression &root_expression);
  void printTree(void);
private:
  Expression expression;
};



