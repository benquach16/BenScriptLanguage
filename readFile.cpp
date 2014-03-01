#include <iostream>
#include <fstream>

using namespace std;

void readFile(char * filePath)
{
  // checks if file exists
  ifstream file;
  file.open(filename);
  
  if(!file.isopen())
    {
      cerr << "File doesn't exist" << endl;
      return 1;
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
