#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Function
{
	string name;
	unsigned fileLine;
	vector<Variable> functionArguments;
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

enum OperatorTypes
{
	//arthemetic operators
	ADD,
	SUBTRACT,
	MULTIPLY,
	DIVIDE,
	MODULO,
	//assignment and comparison operators
	ASSIGN,
	EQUALS,
	NOT,
	NOTEQUALS,
	GREATERTHAN,
	LESSTHAN
};


//lexer class code
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
	unsigned currentLine;
	//important stacks
	vector<string> callStack;
	vector<Function> vectorOfFunctions;
	vector<string> fileLines;
	vector<Variable> variables;
};
