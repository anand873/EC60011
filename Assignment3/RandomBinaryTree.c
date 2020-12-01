// Author: AnandRaj
// Roll: 17EC10003
// Assignment: 3

// Write a program to generate a Random Binary Tree and to traverse it in Preorder.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Change here the size of the Tree.
// Use smaller size for clear visualization.
#define MAX 30
int A[MAX];

// General Node Definition
typedef struct Node
{
	char info;
	struct Node *left;
	struct Node *right;
}Node;

#define TYPE Node*
#include "stack.h"

// Function to create a new Node
Node* getnode(int x)
{
	Node *A;
	A = (Node *)malloc(sizeof(Node));
	A->info = x;
	A->left = NULL;
	A->right = NULL;
}

// Function to generate the tree.
// Uses the values in the Array A.
// Randomly chooses the root, 
// and creates two random Binary trees
// from the left and right part using recursion 
Node* genRandTree(int start, int end)
{
	if(end<start) return NULL;
	int mid = start + rand()%(end-start+1);
	Node* root;
	root = getnode(A[mid]);
	root->left = genRandTree(start,mid-1);
	root->right = genRandTree(mid+1,end);
	return root;
}

// Function to recursively print Preorder traversal of the Tree.
void recPreorder(Node* root)
{
	if(root==NULL) return;
	printf("%d ",root->info);
	recPreorder(root->left);
	recPreorder(root->right);
}

// Function to print Preorder traversal using stack.
void nonRecPreorder(Node* root)
{
	if(root==NULL) return;
	stack S;
	init(&S);
	push(&S,root);
	while(!empty(&S))
	{
		Node* curr = pop(&S);
		printf("%d ",curr->info);
		if(curr->right) push(&S,curr->right);
		if(curr->left) push(&S,curr->left);
	}
}

// Function to visualise the tree
// Prints the value of the root node, 
// and its left and right nodes
// 0 represents NULL
void printNodeLeftRight(Node* root)
{
	if(root==NULL) return;
	printf("%d\t%d\t%d\n",root->info,root->left?root->left->info:0,root->right?root->right->info:0);
	printNodeLeftRight(root->left);
	printNodeLeftRight(root->right);
}

// Main driver function
int main()
{
	srand(time(NULL));
	for(int i=0;i<MAX;i++)
	{
		A[i] = 1+rand()%50;
	}
	
	printf("Generting a Random Binary Tree\n");
	Node *root;
	root = genRandTree(0,MAX-1);
	printf("Binary Tree Generated\n\n");
	
	printf("Generting the Preorder Traversal of the Tree using Recursion\n");
	recPreorder(root);
	printf("\n\n");

	printf("Generting the Preorder Traversal of the Tree without Recursion\n");
	nonRecPreorder(root);
	printf("\n\n");


	printf("Printing for each node, its left and right child nodes\nNote: '0' represents NULL\n\n");
	printf("Node\tLeft\tRight\n");
	printf("---------------------\n");
	printNodeLeftRight(root);
}