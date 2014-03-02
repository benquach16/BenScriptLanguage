#include "lexer.h"
Lexer::Lexer() : currentLine(1)
{
	//amazing.
	Variable temp;
	temp.type = BOOL;
	temp.name = "true";
	temp.data = new bool(true);

	Variable temp2;
	temp2.type = BOOL;
	temp2.name = "false";
	temp2.data = new bool(false);
  
	variables.push_back(temp);
	variables.push_back(temp2);
}

Lexer::~Lexer()
{
	for(unsigned i = 0; i < variables.size(); i++)
	{
		delete variables[i].data;
	}
	variables.clear();
}

//Helper Functions
//email function
int Lexer::sendMail(vector<string> &tokens)
{
    //for(int i = 0; i < 5; i++)
        //cout << tokens[i] << endl;
        
    //tokens[3] = tokens[3].substr(1,tokens[3].find('"'));
    //tokens[4] = tokens[4].substr(1,tokens[4].find('"'));
	int retval = -1;
	FILE *mailpipe = popen("/usr/lib/sendmail -t", "w");
	if (mailpipe != NULL) 
	{
		fprintf(mailpipe, "To: %s\n", tokens[1].c_str());
		fprintf(mailpipe, "From: %s\n", tokens[2].c_str());
		fprintf(mailpipe, "Subject: %s\n\n", tokens[3].c_str());
		fwrite(tokens[4].c_str(), 1, tokens[4].size(), mailpipe);
		fwrite(".\n", 1, 2, mailpipe);
		pclose(mailpipe);
		retval = 0;
	}
	else 
		perror("Failed to invoke sendmail");
	
	return retval;
}


bool Lexer::MakeVarIfVar(vector<string> &tokens)
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
	if(tokens.size() > 2)
	{
		tokens.erase(tokens.begin());
		doLine(tokens);
	}

	variables.push_back(var);
	//cerr << "current scope: " << endl;
	//for(int i = 0; i < variables.size(); i++)
	//	cerr << variables[i].name << endl;
	//cout << tokens[1] << endl;
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
	for (int i = leftParens + 1; i < tokens.size(); i++)
	{
		if (tokens[i] == "(")  // If a left parenthesis is found
			leftParensCount++; // increment 
		else if (tokens[i] == ")") // otherwise if a right parenthesis is found
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
		//cout << "Line: " << i+1 << " First char: "<< fileLines[i]  << endl;
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
				//cout << "Here." << endl;
				if( tokens[j][0] == ')' && (varTypeAssigned == nameAssigned))
				{
					//cout << ") detected.\n";
					for(int q = 0; q < tokens.size(); q++)
					{
						//cout << "\"" << tokens[q] << "\"\n";
					}
					
					if(j != tokens.size()-1 )
					{
						cerr << "Line " << (i+1) << " is not declared properly. There is information after the closed parenthesis.";
						//exit(1);
					}
                    
					if(varTypeAssigned && nameAssigned)// if both are true, then variable has been created
					{
						newFunc.functionArguments.push_back(arg);
					}
					//cerr << newFunc.name << endl;
					vectorOfFunctions.push_back(newFunc);
                    
					//cout << "Function pushed.\n";
					break;
				}
				else if( tokens[j] == "string" && !varTypeAssigned) 
				{
					arg.type = STRING; varTypeAssigned = true;
				}
				else if( tokens[j] == "bool" && !varTypeAssigned) 
				{
					arg.type = BOOL; varTypeAssigned = true;
				}
				else if( tokens[j] == "int" && !varTypeAssigned) 
				{
					arg.type = INT; varTypeAssigned = true;
				}
				else if( tokens[j] == "float" && !varTypeAssigned) 
				{
					arg.type = FLOAT;varTypeAssigned = true;
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
        else if(fileLines[i].substr(0, 5) == "email")
        {
            bool concat = false; 
            vector<string> tokens = TokenizeLine(fileLines[i]);
            if(tokens.size() < 5 )
			{
				cerr << "Email at line " << currentLine + 1 << " is improperly declared"; exit(1);
			}
            
            int x = sendMail(tokens);
        }
		else
		{
			// << "GVAR";
			//vector<string> tokens = TokenizeLine(fileLines[i]);
			//cout << tokens[1] << endl;
			//MakeVarIfVar(tokens);
			//cout << fileLines[i] << endl;
		}
	}
	for(int j = 0; j<vectorOfFunctions.size(); j++)
	{
		if(vectorOfFunctions[j].name == "main")
		{
			currentLine = vectorOfFunctions[j].fileLine;
			vector<Variable> emptyArgs;
			doFunction("main", emptyArgs);
			break;
		}
	}
	//cout << "We are out of the FirstPass!" << endl;
}

