#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
	struct Node* left;
	int data;
	struct Node* right;
}Node;
Node* insert(Node* root, int data)
{
	if(root == NULL)
	{
		root = (Node*)malloc(sizeof(Node));
		root->data = data;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	if(data < root->data)
		root->left = insert(root->left, data);
	else
		root->right = insert(root->right, data);
	return root;
}
void inOrder(Node* root); 	
Node* search(Node* root, int key);
int main()
{
	Node* root = NULL;
	root = insert(root, 50); 
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40); 
    root = insert(root, 70); 
    root = insert(root, 60); 
    root = insert(root, 80); 
    inOrder(root);
    Node* res = search(root, 50);
    Node* res2 = search(root, 25);
    (res==NULL)?printf("NOT FOUND "):printf("FOUND ");
    (res2==NULL)?printf("NOT FOUND"):printf("FOUND");
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
		printf("%d ",root->data);
		inOrder(root->right);
	}
}