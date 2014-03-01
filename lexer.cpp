#include "lexer.h"

Lexer::Lexer() : currentLine(1)
{
	
}

Lexer::~Lexer()
{
}

//Helper Functions
bool Lexer::MakeVarIfVar( vector<string> &tokens)
{
    
    Variable var;
    var.name = tokens[1];
    
    if ( tokens[0] == "int" )
        var.type = INT;
    else if (tokens[0] == "bool")
        var.type = BOOL;
    else if (tokens[0] == "float")
        var.type = FLOAT;
    else if (tokens[0] == "string")
        var.type = STRING;
    else
        return false;  
    
    //~ tokens.erase(tokens.begin());
    //~ doLine(tokens);
    variables.push_back(var);
    cout << tokens[1] << endl;
    return true;
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
        //cout << "Line: " << i+1 << " First char: "<< fileLines[i][0]  << ":";
		//Ignore all lines that begin with whitespace or are commented
		if(fileLines[i][0] == '\t' || fileLines[i][0] == ' ' || fileLines[i][0] == '#' || fileLines[i].size() == 0)
		{
			continue;
		}
		else if(fileLines[i].substr(0, 8) == "function")
		{
			//cout << "Found a function on line " << i << ".\n";
			//Tokenize line.
            vector<string> tokens = TokenizeLine(fileLines[i]);
			//Make sure that it meets the basic requirements.
			if(tokens.size() < 4 || tokens[2][0]!='(' )
			{
				cerr << "Function at line " << currentLine + 1 << " is improperly declared"; exit(1);
			}
			
			int count = 0;
			Function newFunc;
			newFunc.name = tokens[1];
			//cout << "Function name found: " << newFunc.name << ".\n";
			newFunc.fileLine = i;
			Variable arg;
			bool varTypeAssigned = false;
			bool nameAssigned = false;
			for(int j = 3; j < tokens.size(); j++)
			{
				if( tokens[j][0] == ')' && (varTypeAssigned == nameAssigned))
				{
					//cout << ") detected.\n";
					if(j != tokens.size()-2 )
					{
						cerr << "Line " << (i+1) << " is not declared properly. There is information after the closed parenthesis.";
						//exit(1);
					}
                    
                    if(varTypeAssigned && nameAssigned)// if both are true, then variable has been created
                    {
                    	newFunc.functionArguments.push_back(arg);
                    }
                        
					vectorOfFunctions.push_back(newFunc);
                    
					//cout << "Function pushed.\n";
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
					//cout << "Variable pushed into function.\n";
					newFunc.functionArguments.push_back(arg);
					Variable tmp;
					arg = tmp;
					varTypeAssigned = false;
					nameAssigned = false;
				}
				else if(varTypeAssigned && !nameAssigned)
				{
					arg.name = tokens[j];
					//cout << "Variable created: " << arg.name << ".\n";
					nameAssigned = true;
				}
				else
				{
					cerr << "Unexpected Error on line " << (i+1) << "Maybe missing a ( ?";
					exit(1);
				}
                
			}
            
		}
        else
        {
            // << "GVAR";
            //vector<string> tokens = TokenizeLine(fileLines[i]);
            //cout << tokens[1] << endl;
            //MakeVarIfVar(tokens);
            //cout << fileLines[i] << endl;
        }
        //cout << endl;
	}
}

Variable Lexer::doFunction(string fnName, vector<Variable> &arguments)
{
	Variable var;
	return var;
}

Variable Lexer::SetupFunction(unsigned leftParens, vector<string> &tokens)
{
	int leftParensCount = 0;
	vector<int> commas;						//Stores indexes of commas and last )

	for (int i = leftParens+1; i < tokens.size(); i++)
	{
		if (tokens[i] == "(")				// If a left parenthesis is found
			leftParensCount++;				// increment 
		else if (tokens[i] == ")")			// otherwise if a right parenthesis is found
		{
			if(leftParensCount==0)		// check if this should be the last right parens
			{
				commas.push_back(i);	// and add index to commas vector
				//cout << "Added comma." << endl;
			}
			else
				leftParensCount--;			// otherwise it's not last right parens and decrement
		}
		else if (tokens[i][0] == ',' && leftParensCount == 0) //If it's the last comma 
			commas.push_back(i);	// Add that shit
	}
	
	vector<Variable> args;
	vector<string> convertTokens;
	//cout << "Commas: " << (commas.size()-1) << endl;
	if(commas.size()>=1 && tokens.size() > leftParens+1)
	{
		cout << "First Arg." << endl;
		for(int i = leftParens+1; i<commas[0]; i++)
		{
			convertTokens.push_back(tokens[i]);
			//cout << tokens[i] << endl;
		}
		//cout << endl;
		//args.push_back(doLine(convertTokens));
		convertTokens.clear();
	}
	for(int i = 1; i<commas.size(); i++)
	{
		cout << "Arg"<< (i+1) <<": ";
		for(int j = commas[i-1] + 1; j<commas[i]; j++)
		{
			convertTokens.push_back(tokens[j]);
			//cout << tokens[j] << endl;
		}
		//cout << endl;
		//args.push_back(doLine(convertTokens));
		convertTokens.clear();
	}
	return doFunction(tokens[leftParens-1], args);
}


vector<string> Lexer::TokenizeLine(const string &str)
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