void Lexer::AddScope(string input)
{
	//checks if adding main
	Variable temp;
	temp.name = input;
	temp.type = INT;

	int firstHash = -1;
	// traverses variables for hashtags and 
	if(input[0] != '-')
	{
		for(int i = 0; i < variables.size(); i++)
		{
			if(variables.at(i).name == "#")
			{
				firstHash = i;
				break;
			}
		}
	
			
		if(firstHash != -1)
		{
			temp.data = new int(*(int *)variables.at(firstHash).data);
			*(int*)variables.at(firstHash).data = variables.size();
			
		}
		else
		{
			temp.data = new int(variables.size());
		}
	}
	variables.push_back(temp);
}

void Lexer::EraseScope()
{
	while(variables.at(variables.size()-1).name != "#" && variables.at(variables.size()-1).name != "-")
	{
		variables.pop_back();
	}

	if(variables.at(variables.size()-1).name == "#")
	{
		for(int j = 0; j < variables.size(); j++)
		{
			if(variables.at(j).name == "#")
			{
				*(int *)variables.at(j).data = *(int *)variables.at(variables.size()-1).data;
				break;
			}
		}
	}
	variables.pop_back();
}

Variable Lexer::doFunction(string funcName, vector<Variable> arguments)
{
	//set return value to null
	if(funcName != "print")
	{
		if(funcName == "if" || funcName == "while" || funcName == "for" || funcName =="else")
		{
			AddScope("-");
		}
		else
		{
			AddScope("#");
		}
	}

	if(funcName == "print")
	{
		for (unsigned i = 0; i < arguments.size(); i++)
		{
			if(arguments[i].type == INT)
			{
				cout << (*(int*)arguments[i].data) << endl;
			}
			else if(arguments[i].type == STRING)
			{
				cout << (char*)arguments[i].data << endl;
			}
			else if(arguments[i].type == FLOAT)
			{
				cout << *(float*)arguments[i].data << endl;
			}
			else
			{
				if(*(bool*)arguments[i].data)
					cout << "true" << endl;
				else
					cout << "false" << endl;
			}
		}
		if(arguments.size() == 0)
		{
			cerr << "Not enough arguments for print at line " << currentLine << "." << endl;
			exit(1);
		}
		return arguments[0];
	}
	else if(funcName == "if")
	{
		if(arguments[0].type != BOOL || arguments.size() != 1)
		{
			cerr << "If statements need a single boolean condition, you dingus. Line " << currentLine << ".";
			exit(1);
		}
		int PCBack = FindPCBack(!*(bool*)arguments[0].data) - 1;
		if(*(bool*)arguments[0].data)
		{
			currentLine++;
			GoThroughFunction();
		}
		currentLine = PCBack;
		if(arguments.size() == 0)
		{
			cerr << "Not enough arguments for print at line " << currentLine << "." << endl;
			exit(1);
		}
		return arguments[0];
	}
	for(unsigned i = 0; i < vectorOfFunctions.size(); i++)
	{
		if(funcName == vectorOfFunctions[i].name && vectorOfFunctions[i].functionArguments.size() == arguments.size())
		{
			bool loopBroken = false;
			for(unsigned j = 0; j < vectorOfFunctions[i].functionArguments.size(); j++)
			{
				if(vectorOfFunctions[i].functionArguments[j].type != arguments[j].type)
				{
					loopBroken = true;
					break;
				}
			}
			if(!loopBroken)
			{

				for(int k = 0; k < arguments.size(); k++)
				{
					arguments[k].name = vectorOfFunctions[i].functionArguments[k].name;
					variables.push_back(arguments[k]);
				}
				Variable ret;
				ret.data = 0;			
				//save the program counter temporarily
				int prevCurrentLine = currentLine;
				GoThroughFunction(vectorOfFunctions[i]);
				//reset
				currentLine = prevCurrentLine;
				return ret;
			}
		}
	}
	cerr << "No function call found for " << funcName << endl;
	exit(1);
  
}

