#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 36
typedef struct Node
{
	char *symbol;
	int  frequency;
	struct Node *next;
	struct Node *left;
	struct Node *right;
}Node;
Node* addList(Node* list, char x);
Node* rearrangeList(Node* list);
Node* resolveConflict(Node* list);
int find(char c, Node* list); 
Node* addRedundant(Node* list, char arr[]);
int main()
{
	FILE* in = fopen("log.txt", "r");
	if(in==NULL)
		printf("Not Found\n");
	Node* list = NULL,*new=NULL,*temp=NULL,*pre=NULL;
	char x;
	while((x=fgetc(in))!=EOF)		//sorted list created
	{
		if(x=='\n')
			continue;
		list = addList(list, x);
		list = rearrangeList(list);
	}
	char arr[SIZE];
	int i;
	for(i=0;i<26;i++)
		arr[i] = 97+i;
	for(i=26; i<36;i++)
		arr[i] = '0'+i-26;
	for(i=0;i<SIZE;i++)
	{
		int res = find(arr[i],list);
		if(res==1)	//FOUND
			arr[i] = 'P';
	}
	list = addRedundant(list,arr);
	list = resolveConflict(list);
	temp = list;
	while(temp)
	{
		printf("%c %d\n", *(temp->symbol), temp->frequency);
		temp = temp->next;
	}
	
}
Node* addRedundant(Node* list, char arr[])
{
	int i;
	for (i = 0; i < SIZE; ++i)
	{
		if(arr[i]!='P')
		{
			Node* newNode = (Node*)malloc(sizeof(Node));
			newNode->symbol = (char*)malloc(sizeof(char));
			*(newNode->symbol) = arr[i];
			newNode->frequency = 0;
			newNode->next = list;
			list = newNode;
			newNode->left = NULL;
			newNode->right = NULL;
		}
	}
}
int find(char c, Node* list)
{
	Node* temp = list;
	while(temp!=NULL && *(temp->symbol)!=c)
		temp = temp->next;
	return temp==NULL?0:1;
}
Node* resolveConflict(Node* list)
{
	Node* temp = list, *tempList = list;
	while(*(temp->symbol)>='0' && *(temp->symbol)<='9')
		temp = temp->next;
	list = temp;
	while(temp->next)
		temp = temp->next;
	while(tempList!=list)
	{
		temp->next = tempList;
		temp = tempList;
		tempList = tempList->next;
		temp->next = NULL;
	}
	temp = list, tempList = list;
	while(tempList!=NULL)
	{
		int frequency = tempList->frequency;
		while(temp!=NULL && frequency == temp->frequency)
		{
			if(*(temp->symbol) < *(tempList->symbol))
			{
				char Temp = *(temp->symbol);
				*(temp->symbol) = *(tempList->symbol);
				*(tempList->symbol) = Temp;
			}
			temp = temp->next;
		}
		temp = tempList->next;
		tempList = temp;
	}
	return list;
}
Node* rearrangeList(Node* list)
{
	Node* temp = NULL, *pre = NULL,*Next = NULL;
	if(list->next == NULL)
		return list;
	if(list->frequency > list->next->frequency)
	{
		temp = list;
		Next = temp->next;
		temp->next = Next->next;
		Next->next = temp;
		list = Next;
		Next = temp->next;
		pre = list;
		while(Next!=NULL && Next->frequency  == temp->frequency-1)
		{
			pre->next = Next;
			temp->next = Next->next;
			Next->next = temp;
			pre = Next;
			Next = temp->next;
		}
		return list;
	}
	else
	{
		temp = list;
		while(temp->next)
		{
			pre = temp;
			temp = temp->next;
			Next = temp->next;
			if(Next==NULL)
				break;
			if(pre->frequency < temp->frequency && temp->frequency > Next->frequency)
			{
				while(Next!=NULL && Next->frequency  == temp->frequency-1)
				{
					pre->next = Next;
					temp->next = Next->next;
					Next->next = temp;
					pre = Next;
					Next = temp->next;
				}
			}
		}
		return list;
	}
}
Node* addList(Node* list, char x)
{
	if(list==NULL)
	{
		list = (Node*)malloc(sizeof(Node));
		list->symbol = (char*)malloc(sizeof(char));
		*(list->symbol) = x;
		list->frequency = 1;
		list->next = NULL;
		list->left = NULL;
		list->right = NULL;
		return list;
	}
	Node* temp = list, *new = NULL,*pre =NULL;
	while(temp)
	{
		if(*(temp->symbol) == x)
		{
			temp->frequency += 1;
			return list;
		}
		pre = temp;
		temp = temp->next;
	}
	new = (Node*)malloc(sizeof(Node));
	new->symbol = (char*)malloc(sizeof(char));
	*(new->symbol)=x;
	new->next = list;
	list = new;
	new->frequency = 1;
	new->right = NULL;
	new->left = NULL;
	return list;
}