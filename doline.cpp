void doLine(const vector<string> &tokens)
{
	if(tokens.size() > 1)
	{
		for(unsigned i = 0; i < tokens.size(); i++)
		{
			if(tokens[i] == "=" || tokens[i] == "+=" || tokens[i] == "-=" ||
				 tokens[i] == "*=" || tokens[i] == "/=" || tokens[i] == "%=")
			{
				//found the assignment operator - most important
				//split into to two vectors
				vector<string> leftTokens;
				vector<string> rightTokens;
				//allocate to these vectors
				for(unsigned n = 0; n < i; n++)
				{
					leftTokens.push_back(tokens[n]);
				}
				for(unsigned n = tokens.size(); n > i; n--)
				{
					rightTokens.push_back(tokens[n]);
				}

				//doLine(leftTokens);
				//doLine(rightTokens);
				operatorSelect(leftTokens, rightTokens, tokens[i]);
				
			}
		}
		//we didnt find the assignment so we go on to the other sijdes
		for(unsigned i = 0; i < tokens.size(); i++)
		{
			//or operator
			if(tokens[i] == "||")
			{
			}
		}
		//no or operator? lets go through it again
		for(unsigned i = 0; i < tokens.size(); i++)
		{
			if(tokens[i] == "&&")
			{
			}
		}
		//handle comparison operators
		for(unsigned i = 0; i < tokens.size(); i++)
		{
			if(tokens[i] == "==" || tokens[i] == "!=")
			{
			
			}
		}
		//handle more comparision operators
		for(unsigned i = 0; i < tokens.size(); i++)
		{
			if(tokens[i] == "<=" || tokens[i] == ">=" || tokens[i] == ">"
				 tokens[i] == "<")
			{
			
			}
		}
		//handle the arthimetic operators
		for(unsigned i = 0; i < tokens.size(); i++)
		{
		
		}
	}
}
