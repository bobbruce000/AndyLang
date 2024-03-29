#include "parseTree.hpp"
#include "globals.hpp"
#include "symbol.hpp"
#include "utils.hpp"
#include <cassert>

ProgramRoot::ProgramRoot(Expression &root_expression)
    : expression{root_expression} {}
ProgramRoot::ProgramRoot() {}

Identifier::Identifier(std::string ident_name) : name{ident_name} {}
Identifier::Identifier() : name{"__BAD_UNINITILAIZED"} {}

Expression::Expression(Identifier &ident) : value{ident} {}
Expression::Expression(int integer_literal) : value{integer_literal} {}

Expression::Expression(FunctionApplication const &func)
: value{std::unique_ptr<const FunctionApplication>(new FunctionApplication(func))} {}
Expression::Expression() : value{Identifier()} {}
Expression::Expression(Expression const &other) : value{Identifier()} {
  std::visit(
      [this](const auto &var) {
        using T = std::decay_t<decltype(var)>;
        if constexpr (std::is_same_v<T, Identifier>) {
          this->value = var;
        } else if constexpr (std::is_same_v<T, int>) {
          this->value = var;
        } else if constexpr (std::is_same_v<
                                 T,
                                 std::unique_ptr<const FunctionApplication>>) {
          this->value = std::unique_ptr<const FunctionApplication>(
              new FunctionApplication(*var));
        } else {
          assert(false);
        }
      },
      other.value);
}

Expression &Expression::operator=(const Expression &other) {
  std::visit(
      [this](const auto &var) {
        using T = std::decay_t<decltype(var)>;
        if constexpr (std::is_same_v<T, Identifier>) {
          this->value = var;
        } else if constexpr (std::is_same_v<T, int>) {
          this->value = var;
        } else if constexpr (std::is_same_v<
                                 T,
                                 std::unique_ptr<const FunctionApplication>>) {
          this->value = std::unique_ptr<const FunctionApplication>(
              new FunctionApplication(*var));
        } else {
          assert(false);
        }
      },
	     other.value);
  
  return *this;
}

void ProgramRoot::printTree(void) {
  this->expression.printExpression();
  printf("\n");
}
void Expression::printExpression(void) const {
  std::visit(
      [this](const auto &var) {
        using T = std::decay_t<decltype(var)>;
        if constexpr (std::is_same_v<T, Identifier>) {
          printf("%s", std::get<0>(value).name.c_str());
        } else if constexpr (std::is_same_v<T, int>) {
          printf("%d", std::get<1>(value));
        } else if constexpr (std::is_same_v<
                                 T,
                                 std::unique_ptr<const FunctionApplication>>) {
          std::get<2>(value)->printFunctionApplication();
        } else {
          assert(false);
        }
      },
      this->value);
}
FunctionApplication::FunctionApplication(Expression &function_expr,
                                         Expression &object_expr)
    : function{function_expr}, argument{object_expr} {}

void FunctionApplication::printFunctionApplication(void) const {
  printf("(");
  this->function.printExpression();
  printf(" ");
  this->argument.printExpression();
  printf(")");
}

// int Parse::count = 1; // Node zero is unused.

// static ParseNode parseNodes[ParseNode::NumParseNodes];

// int ParseNode::node(int operand, int intValue, int left, int right) {
//   int n = ParseNode::count++;
//   assert(n < NumParseNodes);
//   parseNodes[n].operand = operand;
//   parseNodes[n].intValue = intValue;
//   parseNodes[n].left = left;
//   parseNodes[n].right = right;
//   return n;
// }

