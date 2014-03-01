#include <iostream>
#include "lexer.h"

using namespace std;


int main(int argc, char **argv)
{
	for (unsigned i = 1; i < argc; i++)
	{
		Lexer interpreter;
        vector<string> myvec; 
        //~ myvec.push_back("int"); 
        //~ myvec.push_back("fuxkthis");
        //~ cout << interpreter.MakeVarIfVar(myvec);
		interpreter.ReadFile(argv[i]);
        interpreter.FirstPass();
        //cout << interpreter.vectorOfFunctions[0].fileLine << endl;
        for(int i=0; i < interpreter.vectorOfFunctions.size();i++)
            for(int j=0; j < interpreter.vectorOfFunctions[i].functionArguments.size(); j++)
                cout << interpreter.vectorOfFunctions[i].functionArguments[j].name << endl;
        cout << interpreter.variables.size()<< endl;
	}
	return 0;
}
