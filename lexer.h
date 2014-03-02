#include <iostream>
#include <vector>
#include <istream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>

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

	Variable OpPlus(Variable left, Variable right);
	Variable OpMinus(Variable left, Variable right);
	Variable OpMultiply(Variable left, Variable right);
	Variable OpDivide(Variable left, Variable right);
	Variable OpMod(Variable left, Variable right);
	bool OpOr(Variable left, Variable right);
	bool OpAnd(Variable left, Variable right);
	bool OpCompare(Variable left, Variable right);
	bool OpInvCompare(Variable left, Variable right);
	Variable OpPlusPlus(Variable var, bool isLeft);
	Variable OpMinusMinus(Variable var, bool isLeft);
	Variable OpNot(Variable var);
    bool OpLess(Variable left,Variable right);
    bool OpLessEqual(Variable left,Variable right);
    bool OpGreatEqual(Variable left,Variable right);
    bool OpGreat(Variable left,Variable right);
    int numTabs(string line);
    
    
	Variable doLine(vector<string> &tokens);
	Variable split(int index, vector<string> tokens);
	Variable operatorSelect(vector<string> leftTokens, vector<string> rightTokens, string op);
	int findOperator1(vector<string> tokens);
	int findOperator2(vector<string> tokens);
	int findOperator3(vector<string> tokens);
	int findOperator4(vector<string> tokens);
	int findOperator5(vector<string> tokens);
	int findOperator6(vector<string> tokens);
	int findOperator7(vector<string> tokens);
	int findOperator8(vector<string> tokens);
	int FindPCBack(bool elseOk);
	Variable doFunction(string funcName, vector<Variable> &arguments);
	void GoThroughFunction(Function func);
	void GoThroughFunction();
 	void ChangeFunction(unsigned vectorIndex);
	int GetMatchingParens(unsigned leftParens, vector<string> &tokens);
	Variable SetupFunction(unsigned leftParens, vector<string> &tokens);
	bool MakeVarIfVar( vector<string> &tokens);
	Variable& FindValue(string name);
	Variable UpdateValue(string name, Variable var);

	unsigned currentLine;
	//important stacks
	vector<string> callStack;
	vector<Function> vectorOfFunctions;
	vector<string> fileLines;
	vector<Variable> variables;
    
};
