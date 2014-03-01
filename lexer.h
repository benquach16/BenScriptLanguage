#include <iostream>
#include <vector>
#include <string>

using namespace std;


class Lexer
{
public:
	Lexer();
	~Lexer();

	void OpenFile(char *filePath);
protected:

	vector<string> callStack;
	vector<string> fileLines;
};
