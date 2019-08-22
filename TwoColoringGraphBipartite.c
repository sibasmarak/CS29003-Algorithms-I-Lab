#include <stdio.h>
#include <stdlib.h>
#define V 4
#define NOCOLOR -1
typedef struct Node
{
	int data;
	struct Node* next;
}Node;
int isBipartite(int G[][V]);
void addQueue(Node** f, Node** r, int src);
int isBipartiteUtil(int G[][V], int colorArr[], int src);
Node* deleteQueue(Node** f);

int main()
{
	int G[][V] = {{0, 1, 0, 1}, 
        {1, 0, 1, 0}, 
        {0, 1, 0, 1}, 
        {1, 0, 1, 0} 
    }; 
    int res = isBipartite(G);
    if(res==1)
    	printf("YES\n");
    else
    	printf("NO\n");
}
int isBipartite(int G[][V])
{
	int colorArr[V];
	for(int i=0;i<V;i++)
		colorArr[i] = NOCOLOR;
	for(int i=0;i<V;i++)
		if(colorArr[i]==NOCOLOR)
			return isBipartiteUtil(G,colorArr,i);
}
int isBipartiteUtil(int G[][V], int colorArr[], int src)
{
	colorArr[src] = 1;	//RED
	Node* f=NULL, *r=NULL;
	addQueue(&f,&r,src);
	while(f!=NULL)
	{
		Node* u = deleteQueue(&f);
		if(G[u->data][u->data])
			return 0;		//to avoid self Loop
		for(int v=0;v<V;v++)
		{
			if(G[u->data][v]==1 && colorArr[v]==NOCOLOR)
			{
				colorArr[v] = 1 - colorArr[u->data];	//conjugate color of the ancestor(This just took away my heart)
				addQueue(&f,&r,v);
			}
			else if(G[u->data][v]==1 && colorArr[u->data] == colorArr[v])
				return 0;
		}
	}
	return 1;
}
Node* deleteQueue(Node** f)
{
	Node* temp = (*f)->next,*pre = *f;
	*f = temp;
	return pre;
}
void addQueue(Node** f, Node** r, int src)
{
	if(*f==NULL)
	{
		*r = (Node*)malloc(sizeof(Node));
		(*r)->data = src;
		(*r)->next = NULL;
		(*f) = (*r);
		(*r) = (*r)->next;
		return;
 	}
 	Node* temp = (*f);
 	while(temp->next)
 		temp = temp->next;
 	*r = (Node*)malloc(sizeof(Node));
	(*r)->data = src;
	(*r)->next = NULL;
	temp ->next = (*r);
	(*r) = (*r)->next;
	return;
}