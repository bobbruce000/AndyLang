//
//  symbol.hpp
//

class Symbol {
public:
  static constexpr int MaxNumSymbols = 1024;
  static int numSymbols;

  const char *name;
  int intValue;

  static void unitTest(void);
  static void dumpList(void);
  static int newIndex(const char *symbolName);
  static int getIndex(const char *symbolName);
  static const char *getName(int n);
  static int getValue(int n);
  static void setValue(int n, int value);
};