void Lexer::GoThroughFunction(Function func)
{
	//loop while there is a tab
	currentLine = func.fileLine+1;

	GoThroughFunction();
}
void Lexer::GoThroughFunction()
{
	//loop while there is a tab
	int tabCount = numTabs(fileLines[currentLine])-1;	
	while(fileLines[currentLine][tabCount] == '\t')
	{
		//cerr << currentLine << endl;
		//cerr << fileLines[currentLine] << endl;
		vector<string> tokens = TokenizeLine(fileLines[currentLine]);

		//cerr << currentLine << endl;
		if(tokens.size()> 0)
			doLine(tokens);
		currentLine++;
		if(currentLine >= fileLines.size())
		{
			break;
		}
	}
	EraseScope();
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
		//cout << "First Arg." << endl;
		for(int i = leftParens+1; i<commas[0]; i++)
		{
			convertTokens.push_back(tokens[i]);
			//cout << tokens[i] << endl;
		}
		//cout << endl;
		if(convertTokens.size() > 0)
			args.push_back(doLine(convertTokens));
		convertTokens.clear();
	}
	for(int i = 1; i<commas.size(); i++)
	{
		//cout << "Arg"<< (i+1) <<": ";
		for(int j = commas[i-1] + 1; j<commas[i]; j++)
		{
			convertTokens.push_back(tokens[j]);
			//cout << tokens[j] << endl;
		}
		//cout << endl;
		if(convertTokens.size()>0)
			args.push_back(doLine(convertTokens));
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
	while(i != str.size() && str[i] != '#' && str[i] != 13)
	{
		if(str[i] == '\t' && !quote)
		{
			i++;
			continue;
		}
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

	if(!curToken.empty())
		tokens.push_back(curToken);

	if((int)(tokens[tokens.size()-1][0]) == 13)
		tokens.pop_back();
	return tokens;
}

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

		if(parens == 0 && (tokens.at(i) == "+=" || tokens.at(i) == "?" ||
						   tokens.at(i) == "-=" || tokens.at(i) == "*=" || tokens.at(i) == "/=" ||
						   tokens.at(i) == "=" ))
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

		if(parens == 0 && (tokens.at(i) == "*" || tokens.at(i) == "/" || tokens.at(i) == "%" ))
			return i;
	}
	return -1;
}
// checks unary operators
int Lexer::findOperator8(vector <string> tokens)
{
	int parens = 0;
	for(int i = 0; i < tokens.size(); i++)
	{
		if(tokens.at(i) == "(")
			parens++;

		else if(tokens.at(i) == ")")
			parens--;

		if(parens == 0 && (tokens.at(i) == "++" || tokens.at(i) == "--" || tokens.at(i) == "!"))
			return i;
	}
	return -1;
}

// selects operation and executes left and right
Variable Lexer::operatorSelect(vector<string> leftTokens, vector<string> rightTokens, string op)
{

	Variable var; 
	
	if (op == "++" || op == "--" || op == "!")
	{
		bool isLeft = false;
		Variable send;
		if(leftTokens.size() == 0)
		{
			if(rightTokens.size() == 0)
			{
				cerr << "Unary Operator "<< op <<" has no arguments on line " << currentLine <<".\n";
				exit(1);
			}
			send = doLine(rightTokens);
		}else if(rightTokens.size() == 0)
		{
			send = doLine(leftTokens);
			isLeft = true;
		}else{
			cerr << "Operator "<< op <<" has two variables on line " << currentLine <<".\n";
			exit(1);
		}
		if(op == "++")
		{
			OpPlusPlus(send, isLeft);		  
		}
	  
		else if(op == "--")
		{
			OpMinusMinus(send, isLeft);
		}
	  
		else
		{
			OpNot(send);
		}
	}
	
	Variable left = doLine(leftTokens);
	Variable right = doLine(rightTokens);

	if(op == "=")
		return UpdateValue(left.name, right);

	if(op == "+=")
		return UpdateValue(left.name, OpPlus(left, right));
    
	if(op == "-=")
		return UpdateValue(left.name, OpMinus(left, right));

	if(op == "*=")
		return UpdateValue(left.name, OpMultiply(left, right));

	if(op == "/=")
		return UpdateValue(left.name, OpDivide(left, right));

	if(op == "%=")
		return UpdateValue(left.name, OpMod(left, right));

	if(op == "+")
		return OpPlus(left, right);

	if(op == "-")
		return OpMinus(left, right);

	if(op == "*")
		return OpMultiply(left, right);

	if(op ==  "/")
		return OpDivide(left, right);

	if (op == "%")
		return OpMod(left, right);

	else if (op == ">")
	{
		var.type = BOOL;
		var.data = new bool(OpGreat(left, right));
		return var;
	}
		 

	else if (op == "<")
	{
		var.type = BOOL;
		var.data = new bool(OpLess(left, right));
		return var;
	}

	else if (op == ">=")
	{
		var.type = BOOL;
		var.data = new bool(OpGreatEqual(left, right));
		return var;
	}

	else if (op == "<=")
	{
		var.type = BOOL;
		var.data = new bool(OpLessEqual(left, right));
		return var;
	}

	else if (op == "==")
	{
		var.type = BOOL;
		var.data = new bool(OpCompare(left, right));
		return var;
	}

	else if (op == "!=")
	{
		var.type = BOOL;
		var.data = new bool(OpInvCompare(left, right));
		return var;
	}

	else if (op == "&&")
	{
		var.type = BOOL;
		var.data = new bool(OpAnd(left, right));
		return var;
	}

	else if (op == "||")
	{
		var.type = BOOL;
		var.data = new bool(OpOr(left, right));
		return var;
	}

  
	Variable trash;
	return trash;
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
	/*
	  for(int i = 0; i < leftTokens.size(); i++)
	  cout << leftTokens.at(i) << " ";
	  cout << endl;
  
	  for(int i = 0; i < rightTokens.size(); i++)
	  cout << rightTokens.at(i) << " ";
	  cout << endl;
	*/

	return operatorSelect(leftTokens, rightTokens, tokens[index]);
}

