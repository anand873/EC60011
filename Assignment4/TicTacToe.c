// Author: AnandRaj
// Roll: 17EC10003
// Assignment: 4

// Write a program to ive the optimal move for a given position in Tic Tac Toe.

#include <stdio.h>
#include <stdlib.h>

char P[3][3];
char Q[3][3];
const int INF = 1000;
int maxlevel=4;

// Function to find minimum of two integers
int min(int a,int b)
{
	return (a<b)*a + (a>=b)*b;
}

// Function to find maximum of two integers
int max(int a,int b)
{
	return (a>=b)*a + (a<b)*b;
}

// Function to make two Matrices equal
void make_equal(char A[3][3], char B[3][3])
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			A[i][j]=B[i][j];
		}
	}
}

// Function to calculate the score of a given position
int score(char M[3][3], int played)
{
	int first=0,second=0;

	// Rows
	for(int i=0;i<3;i++)
	{
		int x=0,o=0;
		for(int j=0;j<3;j++)
		{
			if(M[i][j]=='X') x++;
			else if(M[i][j]=='O') o++;
		}
		if(x==0&&o) second++;
		else if(x&&o==0) first++; 

		if(played&&x==3) return INF;
		else if(!played&&o==3) return -INF;
	}

	// Columns
	for(int j=0;j<3;j++)
	{
		int x=0,o=0;
		for(int i=0;i<3;i++)
		{
			if(M[i][j]=='X') x++;
			else if(M[i][j]=='O') o++;
		}
		if(x==0&&o) second++;
		else if(x&&o==0) first++; 

		if(played&&x==3) return INF;
		else if(!played&&o==3) return -INF;
	}

	// Diagonal - 1
	int x=0,o=0;
	for(int i=0;i<3;i++)
	{
		if(M[i][i]=='O') o++;
		else if(M[i][i]=='X') x++;
	}
	if(x==0&&o) second++;
	else if(x&&o==0) first++;

	if(played&&x==3) return INF;
	else if(!played&&o==3) return -INF;

	// Diagonal - 2
	x=0;o=0;
	for(int i=0;i<3;i++)
	{
		if(M[i][2-i]=='O') o++;
		else if(M[i][2-i]=='X') x++;
	}
	if(x==0&&o) second++;
	else if(x&&o==0) first++;

	if(played&&x==3) return INF;
	else if(!played&&o==3) return -INF;

	return first-second;
}

// Function to calculate the score of a position using look ahead.
int scorePosition(char M[3][3],int played,int level)
{
	// Handle Corner Cases: Already won or out of space
	int curr_score = score(M,played);
	if(level==maxlevel) return curr_score;
	if((played&&curr_score==INF)||(!played&&curr_score==-INF)) return curr_score;
	
	// Initialize score
	int score_min = 2*INF;
	int score_max = -2*INF;

	char N[3][3];
	make_equal(N,M);

	// Find the score using lookahead.
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(M[i][j]!='-') continue;
			char T[3][3];
			make_equal(T,M);
			if(!played) T[i][j]='X';
			else T[i][j]='O';

			if(!played)
			{
				score_max = max(score_max,scorePosition(T,1-played,level+1));
			}
			else
			{
				score_min = min(score_min,scorePosition(T,1-played,level+1));
			}
		}
	}

	if(!played) return score_max;
	else return score_min;
}

// Function to chose the best move
void findBestMove(char M[3][3], int first)
{
	char N[3][3];
	make_equal(N,M);

	int score_min = 2*INF;
	int score_max = -2*INF;

	// Check for every possible position,
	// the score of the new position using lookahead

	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(M[i][j]!='-') continue;

			char T[3][3];
			make_equal(T,M);

			if(first) T[i][j]='X';
			else T[i][j]='O';
			int score_this = scorePosition(T,first,1);

			// Update according to first or second player
			if(first)
			{
				if(score_this>score_max)
				{
					score_max=score_this;
					make_equal(N,T);
				}
			}
			else
			{
				if(score_this<score_min)
				{
					score_min=score_this;
					make_equal(N,T);
				}	
			}
		}
	}
	make_equal(M,N);
} 

int main()
{
	printf("Enter the current position: \nUse 'X' for first player and 'O' for second player.\nUse '-' For empty places!\nAn Example of a valid input is:\n- - X\nX O -\n- O X\n\nEnter Here:\n");
	
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			scanf("%s",&P[i][j]);
		}
	}

	char player;
	int first;
	printf("\nEnter Whose turn is now:\n'X' for first player and 'O' for second player: ");
	scanf("%s",&player);
	if(player=='X') first=1;
	else first=0;

	// Find the max number of empty spaces
	int level = 0;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(P[i][j]=='-') level++;
		}
	}
	maxlevel = min(level,maxlevel);

	findBestMove(P,first);
	printf("\nThe position of the board with the best move played is:\n");
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			printf("%c ",P[i][j]);
		}
		printf("\n");
	}
}