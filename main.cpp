#include <iostream>

using namespace std;


int main(int argc, char **argv)
{
	for(unsigned i = 0; i < argc; i++)
	{
		Lexer interpreter; 
		interpreter.FirstPass(argv[i]);
	}
	return 0;
}
