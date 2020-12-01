// Assignment 1
// 
// Author: Anand Raj
// 17EC10003
// 09-09-2000

//Note: Please use -lm while compiling if <math.h> doesn't work!
//		Please Put stack.h file in the same directory as this file.

#define MAX 10000
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "stack.h"


void reverse(char s[])
{
	int n = strlen(s);
	for(int i=0;i<n/2;i++)
	{
		char c = s[i];
		s[i] = s[n-1-i];
		s[n-1-i] = c;
	}

}

bool isOperator(char c)
{
	return (c=='+'||c=='-'||c=='*'||c=='/'||c=='^'||c=='('||c==')');
}

int precedence(char operator)
{
	if(operator=='+'||operator=='-') return 2;
	else if(operator=='*'||operator=='/') return 4;
	else if(operator=='^') return 6;
	else return 1;
}

void Infix_To_Prefix_With_Parenthesis(char Infix[],char Prefix[])
{
	int n = strlen(Infix);
	char curr;
	stack_char S;
	init_char(&S);
	push_char(&S,'#');
	reverse(Infix);

	for(int i=0;i<n;i++)
	{
		if(Infix[i]=='(') Infix[i]=')';
		else if(Infix[i]==')') Infix[i]='(';
	}

	int j = 0;
	for(int i=0;i<n;i++)
	{
		curr = Infix[i];
		if(!isOperator(curr))
		{
			Prefix[j++] = curr;
		}
		else
		{
			if(curr=='(')
			{
				push_char(&S,curr);
			}
			else if(curr==')')
			{
				while(top_char(&S)!='(')
				{
					Prefix[j++] = pop_char(&S);
				}
				pop_char(&S);
			}
			else
			{
				while(precedence(top_char(&S))>precedence(curr))
				{
					Prefix[j++] = pop_char(&S);
				}
				push_char(&S,curr);
			}
			
		}
	}

	while(top_char(&S)!='#')
	{
		Prefix[j++] = pop_char(&S);
	}
	Prefix[j] = '\0';
}

void Infix_To_Prefix_Without_Parenthesis(char Infix[],char Prefix[])
{
	int n = strlen(Infix);
	char curr;
	stack_char S;
	init_char(&S);
	push_char(&S,'#');
	reverse(Infix);
	int j = 0;
	for(int i=0;i<n;i++)
	{
		curr = Infix[i];
		if(!isOperator(curr))
		{
			Prefix[j++] = curr;
		}
		else
		{
			while(precedence(top_char(&S))>precedence(curr))
			{
				Prefix[j++] = pop_char(&S);
			}
			push_char(&S,curr);
		}
	}

	while(top_char(&S)!='#')
	{
		Prefix[j++] = pop_char(&S);
	}
	Prefix[j] = '\0';
}

double Evaluate_Prefix_Expression(char Prefix[])
{
	int n = strlen(Prefix);
	stack_double S;
	init_double(&S);
	for(int i=n-1;i>=0;i--)
	{
		int curr = Prefix[i];
		if(!isOperator(curr))
		{
			push_double(&S,curr-'0');
		}
		else
		{
			double first = pop_double(&S);
			double second = pop_double(&S);
			if(curr=='+')
			{
				push_double(&S,first+second);
			}
			else if(curr=='-')
			{
				push_double(&S,first-second);
			}
			else if(curr=='*')
			{
				push_double(&S,first*second);
			}
			else if(curr=='/')
			{
				push_double(&S,first/second);
			}
			else
			{
				push_double(&S,pow(first,second));
			}
		}
	}
	return top_double(&S);
}

int main()
{
	puts("Input a valid Infix Expression with Parenthesis");
	
	char Infix[MAX],Prefix[MAX];
	scanf("%s",Infix);
	Infix_To_Prefix_With_Parenthesis(Infix,Prefix);
	reverse(Prefix);
	puts(Prefix);

	puts("Input a valid Infix Expression without Parenthesis");
	
	char Infix2[MAX],Prefix2[MAX];
	scanf("%s",Infix2);
	Infix_To_Prefix_Without_Parenthesis(Infix2,Prefix2);
	reverse(Prefix2);
	puts(Prefix2);

	puts("Input a valid Prefix Expression to evaluate");

	char Prefix3[MAX];
	double ans;
	scanf("%s",Prefix3);
	ans = Evaluate_Prefix_Expression(Prefix3);
	printf("%lf\n",ans);


}