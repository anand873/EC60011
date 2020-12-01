/////////////////Queue//////////////////
#define MAX 1000
typedef struct Queue
{
	TYPE A[MAX];
	int head=0,tail=-1;
	void push(TYPE x)
	{
		A[++tail] = x; 
	}

	void pop()
	{
		head++;
	}

	bool empty()
	{
		return tail<head;
	}

	TYPE front()
	{
		return A[head];
	}
}queue;
/////////////Queue////////////////////