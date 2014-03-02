Variable Lexer::OpMinus(Variable left, Variable right)
{
  Variable var;

  //case float - float
  if(left.VariableTypes.FLOAT && right.VariableTypes.FLOAT)
  {
    var.VariableTypes = FLOAT;
    var.data = new float(0);
    var -> data = *(float*) left.data - *(float *) right.data;
  }

  // case int - int
  else if(left.VariableTypes.INT && right.VariableTypes.INT)
  {
    var.VariableTypes = INT;
    var.data = new int(0);
    var -> data = *(int *) left.data - *(int *) right.data;
  }

  // case int - float
  else if(left.VariableTypes.INT && right.VariableTypes.FLOAT)
  {
    var.VariableTypes = INT;
    var.data = new int(0);
    var -> data = *(int *) left.data - *(int *) right.data;
  }

  // case float - int
  else if(left.VariableTypes.FLOAT && right.VariableTypes.INT)
  {
    var.VariableTypes = INT;
    var.data = new int(0);
    var -> data = *(int *) left.data - *(int *) right.data;
  }
 
  else
  {
    cerr << "invalid variable type" << endl;
    exit(1);
  }

  return var;
}

Variable Lexer::OpMultiply(Variable left, Variable right)
{
  Variable var;

  //case float - float
  if(left.VariableTypes.FLOAT && right.VariableTypes.FLOAT)
  {
    var.VariableTypes = FLOAT;
    var.data = new float(0);
    var -> data = *(float*) left.data * *(float *) right.data;
  }

  // case int - int
  else if(left.VariableTypes.INT && right.VariableTypes.INT)
  {
    var.VariableTypes = INT;
    var.data = new int(0);
    var -> data = *(int *) left.data * *(int *) right.data;
  }

  // case int - float
  else if(left.VariableTypes.INT && right.VariableTypes.FLOAT)
  {
    var.VariableTypes = INT;
    var.data = new int(0);
    var -> data = *(int *) left.data * *(int *) right.data;
  }

  // case float - int
  else if(left.VariableTypes.FLOAT && right.VariableTypes.INT)
  {
    var.VariableTypes = INT;
    var.data = new int(0);
    var -> data = *(int *) left.data * *(int *) right.data;
  }
  
  else
  {
    cerr << "invalid variable type" << endl;
    exit(1);
  }

  return var;
}

Variable Lexer::OpDivide(Variable left, Variable right)
{
  Variable var;

  //case float - float
  if(left.VariableTypes.FLOAT && right.VariableTypes.FLOAT)
  {
    var.VariableTypes = FLOAT;
    var.data = new float(0);
    var -> data = *(float*) left.data / *(float *) right.data;
  }

  // case int - int
  else if(left.VariableTypes.INT && right.VariableTypes.INT)
  {
    var.VariableTypes = INT;
    var.data = new int(0);
    var -> data = *(int *) left.data / *(int *) right.data;
  }

  // case int - float
  else if(left.VariableTypes.INT && right.VariableTypes.FLOAT)
  {
    var.VariableTypes = INT;
    var.data = new int(0);
    var -> data = *(int *) left.data / *(int *) right.data;
  }

  // case float - int
  else if(left.VariableTypes.FLOAT && right.VariableTypes.INT)
  {
    var.VariableTypes = INT;
    var.data = new int(0);
    var -> data = *(int *) left.data / *(int *) right.data;
  }
  
  else
  {
    cerr << "invalid variable type" << endl;
    exit(1);
  }

  return var;
}

Variable Lexer::OpMod(Variable left, Variable right)
{
  Variable var;

  if(left.VariableTypes.INT && right.VariableTypes.INT)
  {
    var.VariableTypes = INT;
    var.data = new int(0);
    var -> data = *(int *) left.data % *(int *) right.data;
  }

  else
  {
    cerr << "invalid variable type" << endl;
    exit(1);
  }

  return var;
}

bool Lexer::OpOr(Variable left, Variable right)
{
  if(left.VariableTypes.BOOL && right.VariableTypes.BOOL)
  {
    return *(bool *) left.data || *(bool *) right.data;
  }

  else
  {
    cerr << "invalid variable type" << endl;
    exit(1);
  }
}

bool Lexer::OpAnd(Variable left, Variable right)
{
  if(left.VariableTypes.BOOL && right.VariableTypes.BOOL)
  {
    return *(bool *) left.data && *(bool *) right.data;
  }

  else
  {
    cerr << "invalid variable type" << endl;
    exit(1);
  }
}

bool Lexer::OpCompare(Variable left, Variable right)
{
  if(left.VariableTypes.BOOL == right.VariableTypes.BOOL)
  {
    return *(bool *) left.data == *(bool *) right.data;
  }

  else
  {
    cerr << "invalid variable type" << endl;
    exit(1);
  }
}

bool Lexer::OpInvCompare(Variable left, Variable right)
{
  if(left.VariableTypes.BOOL && right.VariableTypes.BOOL)
  {
    return *(bool *) left.data != *(bool *) right.data;
  }

  else
  {
    cerr << "invalid variable type" << endl;
    exit(1);
  }
}

Variable Lexer::OpPlusPlus(Variable var)
{
  Variable temp;
  if(var.VariableTypes.INT)
  {
   temp.variableTypes = INT;
    temp.data = new int(1);
    UpdateValue(var.name, OpPlus(var, temp));
  }

  if(var.VariablesTypes.FLOAT)
  {
    temp.VariableTypes = FLOAT;
    temp.data = new float(1.0);
    UpdateValue(var.name, OpPlus(var, temp));
  }

  else
  {
    cerr << "invalid variable type" << endl;
    exit(1);
  }

  return var;
}

Variable Lexer::OpMinusMinus(variable var)
{
  Variable temp;
  if(var.VariableTypes.INT)
  {
    temp.variableTypes = INT;
    temp.data = new int(1);
    UpdateValue(var.name, OpMinus(var, temp));
  }

  if(var.VariablesTypes.FLOAT)
  {
    temp.VariableTypes = FLOAT;
    temp.data = new float(1.0);
    UpdateValue(var.name, OpMinus(var, temp));
  }

  else
  {
    cerr << "invalid variable type" << endl;
    exit(1);
  }

  return var;
}

Variable Lexer::OpNot(Variable var)
{
  Variable temp;
  if(var.VariableTypes.BOOL)
  {
    temp.VariableTypes = var.VariableTypes;
    temp -> data = new bool(!*(bool *) var.data);
  }

  else
  {
    cerr << "invalid variable type" << endl;
    exit(1);
  }
}