Variable Lexer::doLine(vector<string> &tokens)
{
	if(tokens.size() > 1)
	{
		// shave outer parens
		if(tokens.at(0) == "(" && (GetMatchingParens(0, tokens)==tokens.size()-1))
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
    
		if(mid == -1)
			mid = findOperator8(tokens);
    
		if(mid != -1)
			return split(mid, tokens);
    
		if (tokens[0] == "int" || tokens[0] == "float" || tokens[0] == "string"
			|| tokens[0] == "bool")
		{
			//variable declaration here
			//so lets interpret
			MakeVarIfVar(tokens);
			//cerr <<"ADDING: "<< variables[variables.size()-1].name << endl;
			return variables[variables.size()-1];
		}
        
		//check if its a function
		if(tokens.size() > 2)
		{
			//we assume function call
			if(tokens[1] == "(" && tokens[tokens.size()-1] == ")")
			{
				//proper function call
				//cout << "Found a function: " << tokens[0] << endl;
				return SetupFunction(1, tokens);

			}

			else
			{
				cerr << "Function call syntax error at line " << currentLine << endl;
				exit(1);
			}
		}
	}
	else if (tokens.size() == 1)
	{
		//Find Value should handle the type and value.
		return FindValue(tokens[0]);
	}
	else
	{
		cerr << tokens.size() << endl;
		cerr << "Function: DoLine. Syntax error on line: " << currentLine << endl;
		exit(1);
	}
}
Variable Lexer::UpdateValue(string name, Variable var)
{
	for(int i = 0; i < variables.size(); i++)
	{
		if(variables[i].name == name)
		{
			if(variables[i].type == var.type)
			{
				variables[i].data = var.data;
				return variables[i];
			}
			else
			{
				cerr << "Variable 1 : " << *(int*)variables[i].data << endl;
				cerr << "Variable 2 : " << *(int*)var.data << endl;
				cerr << "Tried to cast variable of type " << variables[i].type <<
					" to "<< var.type << " at line " << currentLine << endl;
				exit(1);
			}
			
		}
		else if(variables[i].name[0] == '#')
		{
			i = *(int*)(variables[i].data);
		}
	}
	cerr << "Variable " << name << " not declared in scope." << endl;
	exit(1);
}

