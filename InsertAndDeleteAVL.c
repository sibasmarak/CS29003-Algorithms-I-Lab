#include <stdio.h>
#include <stdlib.h>
struct Node
{
	int data;
	struct Node* left;
	struct Node* right;
	int height;
};
typedef struct Node Node;
void preorder(Node* root);
Node* leaf(Node* root, int key);
int max(int a, int b);
Node* insert(Node* root, int key);
Node* rightRot(Node* T);
Node* leftRot(Node* root);
Node* rebalance_right(Node* root);
Node* rebalance_left(Node* root);
int compare(int a, int b);
int main()
{
	Node* root = NULL;
	root = insert(root, 10);
	preorder(root);
	printf("\n");

	root = insert(root, 20); 
	printf("\n");
	preorder(root);
	printf("\n");

	
	root = insert(root, 30);
	preorder(root);
	printf("\n");


	root = insert(root, 40);
	preorder(root);
	printf("\n");

	root = insert(root, 50);
	preorder(root);

	root = insert(root, 25);
	preorder(root);
	printf("\n");

	return 0;
}
int height(Node* root)
{
	return (root==NULL) ? 0 : root->height;
}
Node* rightRot(Node* T)
{
	Node* root = T->left;
	T->left = root->right;
	root->right = T;
	T->height = max(height(T->left), height(T->right))+1;
	root->height = max(height(root->left), height(root->right))+1;
	return root;
}			
Node* leftRot(Node* T)
{
	Node* root = T->right;
	T->right = root->left;
	root->left = T;
	T->height = max(height(T->left), height(T->right))+1;
	root->height = max(height(root->left), height(root->right))+1;
	return root;
}
Node* rebalance_right(Node* root)
{
	printf("REBALANCE RIGHT %d\n", root);
	Node* l = root->left;
	Node* r = root->right;
	printf("L:%d R: %d\n", l,r);
	int hl = height(l);
	int hr = height(r);
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
Node* rebalance_left(Node* root)
{
	Node* l = root->left;
	Node* r = root->right;
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
Node* insert(Node* root, int key)
{ 				  						
	printf("ROOT IN INSERT: %d\n", root);
	if(root==NULL)
		root =  leaf(root,key);
	else
	{
		int r = compare(root->data, key);
		if(r<0)			//root->data < key, insert in the right
		{
			root->right = insert(root->right, key);
			root->height = max(height(root->left), height(root->right))+1;
			printf("ROOT HEIGHT: %d\n", height(root));
			root = rebalance_right(root);
		}
		else if(r==0)
			root->data = key;
		else if(r>0)
		{
			root->left = insert(root->left, key);
			root->height = max(height(root->left), height(root->right))+1;
			root = rebalance_left(root);
		}
	}
	return root;
}
int compare(int a, int b)
{
	if(a>b)
		return 1;
	else if(a==b)
		return 0;
	else return -1;
}
Node* leaf(Node* root, int key)
{
	root = (Node*)malloc(sizeof(Node));
	root->height = 1;
	root->data = key;
	root->left = NULL;
	root->right = NULL;
	return root;
}
int max(int a, int b)
{
	return a>b?a:b;
}
void preorder(Node* root)
{	
	Node* p = root;
	if(p!=NULL)
	{
		printf("%d %d\n", p->data, p->height);
		preorder(p->left);
		preorder(p->right);
	}
}