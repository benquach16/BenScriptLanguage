vector<string> TokenizeLine(const string &str)
{
  vector<string> tokens;

  int i = 0;

  string curToken;

  bool isName = false;

  // 
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

	  tokens.push_back(static_cast<string>(str[i]));
	}
      else if(str[i] == '=' || str[i] == '+' || str[i] == '-' ||
	      str[i] == '/' || str[i] == '*' || str[i] == '>' ||
	      str[i] == '<')
	{
	  if(curToken.size() > 0)
	    {
	      tokens.push_back(curToken);
	      curToken = "";
	    }

	  if(str.size() < i + 1 && (str[i+1] == '=') || (str[i+1] == '+') ||
	     (str[i+1] == '-') && str[i] == str[i+1])
	    {
	      tokens.push_back(static_cast<string>(str[i]));
	      tokens.push_back(static_cast<string>(str[i+1]));
	    }
	}
    }
