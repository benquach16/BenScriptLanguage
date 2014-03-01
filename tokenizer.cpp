vector<string> TokenizeLine(const string &str)
{
  vector<string> tokens;

  int i = 0;

  string curToken;

  bool isName = false;

  while(i != str.size() && str[i] != '#')
    {
      if(str[i] == '(' || str[i] == ')' || 
	 str[i] == ',' || str[i] == '?' || str == ':')
	{
	  if(curToken.size() > 0)
	    {
	      tokens.push_back(curToken);
	      curToken = "";
	    }
	  tokens.push_back(str.substr();
	}
    }
