#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

vector<string> TokenizeLine(const string &str)
{
  vector<string> tokens;

  int i = 0;

  string curToken;

  bool quote = false;

  // traverse line end if get to end or hit comment
  while(i != str.size() && str[i] != '#')
  {
    //if hit function operators push them back
    if(str[i] == '(' || str[i] == ')' || 
       str[i] == ',' || str[i] == '?' || str[i] == ':')
    {
      if(curToken.size() > 0)
      {
	tokens.push_back(curToken);
	curToken = "";
      }

      tokens.push_back(str.substr(i,1));
    }

    // if hit math operators push them back
    else if(str[i] == '=' || str[i] == '+' || str[i] == '-' ||
	    str[i] == '/' || str[i] == '*' || str[i] == '>' ||
	    str[i] == '<')
    {
      if(curToken.size() > 0)
      {
	tokens.push_back(curToken);
	curToken = "";
      }

      // if += ++ etc
      if(str.size() > i + 1 && (str[i+1] == '=') || (str[i+1] == '+') ||
	 (str[i+1] == '-') && str[i] == str[i+1])
      {
	tokens.push_back(str.substr(i,2));
	i++;
      }

      else
	tokens.push_back(str.substr(i,1));
    }

    // if or and
    else if((str[i] == '|' || str[i] == '&')  && (str.size() > i+1 && str[i+1] == str[i]))
    {
      if(curToken.size() > 0)
      {
	tokens.push_back(curToken);
	curToken = "";
      }

      tokens.push_back(str.substr(i,2));
      i++;
    }

    else if(str[i] == '\"')
    {
      if(quote && curToken.size() > 0 && str[i-1] != '\\')
      {
	curToken+= str[i];
	tokens.push_back(curToken);
	curToken = "";
      }

      if(!quote)
      {
	curToken+= str[i];
	if(!quote && str[i-1] == '\\')
	{
	  cerr << "escaped \" outside of string literal" << endl;
	  exit(1);
	}
	quote = true;
      }
    }

    // if hit space reset curToken
    else if(str[i] == ' ' && !quote)
    {
      if(curToken.size() > 0)
      {
	tokens.push_back(curToken);
	curToken = "";
      }
    }
      
    // if nothing add it to curToken
    else
      curToken += str[i];

    i++;
  }

  if(curToken.size() > 0)
    tokens.push_back(curToken);

  return tokens;
}

int main()
{
  vector <string> tokens;
  string line = "\" skdlfjskdl \\\" lkdjsfdksf";
  tokens = TokenizeLine(line);
  cout <<tokens.size() << endl;
  for(int i = 0; i < tokens.size(); i++)
    cout << "'" << tokens.at(i) << "'" << endl;
}
