GCC=g++ -g

default: lexer main

main: lexer
	$(GCC) main.cpp lexer.o -o Interpreter.exe

lexer:
	$(GCC) -c lexer.cpp -o lexer.o

clean:
	rm -rf *.o Interpreter
