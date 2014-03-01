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
        //cout << interpreter.vectorOfFunctions[0].fileLine << endl;
        for(int i=0; i < interpreter.vectorOfFunctions.size();i++)
            //for(int j=0; j < interpreter.vectorOfFunctions[i].functionArguments.size(); j++)
                cout << interpreter.vectorOfFunctions[i].functionArguments.size() << endl;

	}
	return 0;
}
