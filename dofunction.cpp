Variable Lexer::DoFunction(string funcName, vector<Variable> &arguments)
{
	//set return value to null
	if(funcName == "print")
	{
		for (unsigned i = 0; i < arguments.size(); i++)
		{
			if(arguments[i].type == INT)
			{
				cout << (int)(*arguments[i].data) << endl;
			}
			else if(arguments[i].type == STRING)
			{
				cout << (char*)arguments[i].data << endl;
			}
			else if(arguments[i].type == FLOAT)
			{
				cout << (float*)arguments[i].data << endl;
			}
			else
			{
				cout << (bool*)arguments[i].data << endl;
			}
		}
	}
	for(unsigned i = 0; i < vectorOfFunctions.size(); i++)
	{
		
		//make sure we have the proper var types
		if(funcName == vectorOfFunctions[i].name && 
			 vectorOfFunctions[i].size() == arguments.size())
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
	
				Variable ret;
				ret.value = 0;			
				//save the program counter temporarily
				int prevCurrentLine = currentLine;
	
				GoThroughFunction(func);
				//reset
				currentLine = prevCurrentLine;
				return Variable;
			}
			
		}
	}
	cerr << "No function call found for " << funcName << endl;
	exit(1);
	
}
