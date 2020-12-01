// Author: AnandRaj
// Roll: 17EC10003
// Assignment: 5

// Write a program to Insert and delete nodes from a Red-Black Tree.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct NODE
{
	// Red = 1, Black = 0;
	int color,info;
	struct NODE *left, *right, *parent;
}Node;
#include "tree.h"

void RedBlackInsert(int x)
{
	// Root
	if(!Root)
	{
		Root = makeNode(x);
		Root->parent = NULL;
		Root->color = 0;
		return;
	}

	// Insert in BST
	Node *curr,*father;
	curr = Root;
	father = NULL;
	while(curr->info!=-1)
	{
		father = curr;
		if(curr->info>x)
		{
			curr = curr->left;
		}
		else curr=curr->right;
	}

	Node* newNode;
	if(x>father->info)
	{
		newNode = makeNode(x);
		father->right = newNode;
		newNode->parent = father;
	}
	else
	{
		newNode = makeNode(x);
		father->left = newNode;
		newNode->parent = father;
	}

	// Fix the Red-Black Tree, if there are two reds
	while(father!=NULL&&father->color==1)
	{
		if(isRight(father))
		{
			Node* uncle = (father->parent)->left;
			if(uncle->color==1)
			{
				uncle->color=0;
				father->color=0;
				father->parent->color = 1;
				father = (father->parent)->parent;
			}
			else 
			{
				if(isLeft(newNode))
				{
					newNode = newNode->parent;
					rightRotate(newNode);
				}
				newNode->color = 1;
				newNode->parent->parent->color = 1;
				leftRotate(newNode->parent->parent);
				newNode->parent->color = 0;
				return;
			}
		}
		else
		{
			Node* uncle = (father->parent)->right;
			if(uncle->color==1)
			{
				uncle->color=0;
				father->color=0;
				father->parent->color = 1;
				father = (father->parent)->parent;
			}
			else 
			{
				if(isRight(newNode))
				{
					newNode = newNode->parent;
					leftRotate(newNode);
				}
				newNode->color = 1;
				newNode->parent->parent->color = 1;
				rightRotate(newNode->parent->parent);
				newNode->parent->color = 0;
				return;
			}
		}
		if(newNode==Root) break;
	}
	Root->color = 0;
}

void RedBlackDelete(int x)
{
	// Delete in BST
	Node *curr;
	curr = Root;
	Node* delnode;
	while(curr->info!=-1)
	{
		if(curr->info==x) break;
		if(curr->info<x)
		{
			curr = curr->right;
		}
		else curr = curr->left;
	}

	Node* min_node = curr;
	int del_color = min_node->color;
	if(curr->left->info==-1)
	{
		delnode = curr->right;
		transplant(curr,curr->right);
	}
	else if(curr->right->info==-1)
	{
		delnode = curr->left;
		transplant(curr,curr->left);
	}
	else
	{
		min_node = minimum(curr->right);
		del_color = min_node->color;
		delnode = min_node->right;
		if(min_node->parent==curr)
		{
			delnode->parent = min_node;
		}
		else
		{
			transplant(min_node,min_node->right);
			min_node->right = curr->right;
			min_node->right->parent = min_node;
		}
		transplant(curr,min_node);
		min_node->left = curr->left;
		min_node->left->parent = min_node;
		min_node->color = curr->color;
		if(del_color==1) return;

		// Fix the Red Black Tree if Deleted node is Black
		Node* sibling;
		while(delnode!=Root && delnode->color==0)
		{
			if(isLeft(delnode))
			{
				sibling = delnode->parent->right;
				if(sibling->color)
				{
					sibling->color = 0;
					delnode->parent->color = 1;
					leftRotate(delnode->parent);
					sibling = delnode->parent->right;
				}
				if(sibling->left->color==0 && sibling->right->color==0)
				{
					sibling->color = 1;
					delnode = delnode->parent;
				}
				else
				{
					if(sibling->right->color==0)
					{
						sibling->left->color = 0;
						sibling->color = 1;
						rightRotate(sibling);
						sibling = delnode->parent->right;
					}
					sibling->color = delnode->parent->color;
					delnode->parent->color = 0;
					sibling->right->color = 0;
					leftRotate(delnode->parent);
					delnode = Root;
				}
			}
			else
			{
				sibling = delnode->parent->left;
				if(sibling->color)
				{
					sibling->color = 0;
					delnode->parent->color = 1;
					rightRotate(delnode->parent);
					sibling = delnode->parent->left;
				}
				if(sibling->left->color==0 && sibling->right->color==0)
				{
					sibling->color = 1;
					delnode = delnode->parent;
				}
				else
				{
					if(sibling->left->color==0)
					{
						sibling->right->color = 0;
						sibling->color = 1;
						leftRotate(sibling);
						sibling = delnode->parent->left;
					}
					sibling->color = delnode->parent->color;
					delnode->parent->color = 0;
					sibling->left->color = 0;
					rightRotate(delnode->parent);
					delnode = Root;
				}
			}
		}
	}
	delnode->color = 0;
}

int main()
{
	printf("Enter the number of nodes: ");
	int N;
	scanf("%d",&N);
	int Arr[N];
	// Input The Nodes of The RedBlack Tree
	printf("Enter the values of the nodes: \n");
	for(int i=0;i<N;i++)
	{
		scanf("%d",&Arr[i]);
		RedBlackInsert(Arr[i]);
	} 
	printf("Final Tree after insertion : \t");
	levelOrder(Root);
	printf("\n");

	printf("Enter the number of nodes to be deleted: ");
	// Delete Nodes One By One
	int M;
	scanf("%d",&M);
	printf("Insert the nodes to be deleted: \n");
	for(int i=0;i<M;i++)
	{
		int x;
		scanf("%d",&x);
		RedBlackDelete(x);
		printf("Tree after deletion of %d : \t",x);
		levelOrder(Root);
		printf("\n");
	}
}