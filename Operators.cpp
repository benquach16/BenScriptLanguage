// add

// float and int returns int
// string + int = concatonates 
// int + string = concatonates 
// bool + string = "true" + concatonate 
// bool + int add 1 if true

Variable Lexer::AddOp(Variable &left, Variable &right)
{
	Variable var; 


				// INT
	// (Int + Int/Float) OR (Float + Int) OR (Int/Bool + Int/Bool)
	if ((left.VariableTypes.INT && (right.VariableTypes.INT || right.VariableTypes.FLOAT)) 
		|| (left.VariableTypes.FLOAT && right.VariableTypes.INT)
		|| ( (left.VariableTypes.INT || left.VariableTypes.BOOL) && (right.VariableTypes.BOOL || right.VariableTypes.INT) )

	{
		var.VariableType = INT;		// Change type
		var.data = new int(0);		// Assign initial value to match type
		var->data = *(int *)left.data + *(int *)right.data; // Assign correct value
	}

	
			// STRING
	// (Int/String/Float + String/Int/Float)
	if ((left.VariableTypes.INT || left.VariableTypes.STRING || left.VariableTypes.FLOAT) && (right.VariableTypes.STRING || right.VariableTypes.INT || right.VariableTypes.FLOAT))
	{
		var.VariableType = STRING;		// Change type
		var.data = new string("");		// Assign initial value to match type
		var->data = *(char *)left.data + *(char *)right.data; // Assign correct value
	}

	// String + Bool
	if (left.VariableTypes.STRING && left.VariableTypes.BOOL)
	{
		var.VariableType = STRING;		// Change type
		var.data = new string("");		// Assign initial value to match type
		
		if (*(bool *)right.data)
			value = "true";
		else
			value = "false";
	
		var->data = *(char *)left.data + value; // Assign correct value
	}

	// Bool + String
	if (left.VariableTypes.BOOL && left.VariableTypes.STRING)
	{
		var.VariableType = STRING;		// Change type
		var.data = new string("");		// Assign initial value to match type

		if (*(bool *)left.data)
			value = "true";
		else
			value = "false";

		var->data = value + *(char *)right.data; // Assign correct value
	}


	
			// FLOAT
	// Float/Bool + Float/Bool
	if ((left.VariableTypes.FLOAT || left.VariableTypes.BOOL) && (right.VariableTypes.FLOAT || right.VariableTypes.BOOL))
	{
		var.VariableType = FLOAT;		// Change type
		var.data = new float(0.0);		// Assign initial value to match type
		var->data = *(float *)left.data + *(float *)right.data; // Assign correct value
	}

	
				// BOOL

	// Bool + Bool
	if (left.VariableTypes.BOOL && left.VariableTypes.STRING)
	{
		var.VariableType = STRING;		// Change type
		var.data = new string("");		// Assign initial value to match type

		var->data = *(bool *)left.data + *(bool *)right.data; // Assign correct value
	}
	
	return var;
}

bool Lexer::GreaterThanOp(Variable &left, Variable &right)
{
	// String
	if (left.VariableTypes.STRING && right.VariableTypes.STRING)
		return (*(char *)left.data > *(char *)right.data;

	// INT
	if (left.VariableTypes.INT && right.VariableTypes.INT)
		return (*(int *)left.data > *(int *)right.data;

	// FLOAT
	if (left.VariableTypes.FLOAT && right.VariableTypes.FLOAT)
		return (*(float *)left.data > *(float *)right.data;

	cerr << "Function: GreatertThabnOp. Line Number: " << numemberLine << "Not right type to compare" << endl; 
	exit(1);
}

bool Lexer::LessThanOp(Variable &left, Variable &right)
{
	// String
	if (left.VariableTypes.STRING && right.VariableTypes.STRING)
		return (*(char *)left.data < *(char *)right.data;

	// INT
	if (left.VariableTypes.INT && right.VariableTypes.INT)
		return (*(int *)left.data < *(int *)right.data;

	// FLOAT
	if (left.VariableTypes.FLOAT && right.VariableTypes.FLOAT)
		return (*(float *)left.data < *(float *)right.data;

	cerr << "Function: LessThanOp. Line Number: " << numemberLine << "Not right type to compare" << endl;
	exit(1);
}

bool Lexer::LessOrEqualThanOp(Variable &left, Variable &right)
{
	// String
	if (left.VariableTypes.STRING && right.VariableTypes.STRING)
		return (*(char *)left.data <= *(char *)right.data;

	// INT
	if (left.VariableTypes.INT && right.VariableTypes.INT)
		return (*(int *)left.data <= *(int *)right.data;

	// FLOAT
	if (left.VariableTypes.FLOAT && right.VariableTypes.FLOAT)
		return (*(float *)left.data <= *(float *)right.data;

	cerr << "Function: LessThanOrEqualOp. Line Number: " << numemberLine << "Not right type to compare" << endl;
	exit(1);
}

bool Lexer::GreaterOrEqualThanOp(Variable &left, Variable &right)
{
	// String
	if (left.VariableTypes.STRING && right.VariableTypes.STRING)
		return (*(char *)left.data >= *(char *)right.data;

	// INT
	if (left.VariableTypes.INT && right.VariableTypes.INT)
		return (*(int *)left.data >= *(int *)right.data;

	// FLOAT
	if (left.VariableTypes.FLOAT && right.VariableTypes.FLOAT)
		return (*(float *)left.data >= *(float *)right.data;

	cerr << "Function: GreaterThanOrEqualOp. Line Number: " << numemberLine << "Not right type to compare" << endl;
	exit(1);
}

