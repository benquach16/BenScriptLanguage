GCC=g++

default: lexer main

main: lexer
	$(GCC) lexer main.cpp -o Interpreter

lexer:
	$(GCC) -c lexer.cpp -o lexer.o

clean:
	rm -rf *.o Interpreter


