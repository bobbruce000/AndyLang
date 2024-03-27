#include <cassert>
#include <cstdio>
#include <cstring>

#include "globals.hpp"
#include "symbol.hpp"
#include "utils.hpp"

int Symbol::numSymbols = 0;
static Symbol symbolTable[Symbol::MaxNumSymbols];

int Symbol::getIndex(const char *symbolName) {
  for (int i = 0; i < numSymbols; ++i) {

    // printf("i = %d, symbolName={%s}\n", i, symbolName);

    assert(symbolTable[i].name != NULL);

    if (strcmp(symbolTable[i].name, symbolName) == 0) {
      return i;
    }
  }
  return -1;
}

int Symbol::newIndex(const char *symbolName) {

  // printf("symbolName={%s}\n", symbolName);

  int n = getIndex(symbolName);
  if (n < 0) {
    n = numSymbols++;
    assert(n < MaxNumSymbols);
    symbolTable[n].name = strdup(symbolName);
  }
  return n;
}

const char *Symbol::getName(int n) {
  assert(n < numSymbols);
  return symbolTable[n].name;
}

int Symbol::getValue(int n) {
  assert(n < numSymbols);
  return symbolTable[n].intValue;
}

void Symbol::setValue(int n, int value) {
  // printf("setSymbolValue(%d, %d) ns=%d\n", n, value, numSymbols);
  assert(n < numSymbols);
  symbolTable[n].intValue = value;
}

void Symbol::dumpList(void) {
  printf("numSymbols = %d\n", numSymbols);
  for (int i = 0; i < numSymbols; ++i) {
    printf("Symbol %d  %-6s %3d\n", i, symbolTable[i].name,
           symbolTable[i].intValue);
  }
}

void Symbol::unitTest(void) {
  int a = newIndex("A");
  int b = newIndex("B");
  int c = newIndex("C");
  assert(numSymbols == 3);
  setValue(a, 23);
  setValue(b, 25);
  setValue(c, 27);
  assert(getValue(a) == 23);
  assert(getValue(b) == 25);
  assert(getValue(c) == 27);
  assert(newIndex("A") == 0);
  assert(newIndex("B") == 1);
  assert(newIndex("C") == 2);
  assert(numSymbols == 3);
  numSymbols = 0;
  memset((char *)symbolTable, '\0', sizeof(symbolTable));
}