Variable& Lexer::FindValue(string name)
{
	for(int i = 0; i < variables.size(); i++)
	{
		if(variables[i].name == name)
		{
			return variables[i];
		}
		else if(variables[i].name[0] == '#')
		{
			i = *(int*)(variables[i].data);
		}
	}
	//find it as a literal if it is one
	if(name[0] == '\"')
	{
		//its a string so interpret it as such
		Variable ret;
		ret.type = STRING;
		//realloc mem
		char *t = new char[name.size()];
		for(unsigned i = 0; i < name.size(); i++)
		{
			t[i] = name[i];
		}
		ret.data = t;
		variables.push_back(ret);
		return variables[variables.size()-1];
	}
	else if (name[0] >= '0' && name[0] <= '9')
	{
		//float or int literal
		Variable ret;
		for(unsigned i = 0; i < name.size(); i++)
		{
			if(name[i] == '.')
			{
				//its a float
				ret.type = FLOAT;
				//cast the string into a float now
				istringstream iss(name);

				float *t = new float;

				iss >> *t;
				ret.data = t;
				variables.push_back(ret);
				return variables[variables.size()-1];
			}
		}
		istringstream iss(name);

		int *t = new int;
		ret.type = INT;
		iss >> *t;
		ret.data = t;
		variables.push_back(ret);
		return variables[variables.size()-1];
	}
	else if (name[0] == '.')
	{
		Variable ret;
		//float literal
		ret.type = FLOAT;
		//cast the string into a float now
		istringstream iss(name);

		float *t = new float;

		iss >> *t;
		ret.data = t;
		variables.push_back(ret);
		return variables[variables.size()-1];
	}

	else if (name == "true" || name == "false")
	{
		Variable ret;
		ret.type = BOOL;
		if(name == "true")
			ret.data = new bool(true);
		else
			ret.data = new bool(false);
	}
	cerr << "Variable " << name << " not declared in scope." << endl;
	cerr << "Scope: " << endl;
	for(int i = 0; i < variables.size(); i++)
	{
		cerr << variables[i].name << endl;
	}
	exit(1);
}

Variable Lexer::OpMinus(Variable left, Variable right)
{
	Variable var;

	//case float - float
	if((left.type == FLOAT) && (right.type == FLOAT))
	{
		var.type = FLOAT;
		var.data = new float(*(float*) left.data - *(float *) right.data);
    
	}

	// case int - int
	else if(left.type == INT && right.type == INT)
	{
		var.type = INT;
		var.data = new int(*(int *) left.data - *(int *) right.data);
	}

	// case int - float
	else if(left.type == INT && right.type == FLOAT)
	{
		var.type = INT;
		var.data = new int(*(int *) left.data - *(int *) right.data);
	}

	// case float - int
	else if(left.type == FLOAT && right.type == INT)
	{
		var.type = INT;
		var.data = new int(*(int *) left.data - *(int *) right.data);

	}
 
	else
	{
		cerr << "invalid variable type" << endl;
		exit(1);
	}

	return var;
}

Variable Lexer::OpMultiply(Variable left, Variable right)
{
	Variable var;

	//case float - float
	if(left.type == FLOAT && right.type == FLOAT)
	{
		var.type = FLOAT;
		var.data = new float(*(float*) left.data * *(float *) right.data);
	}

	// case int - int
	else if(left.type == INT && right.type == INT)
	{
		var.type = INT;
		var.data = new int(*(int *) left.data * *(int *) right.data);
	}

	// case int - float
	else if(left.type == INT && right.type == FLOAT)
	{
		var.type = INT;
		var.data = new int(*(int *) left.data * *(int *) right.data);
	}

	// case float - int
	else if(left.type == FLOAT && right.type == INT)
	{
		var.type = INT;
		var.data = new int(*(int *) left.data * *(int *) right.data);
	}
  
	else
	{
		cerr << "invalid variable type" << endl;
		exit(1);
	}

	return var;
}

Variable Lexer::OpDivide(Variable left, Variable right)
{
	Variable var;

	//case float - float
	if(left.type == FLOAT && right.type == FLOAT)
	{
		var.type = FLOAT;
		var.data = new float(*(float*) left.data / *(float *) right.data);
	}

	// case int - int
	else if(left.type == INT && right.type == INT)
	{
		var.type = INT;
		var.data = new int(*(int *) left.data / *(int *) right.data);
	}

	// case int - float
	else if(left.type == INT && right.type == FLOAT)
	{
		var.type = INT;
		var.data = new int(*(int *) left.data / *(int *) right.data);
	}

	// case float - int
	else if(left.type == FLOAT && right.type == INT)
	{
		var.type = INT;
		var.data = new int(*(int *) left.data / *(int *) right.data);

	}
  
	else
	{
		cerr << "invalid variable type" << endl;
		exit(1);
	}

	return var;
}

Variable Lexer::OpMod(Variable left, Variable right)
{
	Variable var;

	if(left.type == INT && right.type == INT)
	{
		var.type = INT;
		var.data = new int(*(int *) left.data % *(int *) right.data);
	}

	else
	{
		cerr << "invalid variable type" << endl;
		exit(1);
	}

	return var;
}

