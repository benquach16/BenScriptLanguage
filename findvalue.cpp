
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
		ret.data = name;
		variables.push_back(ret);
		return variables[variables.size()-1];
	}
	else if (name[0] > '0' && name[0] < '9')
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
		
		iss >> *t;
		ret.data = t;
		variables.push_back(ret);
		return variables[variables.size()-1];
	}
	else if (name[0] == '.')
	{
		//float literal
	}
	else if (name == "true" || name == "false")
	{

	}
	cerr << "Variable " << name << " not declared in scope." << endl;
	exit(1);
}
