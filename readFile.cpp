#include <iostream>
#include <fstream>

using namespace std;

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

  while(!file.eof())
	{
		getline(&file, line);
		fileLines.push_back(line);
	}

  file.close();
}


int main()
{
  return 0;
}
