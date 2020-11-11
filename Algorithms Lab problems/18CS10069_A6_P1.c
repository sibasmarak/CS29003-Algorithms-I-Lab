#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 100
typedef  struct  _treenode 
{
	char *route;
	struct  _treenode *left;
	struct  _treenode *right;
	int  height;
}AVLtreenode;
typedef  AVLtreenode *AVLtree;		//AVLtree means AVLtreenode*
void filter(char [], int);
AVLtree insert(AVLtree root, char* key);
void inorder(AVLtree root, FILE* out);
int height(AVLtree root);
AVLtree rightRot(AVLtree T);
AVLtree leftRot(AVLtree T);
AVLtree rebalance_right(AVLtree root);
AVLtree rebalance_left(AVLtree root);
AVLtree leaf(AVLtree root, char* key, int length);
int max(int a, int b);

int main()
{
	FILE* in = fopen("Routes.txt", "r");
	int numRoutes,i;
	fscanf(in,"%d",&numRoutes);
	char route[SIZE];
	AVLtree root = NULL;
	for(i=0;i<numRoutes;i++)
	{
		fscanf(in,"%s", &route);
		filter(route, strlen(route));
		root = insert(root,route);
	}
	FILE* out = fopen("18CS10069_A6_output.txt", "w");
	fprintf(out, "%d\n", height(root));	//height also correct!
	inorder(root, out);	//inorder traversal correct!
}
void inorder(AVLtree root, FILE* out)
{
	AVLtree p = root;
	if(p!=NULL)
	{
		inorder(p->left,out);
		fprintf(out, "%s\n", (p->route));
		inorder(p->right,out);
	}
}
int max(int a, int b)
{
	return a>b?a:b;
}
int height(AVLtree root)
{
	return (root==NULL) ? 0 : root->height;
}
AVLtree rightRot(AVLtree T)
{
	AVLtree root = T->left;
	T->left = root->right;
	root->right = T;
	T->height = max(height(T->left), height(T->right))+1;
	root->height = max(height(root->left), height(root->right))+1;
	return root;
}			
AVLtree leftRot(AVLtree T)
{
	AVLtree root = T->right;
	T->right = root->left;
	root->left = T;
	T->height = max(height(T->left), height(T->right))+1;
	root->height = max(height(root->left), height(root->right))+1;
	return root;
}
AVLtree rebalance_right(AVLtree root)
{
	AVLtree l = root->left;
	AVLtree r = root->right;
	int hr = height(r);
	int hl = height(l);
	if(hr>hl+1)
	{
		if(height(r->left) < height(r->right))	//right-right condition
		{
			root = leftRot(root);
		}
		else			//right-left condition
		{
			root->right = rightRot(root->right);	//here if r is passed then r is changing but not the root!! pass root->right
			root = leftRot(root);
		}
	}
	return root;
}
AVLtree rebalance_left(AVLtree root)
{
	AVLtree l = root->left;
	AVLtree r = root->right;
	int hl = height(l);
	int hr = height(r);
	if(hl>hr+1)
	{
		if(height(l->left) > height(l->right))	//left-left condition
		{
			root = rightRot(root);
		}
		else					//left-right condition
		{
			root->left = leftRot(root->left);
			root = rightRot(root);
		}
	}
	return root;
}
AVLtree insert(AVLtree root, char* key)
{ 				  						
	if(root==NULL)
		root =  leaf(root,key, strlen(key));
	else
	{
		int r = strcmp(root->route, key);
		if(r<0)			//root->data < key, insert in the right
		{
			root->right = insert(root->right, key);
			root->height = max(height(root->left), height(root->right))+1;
			root = rebalance_right(root);
		}
		else if(r==0)
			*(root->route) = *key;
		else if(r>0)
		{
			root->left = insert(root->left, key);
			root->height = max(height(root->left), height(root->right))+1;
			root = rebalance_left(root);
		}
	}
	return root;
}
AVLtree leaf(AVLtree root, char* key, int length)
{
	int i;
	root = (AVLtree)malloc(sizeof(AVLtreenode));
	(root->route) = (char*)malloc((length+1)*sizeof(char));
	root->height = 1;
	//root->route = key;
	for(i=0;i<length+1;i++)
		root->route[i] = key[i];
	root->left = NULL;
	root->right = NULL;
	return root;
}
void filter(char route[], int length)
{
	char newRoute[length+1];
	memset(newRoute, '\0', sizeof(newRoute));
	int i=0,j=0;
	while(i<length)
	{
		newRoute[j] = route[i];
		if(newRoute[j] == route[i+1])
			i = i+2;
		else
			i++;
		j++;
	}
	memset(route, '\0', sizeof(newRoute));
	for(i=0;i<strlen(newRoute);i++)
		route[i] = newRoute[i];
	return;
}