void doLine(const vector<string> &tokens)
{
	
	for(unsigned i = 0; i < tokens.size(); i++)
	{
		if(tokens[i] == "=")
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

			doLine(leftTokens);
			doLine(rightTokens);
			//now we can assign it
		}

		
	}

}