Variable Lexer::OpPlusPlus(Variable var, bool isLeft)
{
	Variable temp;

	if(var.type == INT)
	{
		temp.type = INT;
		temp.data = new int(1);
		if(isLeft)
		{
			temp = OpPlus(var, temp);
			UpdateValue(var.name, temp);
			return temp;
		}
    
		else
		{
			UpdateValue(var.name, OpPlus(var, temp));
			return var;
		}
	}

	if(var.type == FLOAT)
	{
		temp.type = FLOAT;
		temp.data = new float(1.0);

		if(isLeft)
		{
			temp = OpPlus(var, temp);
			UpdateValue(var.name, temp);
			return temp;
		}
    
		else
		{
			UpdateValue(var.name, OpPlus(var, temp));
			return var;
		}
	}

	else
	{
		cerr << "invalid variable type" << endl;
		exit(1);
	}
}

Variable Lexer::OpMinusMinus(Variable var, bool isLeft)
{
	Variable temp;
	if(var.type == INT)
	{
		temp.type = INT;
		temp.data = new int(-1);
		if(isLeft)
		{
			temp = OpPlus(var, temp);
			UpdateValue(var.name, temp);
			return temp;
		}
    
		else
		{
			UpdateValue(var.name, OpPlus(var, temp));
			return var;
		}
	}

	if(var.type == FLOAT)
	{
		temp.type = FLOAT;
		temp.data = new float(1.0);

		if(isLeft)
		{
			temp = OpPlus(var, temp);
			UpdateValue(var.name, temp);
			return temp;
		}
    
		else
		{
			UpdateValue(var.name, OpPlus(var, temp));
			return var;
		}
	}

	else
	{
		cerr << "invalid variable type" << endl;
		exit(1);
	}
}

Variable Lexer::OpNot(Variable var)
{
	Variable temp;
	if(var.type == BOOL)
	{
		temp.type = var.type;
		temp.data = new bool(!*(bool *) var.data);
	}

	else
	{
		cerr << "invalid variable type" << endl;
		exit(1);
	}
	return temp;
}

Variable Lexer::OpPlus(Variable left, Variable right)
{
	Variable var;


	// INT
	// (Int + Int/Float) OR (Float + Int) OR (Int/Bool + Int/Bool)
	if ((left.type == INT && (right.type == INT || right.type == FLOAT))
		|| (left.type == FLOAT && right.type == INT)
		|| ((left.type == INT || left.type == BOOL) && (right.type == BOOL || right.type == INT)))

	{
		var.type = INT;		// Change type
		var.data = new int(*(int *)left.data + *(int *)right.data);		// Assign initial value to match type
		// Assign correct value
	}


	// STRING
	// (String + String)
   
	if ((left.type == STRING) && (right.type == STRING))
	{
		var.type = STRING;		// Change type
		string temp = *(char **)left.data;
		temp += *(char **)right.data;
		var.data = new string(temp);		// Assign initial value to match type
		// Assign correct value
	}
	/*
	  if ((left.type == STRING) && (right.type == INT))
	  {
	  var.type = STRING;		// Change type
	  var.data = new string(*(char *)left.data + *(char *)right.data);		// Assign initial value to match type
	  // Assign correct value
	  }
	*/
	// String + Bool
	if (left.type == STRING && left.type == BOOL)
	{
		string value;
		var.type = STRING;		// Change type
		if (*(bool *)right.data)
			value = "true";
		else
			value = "false";
		var.data = new string(*(char *)left.data + value);		// Assign initial value to match type
		// Assign correct value
	}

	// Bool + String
	if (left.type == BOOL && left.type == STRING)
	{
		string value;
		var.type = STRING;		// Change type
		if (*(bool *)left.data)
			value = "true";
		else
			value = "false";
		var.data = new string(value + *(char *)right.data);		// Assign initial value to match type
		// Assign correct value
	}

	// :)

	// FLOAT
	// Float/Bool + Float/Bool
	if ((left.type == FLOAT || left.type == BOOL) && (right.type == FLOAT || right.type == BOOL))
	{
		var.type = FLOAT;		// Change type
		var.data = new float(*(float *)left.data + *(float *)right.data);		// Assign initial value to match type
		// Assign correct value
	}


	// BOOL

	// Bool + Bool
	if (left.type == BOOL && left.type == STRING)
	{
		var.type = BOOL;		// Change type
		var.data = new bool(*(bool *)left.data + *(bool *)right.data);		// Assign initial value to match type

		// Assign correct value
	}

	return var;
}

