#include <iostream>
#include <vector>
#include <istream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;


enum VariableTypes
{
	INT,
	FLOAT,
	BOOL,
	STRING
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

struct Variable
{
	string name;
	VariableTypes type;
	void* data;
};


struct Function
{
	string name;
	unsigned fileLine;
	vector<Variable> functionArguments;
};



//lexer class code
class Lexer
{
public:
	Lexer();
	~Lexer();
	void FirstPass();
	void ReadFile(char *filePath);

	vector<string> TokenizeLine(const string &str);

	Variable doLine(vector<string> &tokens);
	Variable split(int index, vector<string> tokens);
	Variable operatorSelect(vector<string> left, vector<string> right, string op);
	int findOperator1(vector<string> tokens);
	int findOperator2(vector<string> tokens);
	int findOperator3(vector<string> tokens);
	int findOperator4(vector<string> tokens);
	int findOperator5(vector<string> tokens);
	int findOperator6(vector<string> tokens);
	int findOperator7(vector<string> tokens);

 	void ChangeFunction(unsigned vectorIndex);
	int GetMatchingParens(unsigned leftParens, vector<string> &tokens);
	vector<int> SetupFunction(unsigned leftParens, vector<string> &tokens);
	bool MakeVarIfVar( vector<string> &tokens);

	unsigned currentLine;
	//important stacks
	vector<string> callStack;
	vector<Function> vectorOfFunctions;
	vector<string> fileLines;
	vector<Variable> variables;
    
};
