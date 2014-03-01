#include <iostream>
#include "lexer.h"

using namespace std;


int main(int argc, char **argv)
{
	for (unsigned i = 0; i < argc; i++)
	{
		Lexer interpreter;
		interpreter.ReadFile(argv[i]);
        interpreter.FirstPass();
        cout << interpreter.vectorOfFunctions.size() << endl;
        //cout << interpreter.vectorOfFunctions[0].functionArguments.size() << endl;

	}
	return 0;
}
