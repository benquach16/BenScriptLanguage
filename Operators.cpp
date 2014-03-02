// add

// float and int returns int
// string + int = concatonates 
// int + string = concatonates 
// bool + string = "true" + concatonate 
// bool + int add 1 if true

Variable Lexer::OpPlus(Variable left, Variable right)
{
	Variable var; 


				// INT
	// (Int + Int/Float) OR (Float + Int) OR (Int/Bool + Int/Bool)
	if ((left.type.INT && (right.type.INT || right.type.FLOAT)) 
		|| (left.type.FLOAT && right.type.INT)
		|| ( (left.type.INT || left.type.BOOL) && (right.type.BOOL || right.type.INT) )

	{
		var.VariableType = INT;		// Change type
		var.data = new int(0);		// Assign initial value to match type
		var->data = *(int *)left.data + *(int *)right.data; // Assign correct value
	}

	
			// STRING
	// (Int/String/Float + String/Int/Float)
	if ((left.type.INT || left.type.STRING || left.type.FLOAT) && (right.type.STRING || right.type.INT || right.type.FLOAT))
	{
		var.VariableType = STRING;		// Change type
		var.data = new string("");		// Assign initial value to match type
		var->data = *(char *)left.data + *(char *)right.data; // Assign correct value
	}

	// String + Bool
	if (left.type.STRING && left.type.BOOL)
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
	if (left.type.BOOL && left.type.STRING)
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
	if ((left.type.FLOAT || left.type.BOOL) && (right.type.FLOAT || right.type.BOOL))
	{
		var.VariableType = FLOAT;		// Change type
		var.data = new float(0.0);		// Assign initial value to match type
		var->data = *(float *)left.data + *(float *)right.data; // Assign correct value
	}

	
				// BOOL

	// Bool + Bool
	if (left.type.BOOL && left.type.STRING)
	{
		var.VariableType = STRING;		// Change type
		var.data = new string("");		// Assign initial value to match type

		var->data = *(bool *)left.data + *(bool *)right.data; // Assign correct value
	}
	
	return var;
}

bool Lexer::OpGreat(Variable left, Variable right)
{
	// String
	if (left.type.STRING && right.type.STRING)
		return (*(char *)left.data > *(char *)right.data;

	// INT
	if (left.type.INT && right.type.INT)
		return (*(int *)left.data > *(int *)right.data;

	// FLOAT
	if (left.type.FLOAT && right.type.FLOAT)
		return (*(float *)left.data > *(float *)right.data;

	cerr << "Function: GreatertThabnOp. Line Number: " << numemberLine << "Not right type to compare" << endl; 
	exit(1);
}

bool Lexer::OpLess(Variable left, Variable right)
{
	// String
	if (left.type.STRING && right.type.STRING)
		return (*(char *)left.data < *(char *)right.data;

	// INT
	if (left.type.INT && right.type.INT)
		return (*(int *)left.data < *(int *)right.data;

	// FLOAT
	if (left.type.FLOAT && right.type.FLOAT)
		return (*(float *)left.data < *(float *)right.data;

	cerr << "Function: LessThanOp. Line Number: " << numemberLine << "Not right type to compare" << endl;
	exit(1);
}

bool Lexer::OpLessEqual(Variable left, Variable right)
{
	// String
	if (left.type.STRING && right.type.STRING)
		return (*(char *)left.data <= *(char *)right.data;

	// INT
	if (left.type.INT && right.type.INT)
		return (*(int *)left.data <= *(int *)right.data;

	// FLOAT
	if (left.type.FLOAT && right.type.FLOAT)
		return (*(float *)left.data <= *(float *)right.data;

	cerr << "Function: LessThanOrEqualOp. Line Number: " << numemberLine << "Not right type to compare" << endl;
	exit(1);
}

bool Lexer::OpGreatEqual(Variable left, Variable right)
{
	// String
	if (left.type.STRING && right.type.STRING)
		return (*(char *)left.data >= *(char *)right.data;

	// INT
	if (left.type.INT && right.type.INT)
		return (*(int *)left.data >= *(int *)right.data;

	// FLOAT
	if (left.type.FLOAT && right.type.FLOAT)
		return (*(float *)left.data >= *(float *)right.data;

	cerr << "Function: GreaterThanOrEqualOp. Line Number: " << numemberLine << "Not right type to compare" << endl;
	exit(1);
}

