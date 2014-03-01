void Lexer::SetupFunction(int leftParen, vector<string> &tokens)
{
	int leftParensCount = 0;
	vector<int> commas;						//Stores indexes of commas and last )

	for (int i = leftParens; i < tokens.size(); i++)
	{
		if (tokens[i] == "(")				// If a left parenthesis is found
			leftParensCount++;				// increment 
		else if (tokens[i] == ")")			// otherwise if a right parenthesis is found
		{
			if (leftParensCount == 0)		// check if this should be the last right parens
				commas.push_back(i);	// and add index to commas vector
				return commas;
			else
				leftParensCount--;			// otherwise it's not last right parens and decrement
		}
		else if (tokens[i][0] == ',' && leftParensCount == 0) //If it's the last comma 
			commas.push_back(i);	// Add that shit
		else
			cerr << "ERROR at line: " << currentLine << " Found in Function: setupFunction. You are missing at least one right parenthesis" << endl;
	
		
		
	
	
		
	
	
}

