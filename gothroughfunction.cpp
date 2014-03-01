void Lexer::GoThroughFunction(Function func)
{
	//loop while there is a tab
	currentLine = func.fileLine;
	while(fileLines[currentLine][0] == '\t')
	{
		doLine(TokenizeLine(fileLines[currentLine]));
		currentLine++;
	}
}
