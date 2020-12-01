/////////////////Character Stack//////////////////

typedef struct charStack
{
	char A[MAX];
	int idx;
}stack_char;

void init_char(stack_char *S)
{
	S->idx = -1;
}

void push_char(stack_char *S,char x)
{
	S->A[++S->idx] = x; 
}

char pop_char(stack_char *S)
{
	return S->A[S->idx--];
}

bool empty_char(stack_char *S)
{
	return S->idx==-1;
}

char top_char(stack_char *S)
{
	return S->A[S->idx];
}

/////////////////Integer Stack//////////////////

typedef struct doubleStack
{
	double A[MAX];
	int idx;
}stack_double;

void init_double(stack_double *S)
{
	S->idx = -1;
}

void push_double(stack_double *S,int x)
{
	S->A[++S->idx] = x; 
}

double pop_double(stack_double *S)
{
	return S->A[S->idx--];
}

bool empty_double(stack_double *S)
{
	return S->idx==-1;
}

double top_double(stack_double *S)
{
	return S->A[S->idx];
}