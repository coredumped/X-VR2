#LEX=flex
#YACC=bison

all: config-lexer.o config-parser.o

config-lexer.o: config-lexer.cpp config-parser.h
	g++ $(CFLAGS) -I../../../common -I../../../util/src -I.. -c -o config-lexer.o config-lexer.cpp

config-parser.o: config-parser.cpp 
	g++ $(CFLAGS) -I../../../common -I../../../util/src -I.. -c -o config-parser.o config-parser.cpp

config-lexer.cpp: config.lex
	$(LEX) -P__xvr2_cfg_yy -oconfig-lexer.cpp config.lex

config-parser.cpp: config.y
	$(YACC) -p__xvr2_cfg_yy -d -oconfig-parser.cpp config.y
	@mv -f config-parser.hpp config-parser.h

config-parser.h: config.y
	$(YACC) -p__xvr2_cfg_yy -d -oconfig-parser.cpp config.y
	@mv -f config-parser.hpp config-parser.h

clean:
	@rm -vf config-lexer.cpp config-parser.cpp config-parser.h *.o

rebuild: clean all
