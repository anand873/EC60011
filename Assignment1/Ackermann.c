// Assignment 1
// 
// Author: Anand Raj
// 17EC10003
// 09-09-2000

#include <stdio.h>

// Ackermann Recursive

int Ackermann_recursive(int i, int j)
{
	if(i==1) return 1ll<<j;
	if(j==1) return Ackermann_recursive(i-1,2);
	return Ackermann_recursive(i-1,Ackermann_recursive(i,j-1));
}

// Ackermann Iterative

int Ackermann_iterative(int i, int j)
{
	int Stack[20];
	int idx = 0;

	Stack[idx] = i;
	while(idx!=-1)
	{
		i = Stack[idx--];
		if(i==1)
		{
			j = 1ll<<j;
		}
		else if(j==1)
		{
			Stack[++idx] = i-1;
			j++;
		}
		else
		{
			Stack[++idx] = i-1;
			Stack[++idx] = i;
			j--;
		}
	}
	return j;
}

// Helper Functions To Print!

void print_Ackermann_recursive()
{
	printf("Using Recursive Ackermann Function\n\n");
	printf("i\\j |\t");
	printf("1\t2\t3\t4\n");
	printf("-----------------------------------\n");
	for(int i=1;i<=3;i++)
	{
		printf("%d   |\t",i);
		for(int j=1;j<=4;j++)
		{
			if(i==2&&j==4||i==3&&j>1) printf("---\t");
			else printf("%d\t",Ackermann_recursive(i,j));
		}
		printf("\n");
	}
	printf("\n");
}

void print_Ackermann_iterative()
{
	printf("Using Iterative Ackermann Function\n\n");
	printf("i\\j |\t");
	printf("1\t2\t3\t4\n");
	printf("-----------------------------------\n");
	for(int i=1;i<=3;i++)
	{
		printf("%d   |\t",i);
		for(int j=1;j<=4;j++)
		{
			if(i==2&&j==4||i==3&&j>1) printf("---\t");
			else printf("%d\t",Ackermann_iterative(i,j));
		}
		printf("\n");
	}
	printf("\n");

}


int main()
{
	// Use this to get formatted output!
	print_Ackermann_recursive();
	print_Ackermann_iterative();
	printf("Note: \"---\" represents overflow!\n");

	// Uncomment this to check individual pairs!
	// printf("%lld\n",Ackermann_recursive(2,3));
	// printf("%lld\n",Ackermann_iterative(2,3));

}	