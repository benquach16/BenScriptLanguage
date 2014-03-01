#include <iostream>
#include <vector>
#include "lexer.h"

using namespace std;

int Lexer::findOperator1(vector <string> tokens)
{
  int parens = 0;
  for(int i = 0; i < tokens.size(); i++)
  {
    if(tokens.at(i) == "(")
      parens++;

    else if(tokens.at(i) == ")")
      parens--;

    //cerr << "parens: " << parens << endl;

    if(parens == 0 && (tokens.at(i) == "+=" || tokens.at(i) == "-=" || 
		       tokens.at(i) == "*=" || tokens.at(i) == "/=" || 
		       tokens.at(i) == "=" || tokens.at(i) == "%="))
      return i;
  }
  return -1;
}

// checks or
int Lexer::findOperator2(vector <string> tokens)
{
  int parens = 0;
  for(int i = 0; i < tokens.size(); i++)
  {
    if(tokens.at(i) == "(")
      parens++;

    else if(tokens.at(i) == ")")
      parens--;

    if(parens == 0 && tokens.at(i) == "||")
      return i;
  }
  return -1;
}

// checks and
int Lexer::findOperator3(vector <string> tokens)
{
  int parens = 0;
  for(int i = 0; i < tokens.size(); i++)
  {
    if(tokens.at(i) == "(")
      parens++;

    else if(tokens.at(i) == ")")
      parens--;

    if(parens == 0 && tokens.at(i) == "&&")
      return i;
  }
  return -1;
}

// checks equality comparison
int Lexer::findOperator4(vector <string> tokens)
{
  int parens = 0;
  for(int i = 0; i < tokens.size(); i++)
  {
    if(tokens.at(i) == "(")
      parens++;

    else if(tokens.at(i) == ")")
      parens--;

    if(parens == 0 && (tokens.at(i) == "==" || tokens.at(i) == "!="))
      return i;
  }
  return -1;
}

// checks less than or greater than comparisons
int Lexer::findOperator5(vector <string> tokens)
{
  int parens = 0;
  for(int i = 0; i < tokens.size(); i++)
  {
    if(tokens.at(i) == "(")
      parens++;

    else if(tokens.at(i) == ")")
      parens--;

    if(parens == 0 && tokens.at(i) == "<=" || tokens.at(i) == ">=" ||
      tokens.at(i) == "<" || tokens.at(i) == ">")
      return i;
  }
  return -1;
}

// checks add and subtract
int Lexer::findOperator6(vector <string> tokens)
{
  int parens = 0;
  for(int i = 0; i < tokens.size(); i++)
  {
    if(tokens.at(i) == "(")
      parens++;

    else if(tokens.at(i) == ")")
      parens--;

    if(parens == 0 && (tokens.at(i) == "+" || tokens.at(i) == "-"))
      return i;
  }
  return -1;
}

// checks multiply and divide
int Lexer::findOperator7(vector <string> tokens)
{
  int parens = 0;
  for(int i = 0; i < tokens.size(); i++)
  {
    if(tokens.at(i) == "(")
      parens++;

    else if(tokens.at(i) == ")")
      parens--;

    if(parens == 0 && (tokens.at(i) == "*" || tokens.at(i) == "/" || tokens.at(i) == "%"))
      return i;
  }
  return -1;
}

// selects operation and executes left and right
Variable Lexer::operatorSelect(Variable left, Variable right, string op)
{
  switch(op)
  {
  case "=":
    return UpdateValue(left.name, right);
    break;

  case "+=":
    return UpdateValue(left.name, OpPlus(left, right));
    break;
    
  case "-=":
    return UpdateValue(left.name, OpMinus(left, right));
    break;

  case "*=":
    return UpdateValue(left.name, OpMultiply(left, right));
    break;

  case "/=":
    return UpdateValue(left.name, OpDivide(left, right));
    break;

  case "%=":
    return UpdateValue(left.name, OpMod(left, right));
    break;

  case "||":
    return OpOr(left, right);
    break;

  case "&&":
    return OpAnd(left, right);
    break;

  case "==":
    return OpCompare(left, right);
    break;

  case "!=":
    return OpInvCompare(left, right);
    break;

  case "<=":
    return OpLessEqual(left, right);
    break;

  case ">=":
    return OpGreatEqual(left, right);
    break;

  case "<":
    return OpGreat(left, right);
    break;

  case ">":
    return OpLess(left, right);
    break;

  case "+":
    return OpPlus(left, right);
    break;

  case "-":
    return OpMinus(left, right);
    break;

  case "*":
    return OpMultiply(left, right);
    break;

  case "/":
    return OpDivide(left, right);
    break;

  case "%":
    return OpMod(left, right);
    break;

  }
}

// recursively separates tokens into operators
Variable Lexer::split(int index, vector<string> tokens)
{
  vector<string> leftTokens;
  vector<string> rightTokens;
  //allocate to these vectors
  for(int i = 0; i < index; i++)
    leftTokens.push_back(tokens.at(i));

  for(int i = index+1; i < tokens.size(); i++)
    rightTokens.push_back(tokens.at(i));

  for(int i = 0; i < leftTokens.size(); i++)
    cout << leftTokens.at(i) << " ";
  cout << endl;
  
  for(int i = 0; i < rightTokens.size(); i++)
  cout << rightTokens.at(i) << " ";
  cout << endl;

  Variable left = doLine(leftTokens);
  Variable right = doLine(rightTokens);

  return operatorSelect(left, right, tokens[index]);
}

Variable Lexer::doLine(vector<string> &tokens)
{
  //cerr << "start" << endl;
  if(tokens.size() > 1)
  {
    // shave outer parens
    if(tokens.at(0) == "(" && tokens.at(tokens.size()-1) == ")" )
    {
      tokens.pop_back();
      tokens.erase(tokens.begin());
    }
    
    int mid;
    
    // checks all assignment operators
    mid = findOperator1(tokens);
    
    // checks or
    if(mid == -1)
      mid = findOperator2(tokens);

    // checks and
    if(mid == -1)
      mid = findOperator3(tokens);

    // checks equality comparison
    if(mid == -1)
      mid = findOperator4(tokens);

    // checks less than greater than comparison
    if(mid == -1)
      mid = findOperator5(tokens);
    
    // checks add and subtract
    if(mid == -1)
      mid = findOperator6(tokens);

    // checks multiply and divide
    if(mid == -1)
      mid = findOperator7(tokens);

    cout << "mid: " << mid << endl;
    if(mid != -1)
      return split(mid, tokens);
    
    //check if its a function
    if(tokens.size() > 3)
    {
      //we assume function call
      if(tokens[1] == "(" && tokens[tokens.size()-1] == ")")
      {
	//proper function call
	SetupFunction(1, tokens);
      }

      else
      {
	cerr << "Function call syntax error at line " << currentLine << endl;
	exit(1);
      }
    }
  }
  else
  {
    //find the variable type that this is
    //cerr << "lets do it to it" << endl;
    Variable ret;

    ret.type = STRING;
    
    ret.data = (void*)tokens[0].c_str();
    return ret;
  }
}