bool Lexer::OpGreat(Variable left, Variable right)
{
	// String
	if (left.type == STRING && right.type == STRING)
		return (*(char *)left.data > *(char *)right.data);

	// INT
	if (left.type == INT && right.type == INT)
		return (*(int *)left.data > *(int *)right.data);

	// FLOAT
	if (left.type == FLOAT && right.type == FLOAT)
		return (*(float *)left.data > *(float *)right.data);

	cerr << "Function: GreatertThabnOp. Line Number: " << currentLine << "Not right type to compare" << endl;
	exit(1);
}

bool Lexer::OpLess(Variable left, Variable right)
{
	// String
	if (left.type == STRING && right.type == STRING)
		return (*(char *)left.data < *(char *)right.data);

	// INT
	if (left.type == INT && right.type == INT)
		return (*(int *)left.data < *(int *)right.data);

	// FLOAT
	if (left.type == FLOAT && right.type == FLOAT)
		return (*(float *)left.data < *(float *)right.data);

	cerr << "Function: LessThanOp. Line Number: " << currentLine << "Not right type to compare" << endl;
	exit(1);
}

bool Lexer::OpLessEqual(Variable left, Variable right)
{
	// String
	if (left.type == STRING && right.type == STRING)
		return (*(char *)left.data <= *(char *)right.data);

	// INT
	if (left.type == INT && right.type == INT)
		return (*(int *)left.data <= *(int *)right.data);

	// FLOAT
	if (left.type == FLOAT && right.type == FLOAT)
		return (*(float *)left.data <= *(float *)right.data);

	cerr << "Function: LessThanOrEqualOp. Line Number: " << currentLine << "Not right type to compare" << endl;
	exit(1);
}

bool Lexer::OpGreatEqual(Variable left, Variable right)
{
	// String
	if (left.type == STRING && right.type == STRING)
		return (*(char *)left.data >= *(char *)right.data);

	// INT
	if (left.type == INT && right.type == INT)
		return (*(int *)left.data >= *(int *)right.data);

	// FLOAT
	if (left.type == FLOAT && right.type == FLOAT)
		return (*(float *)left.data >= *(float *)right.data);

	cerr << "Function: GreaterThanOrEqualOp. Line Number: " << currentLine << "Not right type to compare" << endl;
	exit(1);
}

bool Lexer::OpOr(Variable left, Variable right)
{
	if (left.type == BOOL && right.type == BOOL)
	{
		return *(bool *)left.data || *(bool *)right.data;
	}

	else
	{
		cerr << "invalid variable type" << endl;
		exit(1);
	}
}

bool Lexer::OpAnd(Variable left, Variable right)
{
	if (left.type == BOOL && right.type == BOOL)
	{
		return *(bool *)left.data && *(bool *)right.data;
	}

	else
	{
		cerr << "invalid variable type" << endl;
		exit(1);
	}
}

bool Lexer::OpCompare(Variable left, Variable right)
{
	if (left.type == BOOL && right.type == BOOL)
	{
		return *(bool *)left.data == *(bool *)right.data;
	}

	else
	{
		cerr << "invalid variable type" << endl;
		exit(1);
	}
}

bool Lexer::OpInvCompare(Variable left, Variable right)
{
	if (left.type == BOOL && right.type == BOOL)
	{
		return *(bool *)left.data != *(bool *)right.data;
	}

	else
	{
		cerr << "invalid variable type" << endl;
		exit(1);
	}
}

int Lexer::numTabs(string line)
{
	int num = 0; 
	for(int i = 0; i < line.size(); i++)
	{
		if(line[i] == '\t')
			num++;
		else
			return num;
	}
	return num;
}

int Lexer::FindPCBack(bool elseOk)
{
	int tabCount = numTabs(fileLines[currentLine]);
	for(int i = currentLine + 1; i<fileLines.size(); i++)
	{
		int tabsOfLine = numTabs(fileLines[i]);
		if(fileLines[i].size() >= tabsOfLine + 4 && fileLines[i].substr(tabsOfLine, 4) == "else")
		{
			if(elseOk)
				return i;
		}
		else if(tabsOfLine <= tabCount)
			return i;
	}
}

