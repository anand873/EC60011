/////////////////Helper Tree Functions//////////////////
#define TYPE Node*
#include "queue.h"

Node* Root = NULL;

Node* nullNode(Node* father)
{
	Node* node;
	node = (Node*)malloc(sizeof(Node));
	node->info = -1;
	node->color = 0;
	node->left = node->right = NULL;
	node->parent = father;
	return node;
}

Node* makeNode(int x)
{
	Node* thisNode;
	thisNode = (Node*)malloc(sizeof(Node));
	thisNode->info = x;
	thisNode->color = 1;
	thisNode->left = nullNode(thisNode);
	thisNode->right = nullNode(thisNode);
	return thisNode;
}

bool isLeft(Node* p)
{
	return p == (p->parent)->left;
}

bool isRight(Node* p)
{
	return p == (p->parent)->right;
}

Node* minimum(Node* node)
{
	while(node->left->info!=-1)
	{
		node=node->left;
	}
	return node;
}

void transplant(Node* u, Node* v)
{
	if(u->parent==NULL)
	{
		Root = v;
		return;
	}
	else if(isLeft(u))
	{
		u->parent->left = v;
	}
	else u->parent->right = v;
	v->parent = u->parent;
}

void levelOrder(Node* node)
{
	queue Q;
	Q.push(node);
	while(!Q.empty())
	{
		Node* curr = Q.front();
		Q.pop();
		printf("%d %d ", curr->info,curr->color);
		if(curr->left->info!=-1) Q.push(curr->left);
		if(curr->right->info!=-1) Q.push(curr->right);
	}
}

void leftRotate(Node* x)
{
	Node* y = x->right;
	x->right = y->left;
	if(y->left->info!=-1)
	{
		y->left->parent = x;
	}
	y->parent = x->parent;
	if(x->parent == NULL)
	{
		Root = y;
	}
	else if(isLeft(x))
	{
		x->parent->left = y;
	}
	else
	{
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

void rightRotate(Node* x)
{
	Node* y = x->left;
	x->left = y->right;
	if(y->right->info!=-1)
	{
		y->right->parent = x;
	}
	y->parent = x->parent;
	if(x->parent == NULL)
	{
		Root = y;
	}
	else if(isRight(x))
	{
		x->parent->right = y;
	}
	else
	{
		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;
}
/////////////Helper Tree Functions////////////////////