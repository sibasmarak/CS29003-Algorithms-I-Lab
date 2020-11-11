#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
	int data;
	struct Node* left;
	struct Node* right;
	struct Node* parent;
}Node;

void preorder(Node* p);
void inorder(Node* p);
Node* Insert_BST(Node* root, int data, Node* parent);
void findnbr(Node* p, int* maxGap, int* prevVal, int* maxPrevVal);
int abs(int a);
Node* lrotate(Node* root);
Node* rrotate(Node* root);
Node* search(Node* root, int key);
int makechild(Node* root, Node* x, Node* y);

int main()
{
	int n, i, toInsert;
	printf("n = ");
	scanf("%d", &n);
	printf("Keys to insert: ");
	Node* root = NULL;
	for(i = 0; i<n;i++)
	{
		scanf("%d", &toInsert);
		root = Insert_BST(root, toInsert, root);
	}
	printf("\n+++Preorder Traversal:\n");
	preorder(root);

	printf("\n+++Inorder Traversal:\n");
	inorder(root);

	int x = 0, y=159, z= 159;
	int* maxGap = &x;
	int* prevVal = &y;
	int* maxPrevVal = &z;
	findnbr(root, maxGap, prevVal, maxPrevVal);
	printf("\n+++ Finding farthest neighbor\n");
	printf("x = %d, y = %d, gap = %d",(*maxPrevVal)-(*maxGap),(*maxPrevVal),(*maxGap));
	Node* x_ = search(root,(*maxPrevVal)-(*maxGap));
	Node* y_ = search(root,(*maxPrevVal));
	int rotReq = makechild(root, x_,y_);
	printf("\n+++ Bringing neighboring key to child position\n");
	printf("Number of rotations: %d\n", rotReq);

	if(x_->left == NULL)
		printf("x = %d, x->L = NULL , x->R = %d\n", x_->data, x_->right->data);
	else
		printf("x = %d, x->L = %d , x->R = %d\n", x_->data, x_->left->data, x_->right->data);

	printf("\n+++Preorder Traversal of the final tree\n");
	preorder(x_);

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
int makechild(Node* root, Node* x, Node* y)
{
	int rotations=0;
	if(x->data > root->data || y->data < root->data)
	{
		while(x->right!=NULL)
		{
			if(x->right == y)
				return rotations;
			else if(x->right->data > y->data)
			{
				x->right = rrotate(x->right);
				rotations++;
			}
			else if(x->right->data < y->data)
			{
				x->right = lrotate(x->right);
				rotations++;
			}

		}
	}

	else if(x->data < root->data)
	{
		while(root->left!=NULL)
		{
			if(root->left == x)
				break;
			else if(root->left->data > x->data)
			{
				root->left = rrotate(root->left);
				rotations++;
			}
			else if(root->left->data < x->data)
			{
				root->left = lrotate(root->left);
				rotations++;
			}
		}
		//root = rrotate(root); create error as the parent of root is NULL, cause I am trying to access the newParentY->left !
		//rotations++;

		Node* temp = root->left;
		root->left = NULL;
		temp->right = root;
		root->parent = temp;
		temp->parent = NULL;
		rotations++;
		x=temp;

		while(x->right!=NULL)
		{
			if(x->right == y)
				return rotations;
			else if(x->right->data > y->data)
			{
				x->right = rrotate(x->right);
				rotations++;
			}
			else if(x->right->data < y->data)
			{
				x->right = lrotate(x->right);
				rotations++;
			}

		}
	}
}
Node* lrotate(Node* root)
{
	int val;
	Node* y = root->right;
	Node* newParentY = root->parent; 

	if(newParentY-> right == root)
		val = 1;	//right
	else
		val = 0;	//left

	root->right = NULL;
	y->left = root;
	y->parent = newParentY;
	root->parent = y;

	if(val == 1)
		newParentY->right = y;
	else
		newParentY->left  = y;

	return y;
}

Node* rrotate(Node* root)
{
	int val;
	Node* y = root->left;
	Node* newParentY = root->parent; 

	if(newParentY-> right == root)
		val = 1;	//right
	else
		val = 0;	//left

	root->left = NULL;
	y->right = root;
	y->parent = newParentY;
	root->parent = y;
	
	if(val == 1)
		newParentY->right = y;
	else
		newParentY->left  = y;

	return y;
}


Node* Insert_BST(Node* root, int data, Node* parent)
{
	if(root == NULL)
	{
		root = (Node*)malloc(sizeof(Node));
		root->data = data;
		root->left = NULL;
		root->right = NULL;
		root->parent = parent;
		return root;
	}

	if(data < root->data)
		root->left = Insert_BST(root->left, data, root);

	else if(data > root->data)
		root->right = Insert_BST(root->right, data, root);
	return root;
}
void preorder(Node* p)
{
	if(p!=NULL)
	{
		printf("%d ",p->data);
		preorder(p->left);
		preorder(p->right);
	}
}
void inorder(Node* p)
{
	if(p!=NULL)
	{
		inorder(p->left);
		printf("%d ",p->data);
		inorder(p->right);
	}
}


void findnbr(Node* p, int* maxGap, int* prevVal, int* maxPrevVal)
{
	if(p!=NULL)
	{
		findnbr(p->left, maxGap, prevVal, maxPrevVal);
		int temp = abs(p->data - (*prevVal));
		(*prevVal) = p->data;
		if (temp > (*maxGap))
		{
			(*maxGap) = temp;
			(*maxPrevVal) = (*prevVal);
		}
		findnbr(p->right, maxGap,prevVal,maxPrevVal);
	}
}
int abs(int a)
{
	return (a>0)?a:(a*(-1));
}