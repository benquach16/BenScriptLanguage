
#include <iostream>
#include <vector>
#include "lexer.h"

using namespace std;

int main()
{
  vector <string> tokens;
  string t1, t2, t3, t4, t5, t6, t7;
  t1 = "(";
  t2 = "a";
  t3 = "=";
  t4 = ")";
  t5 = "b";
  t6 = "c";
  t7 = "+";
  
  // tokens = "((a = b) + c)"
  /*
  tokens.push_back(t1);
  tokens.push_back(t1);
  tokens.push_back(t2);
  tokens.push_back(t3);
  tokens.push_back(t5);
  tokens.push_back(t4);
  tokens.push_back(t7);
  tokens.push_back(t6);
  tokens.push_back(t4);xo
  */
  tokens.push_back("print");
  tokens.push_back("(");
  tokens.push_back("test");
  tokens.push_back(")");
  Lexer l;
  l.doLine(tokens);
}
