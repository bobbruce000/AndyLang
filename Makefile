CXX := clang++
CXXFLAGS := -std=c++23
CXXFLAGS += -g 
CXXFLAGS += -Wall -Wextra -Wpedantic -Weffc++
CXXFLAGS += -Werror

#bison catches exceptions in yylex() which messes up the backtrace, so just make them all crash so we can see where the errors come from
CXXFLAGS += -fno-exceptions 


BFLAGS += --header -Wcounterexamples

OBJS = main.o lex.o cx.tab.o numbers.o utils.o parseTree.o symbol.o
HDRS = *.hpp cx.tab.hh

cx: ${OBJS}
	${CXX} ${CXXFLAGS} $^ -o $@

main.o: main.cpp ${HDRS}
lex.o: lex.cpp ${HDRS}
numbers.o: numbers.cpp ${HDRS}
utils.o: utils.cpp ${HDRS}
parseTree.o: parseTree.cpp ${HDRS}
symbol.o: symbol.cpp ${HDRS}

cx.tab.o: cx.tab.cc ${HDRS}
	${CXX} ${CXXFLAGS} -Wno-unused-but-set-variable -c $<

cx.tab.hh cx.tab.ch : cx.y
	bison ${BFLAGS} $^

clean:
	rm -f cx cx.tab.cc cx.tab.hh ${OBJS}
