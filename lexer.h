#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Function
{
	string name;
	unsigned fileLine;
	vector<string> functionArguments;
};

enum VariableTypes
{
	int,
	float,
	bool,
	string
};

struct Variable
{
	string name;
	VariableTypes type;
	void* data;
};



class Lexer
{
public:
	Lexer();
	~Lexer();
	void FirstPass();
	void ReadFile(char *filePath);

	void TokenizeLine(string &str);
	void DoLine(vector<string> &line);
	void ChangeFunction(unsigned vectorIndex);
	void GetMatchingParens(unsigned leftParens, vector<string> &tokens);
	void SetupFunction(unsigned leftParens, vector<string> &tokens);
	
protected:
	int currentLine;
	vector<string> callStack;
	vector<Function> vectorOfFunctions;
	vector<string> fileLines;
	vector<Variable> variables;
};
