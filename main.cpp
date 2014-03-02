#include <iostream>
#include "lexer.h"

using namespace std;


int main(int argc, char **argv)
{
	for(unsigned i = 1; i < argc; i++)
	{
		Lexer interpreter; 
		interpreter.ReadFile(argv[i]);
		interpreter.FirstPass();
		vector<Variable> args;
		//interpreter.doFunction("main", args);
		//interpreter.FirstPass(argv[i]);
	}
	return 0;
}
