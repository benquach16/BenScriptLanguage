Variable Lexer::doLine(vector<string> &tokens)
{
	//cerr << "start" << endl;
	if (tokens.size() > 1)
	{
		// shave outer parens
		if (tokens.at(0) == "(" && tokens.at(tokens.size() - 1) == ")")
		{
			tokens.pop_back();
			tokens.erase(tokens.begin());
		}

		int mid;

		// checks all assignment operators
		mid = findOperator1(tokens);

		// checks or
		if (mid == -1)
			mid = findOperator2(tokens);

		// checks and
		if (mid == -1)
			mid = findOperator3(tokens);

		// checks equality comparison
		if (mid == -1)
			mid = findOperator4(tokens);

		// checks less than greater than comparison
		if (mid == -1)
			mid = findOperator5(tokens);

		// checks add and subtract
		if (mid == -1)
			mid = findOperator6(tokens);

		// checks multiply and divide
		if (mid == -1)
			mid = findOperator7(tokens);

		cout << "mid: " << mid << endl;
		if (mid != -1)
			return split(mid, tokens);

		//check if its a function
		if (tokens.size() > 3)
		{
			//we assume function call
			if (tokens[1] == "(" && tokens[tokens.size() - 1] == ")")
			{
				//proper function call
				SetupFunction(1, tokens);
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
		return FindValue(token[0]);
	}
	else
	{
		cerr << "Function: DoLine. Syntax error on line: " << currentLined << endl;
		exit(1);
	}
}