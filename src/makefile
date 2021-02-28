CPPFLAGS += -W -Wall -g 

# This avoids error: ‘fileno’ was not declared in this scope
CPPFLAGS += -std=c++0x

# Avoid warnings about yyunput not used
CPPFLAGS += -Wno-unused-function

all : compiler

compiler_lexer.yy.cpp : compiler_lexer.flex
	flex -o compiler_lexer.yy.cpp  compiler_lexer.flex

compiler : compiler_lexer.yy.o compiler_main.o
	g++ $(CPPFLAGS) -o compiler  compiler_lexer.yy.o compiler_main.o

clean :
	-rm -f compiler compiler.exe
	-rm -f *.yy.cpp
	-rm -f test/out/*
