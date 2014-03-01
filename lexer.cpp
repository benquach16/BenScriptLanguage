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

  while(getline(file, line))
	{
		fileLines.push_back(line);
	}

  file.close();
}

//SULTANS FUNCTION
int Lexer::GetMatchingParens(unsigned leftParens, vector<string> &tokens)
{
	int leftParensCount = 0;
	for (int i = leftParens; i < tokens.size(); i++)
	{
		if (tokens[0] == "(")  // If a left parenthesis is found
			leftParensCount++; // increment 
		else if (tokens[0] == ")") // otherwise if a right parenthesis is found
		{
			if (leftParensCount == 0) // check if this should be the last right parens
				return i;             // and return the  index of it
			else
				leftParensCount--;    // otherwise it's not last right parens and decrement
		}
			
	}
	cerr << "ERROR at line: " << currentLine << " You are missing at least one right parenthesis" << endl;
}

void Lexer::FirstPass()
{
	
	for(int i = 0; i < fileLines.size(); i++ )
	{
		//Ignore all lines that begin with whitespace or are commented
		if(fileLines[i][0] == '\t' || fileLines[i][0] == ' ' || fileLines[i][0] == '\n' || fileLines[i][0] == '#')
		{
			continue;
		}
		else if(fileLines[i].substr(0, 7) == "function")
		{
			//Tokenize line.
			vector<string> tokens = TokenizeLine(fileLines[0]);
			//Make sure that it meets the basic requirements.
			if(tokens.size() < 4 || tokens[2][0]!='(' )
			{
				cerr << "Function at line " << currentLine + 1 << " is improperly declared"; exit(1);
			}
			
			int count = 0;
			Function newFunc;
			newFunc.name = tokens[1];
			newFunc.fileLine = i;
			Variable arg;
			bool varTypeAssigned = false;
			bool nameAssigned = false;
			for(int j = 2; j < tokens.size(); j++)
			{
				if( tokens[j][0] == ')' && (varTypeAssigned == nameAssigned))
				{
					if(j != tokens.size()-1 )
					{
						cerr << "Line " << (i+1) << " is not declared properly. There is information after the closed parenthesis.";
						exit(1);
					}

					vectorOfFunctions.push_back(newFunc);
					break;
				}
				else if( tokens[j] == "string" && !varTypeAssigned) 
				{
					arg.type = STRING; newFunc.name = tokens[j]; varTypeAssigned = true;
				}
				else if( tokens[j] == "bool" && !varTypeAssigned) 
				{
					arg.type = BOOL; newFunc.name = tokens[j]; varTypeAssigned = true;
				}
				else if( tokens[j] == "int" && !varTypeAssigned) 
				{
					arg.type = INT; newFunc.name = tokens[j]; varTypeAssigned = true;
				}
				else if( tokens[j] == "float" && !varTypeAssigned) 
				{
					arg.type = FLOAT; newFunc.name = tokens[j]; varTypeAssigned = true;
				}
				else if(tokens[j][0] == ',' && varTypeAssigned && nameAssigned)
				{
					newFunc.functionArguments.push_back(arg);
					Variable tmp;
					arg = tmp;
				}
				else if(varTypeAssigned && !nameAssigned)
				{
					arg.name = tokens[j];
					nameAssigned = true;
				}
				else
				{
					cerr << "Unexpected Error on line " << (i+1) << "Maybe missing a ( ?";
					exit(1);
				}
			}
		}
	}
}

vector<int> Lexer::SetupFunction(unsigned leftParens, vector<string> &tokens)
{
	int leftParensCount = 0;
	vector<int> commas;						//Stores indexes of commas and last )

	for (int i = leftParens; i < tokens.size(); i++)
	{
		if (tokens[i] == "(")				// If a left parenthesis is found
			leftParensCount++;				// increment 
		else if (tokens[i] == ")")			// otherwise if a right parenthesis is found
		{
			if(!leftParensCount)		// check if this should be the last right parens
			{
				commas.push_back(i);	// and add index to commas vector
				return commas;
			}
			else
				leftParensCount--;			// otherwise it's not last right parens and decrement
		}
		else if (tokens[i][0] == ',' && leftParensCount == 0) //If it's the last comma 
			commas.push_back(i);	// Add that shit
		else
			cerr << "ERROR at line: " << currentLine << " Found in Function: setupFunction. You are missing at least one right parenthesis" << endl;	
	}
}