// static const char *tokenToString(int token) {
//   static const struct {
//     int t;
//     const char *s;
//   } tab[] = {
//       {'\0', "Null"},
//       {'=', "="},
//       {'+', "+"},
//       {'-', "-"},
//       {'*', "*"},
//       {'/', "/"},
//       {'%', "%"},
//       {'~', "~"},
//       {'&', "&"},
//       {'|', "|"},
//       {':', ":"},
//       {'?', "?"},
//       {'!', "!"},
//       {'<', "<"},
//       {'>', ">"},
//   };
// #define _(t, s) {TOK(t), s}
//       _(INTEGER_LITERAL, "Integer"),
//       _(PROGRAM, "Program"),
//       _(STATEMENT_LIST, "Statement-List"),
//       _(PRINT, "Print"),
//       _(ASSERT, "Assert"),
//       _(IF, "If"),
//       _(ELSE, "Else"),
//       _(SYMBOL, "Symbol"),
//       _(PLUS_EQ, "+="),
//       _(MINUS_EQ, "-="),
//       _(MULT_EQ, "*="),
//       _(DIVIDE_EQ, "/="),
//       _(MOD_EQ, "%="),
//       _(AND_EQ, "&="),
//       _(OR_EQ, "|="),
//       _(XOR_EQ, "^="),
//       _(GE, ">="),
//       _(LE, "<="),
//       _(EQ_EQ, "=="),
//       _(NOT_EQ, "!="),
//       _(LOGICAL_AND, "&&="),
//       _(LOGICAL_OR, "||="),
//       _(SHIFT_RIGHT, ">>"),
//       _(SHIFT_LEFT, "<<"),
//       _(PLUS_PLUS, "++"),
//       _(MINUS_MINUS, "--"),
// #undef _
//   };

//   for (int i = 0; i < NumItems(tab); ++i) {
//     if (tab[i].t == token) {
//       return tab[i].s;
//     }
//   }
//   fatal("Bad operand in tokenToString() {%d} {%c}", token, token);
//   return 0;
// }

// void ParseNode::dump(int depth, int n) {
//   (void) (depth + n);
//   assert(false);
//   // if (n == 0) {
//   //   return;
//   // }
//   // assert(n < NumParseNodes);
//   // assert(n < ParseNode::count);
//   // ParseNode *p = &parseNodes[n];
//   // int t = p->operand;
//   // const char *s = tokenToString(t);
//   // if (t == TOK(INTEGER_LITERAL)) {
//   //   printf("%*s%s : %d\n", 2 * depth, "", s, p->intValue);
//   // } else if (t == TOK(SYMBOL)) {
//   //   const char *snm = Symbol::getName(p->intValue);
//   //   printf("%*s%s : %s\n", 2 * depth, "", s, snm);
//   // } else {
//   //   printf("%*s%s\n", 2 * depth, "", s);
//   // }
//   // dump(depth + 1, p->left);
//   // dump(depth + 1, p->right);
// }

// void ParseNode::dumpParseTree(void) {
//   int top = ParseNode::count - 1; // FIXME

//   printf("parseNodeCount = %d\n", ParseNode::count);
//   // printf("g.topParseNodeIndex = %d\n", g.topParseNodeIndex);
//   dump(0, top);
// }

// void ParseNode::dumpParseList(void) {
//   for (int i = 0; i < ParseNode::count; ++i) {
//     printf("Node=%d, %-10s %3d L=%d R=%d\n", i,
//            tokenToString(parseNodes[i].operand), parseNodes[i].intValue,
//            parseNodes[i].left, parseNodes[i].right);
//   }
// }

// int ParseNode::getParseNodeSymbolIndex(int pn) {
//   assert(pn > 0);
//   int symbolIndex = parseNodes[pn].intValue;
//   return symbolIndex;
// }

// int ParseNode::eval(int depth, int n) {
//   (void) (depth + n);
//   assert(false);
//   // int vL;
//   // int vR;

//   // if (n == 0) {
//   //   return 0;
//   // }

//   // // printf("%*seval(%d) d=%d\n", 2*depth, "", n, depth);

//   // assert(n < NumParseNodes);
//   // assert(n < ParseNode::count);
//   // ParseNode *p = &parseNodes[n];

//   // if (p->operand == TOK(ELSE)) {
//   //   ParseNode *pl = &parseNodes[p->left];
//   //   assert(pl->operand == TOK(IF));
//   //   if (eval(depth + 1, pl->left)) {
//   //     eval(depth + 1, pl->right);
//   //   } else {
//   //     eval(depth + 1, p->right);
//   //   }
//   //   return 0;
//   // }

