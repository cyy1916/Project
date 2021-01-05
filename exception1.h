#pragma once
class InterpreteError
{
protected:
	int v;
public:
	InterpreteError();
	InterpreteError(int p);
	int show();
};

InterpreteError::InterpreteError()
{
	v = 0;
}

InterpreteError::InterpreteError(int p)
{
	v = p;
}

int InterpreteError::show()
{
	return v;
}
