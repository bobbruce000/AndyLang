#pragma once
#include <string>
#include <variant>
#include <vector>

class NodeExpression;

class NodeExpressionListAtLeastOne {
public:
  NodeExpressionListAtLeastOne();
  NodeExpressionListAtLeastOne(NodeExpression &first);
  NodeExpressionListAtLeastOne(NodeExpressionListAtLeastOne &rest,
                               NodeExpression last);
  void printExpressionList(void);
private:
  std::vector<NodeExpression> list;
};

class LeafIdentifier {
public:
  LeafIdentifier();
  LeafIdentifier(std::string ident_name);
  //LeafIdentifier(LeafIdentifier const& copy);
  std::string name;
  //LeafIdentifier& operator=(const LeafIdentifier&);
};

class NodeExpression {
public:
  NodeExpression();
  NodeExpression(LeafIdentifier &ident);
  NodeExpression(int integer_literal);
  NodeExpression(NodeExpressionListAtLeastOne &list);
  void printExpression(void);
  
private:
  std::variant<LeafIdentifier, int, NodeExpressionListAtLeastOne> value;
  //static void dump(int depth, int n);
  //static int eval(int depth, int n);
};

class NodeProgramRoot {
public:
  NodeProgramRoot();
  NodeProgramRoot(NodeExpression &root_expression);
  void printTree(void);
private:
  NodeExpression expression;
};



