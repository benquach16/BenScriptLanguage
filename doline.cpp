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

    if(parens == 0 && tokens.at(i) == "+=" || tokens.at(i) == "?" ||
       tokens.at(i) == "-=" || tokens.at(i) == "*=" || tokens.at(i) == "/=" ||
       tokens.at(i) == "=" || tokens.at(i) == "%=")
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

    if(parens == 0 && tokens.at(i) == "==" || tokens.at(i) == "!=")
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

    if(parens == 0 && tokens.at(i) == "+" || tokens.at(i) == "-")
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

    if(parens == 0 && tokens.at(i) == "*" || tokens.at(i) == "/")
      return i;
  }
  return -1;
}

// selects operation and executes left and right
Variable Lexer::operatorSelect(vector<string> left, vector<string> right, string op)
{
}

// recursively separates tokens into operators
Variable Lexer::split(int index, vector<string> tokens)
{
  vector<string> leftTokens;
  vector<string> rightTokens;
  //allocate to these vectors
  for(unsigned n = 0; n < index; n++)
  {
    leftTokens.push_back(tokens[n]);
  }
  for(unsigned n = tokens.size()-1; n > index; n--)
  {
    rightTokens.push_back(tokens[n]);
  }
  //cerr << "doing lefft" << endl;
  doLine(leftTokens);
  //cerr << "did left works" << endl;
  doLine(rightTokens);
  for(int i = 0; i  < leftTokens.size(); i++)
    cout << leftTokens.at(i) << " ";
  
  for(int i = 0; i < rightTokens.size(); i++)
    cout << rightTokens.at(i) << " ";

  return operatorSelect(leftTokens, rightTokens, tokens[index]);
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
    //cerr << mid << endl;
    if(mid != -1)
      return split(mid, tokens);
    // checks or
    mid = findOperator2(tokens);
    if(mid != -1)
      return split(mid, tokens);
    
    // checks and
    mid = findOperator3(tokens);
    if(mid != -1)
      return split(mid, tokens);
    
    // checks equality comparison
    mid = findOperator4(tokens);
    if(mid != -1)
      return split(mid, tokens);
    
    // checks less than or greater than comparisons
    mid = findOperator5(tokens);
    if(mid != -1)
      return split(mid, tokens);
    
    // checks add or subtract
    for(unsigned i = 0; i < tokens.size(); i++)
    {
      cerr << tokens[i];
    }
    cerr << endl;
    mid = findOperator6(tokens);
    if(mid != -1)
      return split(mid, tokens);
    
    // checks multiply and divide
    mid = findOperator7(tokens);
    if(mid != -1)
      return split(mid, tokens);
		
    //check if its a function
    if(tokens.size() > 3)
    {
      //we assume function call
      if(tokens[1] == "(" && tokens[tokens.size()-1] == ")")
      {
				//proper function call
      }

      else
      {
				cerr << "Function call syntax error at line " << currentLine << endl;
				exit(1);
      }
    }
  }
  //cerr << "end";
}
