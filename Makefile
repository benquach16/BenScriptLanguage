GCC=g++

default: lexer main

main: lexer
	$(GCC) testmain.cpp lexer.o -o Interpreter

lexer:
	$(GCC) -c lexer.cpp -o lexer.o

clean:
	rm -rf *.o Interpreter


