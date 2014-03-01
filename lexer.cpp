#include "lexer.h"

Lexer::Lexer() : currentLine(1)
{
	
}

Lexer::~Lexer()
{
}


//DYLANS FUNCTION
void Lexer::ReadFile(char *filePath)
{
  // checks if file exists
  ifstream file;
  file.open(filePath);
  
  if(!file.is_open())
	{
		cerr << "File doesn't exist" << endl;
		exit(1);
	}

  string line;

  while(!file.eof())
	{
		getline(&file, line);
		fileLines.push_back(line);
	}

  file.close();
}

//SULTANS FUNCTION
void Lexer::GetMatchingParens(unsigned leftParens, vector<string> &tokens)
{
	int leftParensCount = 0;
	for (int i = 0; i < token.size(); i++)
	{
		if (tokens[0] == '(')  // If a left parenthesis is found
			leftParensCount++; // increment 
		else if (tokens[0] == ')') // otherwise if a right parenthesis is found
		if (leftParensCount == 0) // check if this should be the last right parens
			return i;             // and return the index of it
		else
			leftParensCount--;    // otherwise it's not last right parens and decrement
	}
	cerr << "ERROR at line: " << currentLine << " You are missing at least one right parenthesis" << endl;
}
