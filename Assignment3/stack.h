/////////////////Stack//////////////////
typedef struct Stack
{
	TYPE A[MAX];
	int idx;
}stack;

void init(stack *S)
{
	S->idx = -1;
}

void push(stack *S,TYPE x)
{
	S->A[++S->idx] = x; 
}

TYPE pop(stack *S)
{
	return S->A[S->idx--];
}

bool empty(stack *S)
{
	return S->idx==-1;
}

TYPE top_int(stack *S)
{
	return S->A[S->idx];
}
/////////////Stack////////////////////