//   // if (p->operand == TOK(IF)) {
//   //   vL = eval(depth + 1, p->left);
//   //   if (vL) {
//   //     eval(depth + 1, p->right);
//   //   }
//   //   return 0;
//   // }
//   // vL = eval(depth + 1, p->left);
//   // vR = eval(depth + 1, p->right);
//   // switch (p->operand) {
//   // case TOK(INTEGER_LITERAL):
//   //   return p->intValue;
//   // case TOK(SYMBOL):
//   //   return Symbol::getValue(p->intValue);
//   // case TOK(PROGRAM):
//   //   return 0;
//   // case TOK(STATEMENT_LIST):
//   //   return 0;
//   // case TOK(PRINT):
//   //   printf("Print: %d\n", vL);
//   //   return 0;
//   // case TOK(ASSERT):
//   //   if (!vL)
//   //     printf("Assert failed, line %d\n", p->intValue);
//   //   return 0; // intValue is the linenum
//   // case TOK(PLUS_EQ):
//   //   return 0;
//   // case TOK(MINUS_EQ):
//   //   return 0;
//   // case TOK(MULT_EQ):
//   //   return 0;
//   // case TOK(DIVIDE_EQ):
//   //   return 0;
//   // case TOK(MOD_EQ):
//   //   return 0;
//   // case TOK(AND_EQ):
//   //   return 0;
//   // case TOK(OR_EQ):
//   //   return 0;
//   // case TOK(XOR_EQ):
//   //   return 0;
//   // case TOK(GE):
//   //   return vL >= vR;
//   // case TOK(LE):
//   //   return vL <= vR;
//   // case TOK(EQ_EQ):
//   //   return vL == vR;
//   // case TOK(NOT_EQ):
//   //   return vL != vR;
//   // case TOK(LOGICAL_AND):
//   //   return vL && vR;
//   // case TOK(LOGICAL_OR):
//   //   return vL || vR;
//   // case TOK(SHIFT_RIGHT):
//   //   return vL >> vR;
//   // case TOK(SHIFT_LEFT):
//   //   return vL << vR;
//   // case TOK(PLUS_PLUS):
//   //   return p->left ? vL + 1 : vR + 1;
//   // case TOK(MINUS_MINUS):
//   //   return p->left ? vL - 1 : vR - 1;

//   // case '=': {
//   //   int n = getParseNodeSymbolIndex(p->left);
//   //   Symbol::setValue(n, vR);
//   //   return vR;
//   // }
//   // case '?': {
//   //   ParseNode *pr = &parseNodes[p->right];
//   //   /*
//   //   printf("### n=%d, vL=%d, vR=%d, p->left = %d, p->right = %d\n",
//   //                            n, vL, vR, p->left, p->right);

//   //   printf("pr->left =%d\n", pr->left);
//   //   printf("pr->right=%d\n", pr->right);

//   //   printf("eval(pr->left) =%d\n", eval(pr->left));
//   //   printf("eval(pr->right)=%d\n", eval(pr->right));
//   //   */

//   //   return vL ? eval(depth + 1, pr->left) : eval(depth + 1, pr->right);
//   // }

//   // case ':':
//   //   return 0;
//   // case '+':
//   //   return vL + vR;
//   // case '*':
//   //   return vL * vR;
//   // case '/':
//   //   return vL / vR;
//   // case '%':
//   //   return vL % vR;
//   // case '~':
//   //   return ~vR;
//   // case '!':
//   //   return !vR;
//   // case '&':
//   //   return vL & vR;
//   // case '|':
//   //   return vL | vR;
//   // case '<':
//   //   return vL < vR;
//   // case '>':
//   //   return vL > vR;
//   // case '-':
//   //   return (p->right == 0) ? -vR : vL - vR;
//   // default:
//   //   fatal("Bad operand in eval(): %d {%c}", p->operand, p->operand);
//   // }
//   // return 0;
// }

// void ParseNode::evalParseTree(void) {
//   int top = ParseNode::count - 1;
//   eval(0, top);
// }
