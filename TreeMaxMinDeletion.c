#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
	struct Node* left;
	int data;
	struct Node* right;
	struct Node* parent;
}Node;
Node* insert(Node* root, int data, Node* parent)
{
	if(root == NULL)
	{
		root = (Node*)malloc(sizeof(Node));
		root->data = data;
		root->parent = parent;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	if(data < root->data)
		root->left = insert(root->left, data,root);
	else
		root->right = insert(root->right, data,root);
	return root;
}
void inOrder(Node* root); 	
Node* search(Node* root, int key);
Node* treeMin(Node* root);
Node* inOrderSuccessor(Node* root, int key);
Node* delete(Node* root, int key);
int main()
{
	Node* root = NULL;
	root = insert(root, 11,NULL); 
	root = insert(root, 6,NULL); 
	root = insert(root, 8,NULL); 
	root = insert(root, 19,NULL); 
	root = insert(root, 4,NULL); 
	root = insert(root, 10,NULL); 
	root = insert(root, 5,NULL); 
	root = insert(root, 17,NULL); 
	root = insert(root, 43,NULL); 
	root = insert(root, 49,NULL); 
	root = insert(root, 31,NULL); 
    
    inOrder(root);
    root = delete(root, 11);
    inOrder(root);
}
Node* delete(Node* root, int key)
{
	Node* res = search(root, key),*par;
	par = res->parent;
	if(res->left == NULL && res->right == NULL)	//leaf node
	{
		if(par->right == res)
		{
			par->right = NULL;
			free(res);
		}
		else
		{
			par->left = NULL;
			free(res);
		}
		return root;
	}
	if(res->right == NULL && res->left!=NULL)
	{
		if(par->right == res)
		{
			res->left->parent = par;
			par->right = res->left;
			free(res);
		}
		else
		{
			res->left->parent = par;
			par->left = res->left;
			free(res);
		}
		return root;
	}
	if(res->left == NULL && res->right!=NULL)
	{
		if(par->right == res)
		{
			res->right->parent = par;
			par->right = res->right;
			free(res);
		}
		else
		{
			res->right->parent = par;
			par->left = res->right;
			free(res);
		}
		return root;
	}
	Node* del = treeMin(res->right);//gives the successor
	Node* tempPar = del->parent;	
	res->data = del->data;
	tempPar->left = NULL;
	free(del);
	return root;
}
Node* inOrderSuccessor(Node* root, int key)
{
	Node* res = search(root,key);
	if(res->right!=NULL)
		return treeMin(res->right);
	Node* par = res->parent;
	while(par!=NULL && par->right == res)
	{
		res = par;
		par = res->parent;
	}
	return par;
}
Node* treeMin(Node* root)
{
	if(root->left == NULL)
		return root;
	treeMin(root->left);
}
Node* search(Node* root, int key)
{
	if(root == NULL || root->data == key)
		return root;
	if(key < root->data)
		return search(root->left, key);
	else if(key>=root->data)
		return search(root->right, key);
}
void inOrder(Node* root)
{
	if(root!=NULL)
	{
		inOrder(root->left);
		printf("%d %d\n",root->data,root->parent);
		inOrder(root->right);
	}
}