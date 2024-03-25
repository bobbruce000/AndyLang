//
//  parseNode.hpp
//

class ParseNode {
public:
	static constexpr int NumParseNodes = 1024;
	static int count;

	int operand;
	int intValue;
	int left;  // Index of left  child ParseNode
	int right; // Index of right child ParseNode


	static int  node(int operand, int intValue, int left, int right);
	static void dumpParseTree(void);
	static void dumpParseList(void);
	static int  getParseNodeSymbolIndex(int pn);
	static void evalParseTree(void);

private:
	static void dump(int depth, int n);
	static int  eval(int n);
};
