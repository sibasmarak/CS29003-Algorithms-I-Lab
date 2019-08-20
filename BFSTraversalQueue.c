#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct listNode
{
	int loc;
	struct listNode* next;
}listNode;
typedef struct list
{
	listNode* head;
}list;
typedef struct Graph
{
	list* arr;
	int V;
}Graph;

Graph* createGraph(Graph* graph, int V)
{
	graph = (Graph*)malloc(sizeof(Graph));
	graph->V = V;
	graph->arr = (list*)malloc(V*sizeof(list));
	for(int i=0;i<V;i++)
		graph->arr[i].head = NULL;
	return graph;
}
void prnGraph(Graph* graph);
void addEdge(Graph* graph,int src, int dest);
void enque(listNode** f, listNode** r, int src);
void deque(listNode** f);
void doBFSTraversal(Graph* graph, int src);

int main()
{
	Graph* graph = NULL;
	graph = createGraph(graph, 4);
    addEdge(graph,0, 2); 
    addEdge(graph,0, 1); 
    addEdge(graph,1, 2); 
    addEdge(graph,2, 0); 
    addEdge(graph,2, 3); 
    addEdge(graph,3, 3);
    prnGraph(graph); 
    doBFSTraversal(graph,2);
	return 0;
}
void addEdge(Graph* graph,int src, int dest)
{
	printf("\n");
	listNode* newListNode = (listNode*)malloc(sizeof(listNode));
	newListNode->loc = dest;
	newListNode->next = graph->arr[src].head;
	graph->arr[src].head = newListNode;
}
void prnGraph(Graph* graph)
{
	int vertices = graph->V;
	for(int i=0;i<vertices;i++)
	{
		listNode* temp = graph->arr[i].head;
		printf("+++Node %d\nHead",i);
		while(temp)
		{
			printf("->%d", temp->loc);
			temp=temp->next;
		}
		printf("\n");
	}
}
void doBFSTraversal(Graph* graph, int src)
{
	int V = graph->V;
	int *visited=(int*)malloc(V*sizeof(int));
	for(int i=0;i<V;i++)
		visited[i] = 0;
	visited[src] = 1;
	listNode* f = NULL, *r = NULL,*temp,*temp1;
	enque(&f,&r,src);
	while(f!=r)
	{
		src = f->loc;
		deque(&f);
		temp = graph->arr[src].head;
		while(temp)
		{
			if(visited[temp->loc]==0)
			{
				visited[temp->loc]=1;
				enque(&f,&r,temp->loc);
			}
			temp = temp->next;
		}
	}
}
void prnQueue(listNode* f,listNode* r)
{
	if(f==NULL)
		return;
	listNode* temp = f;
	while(temp)
	{
		printf("%d ", temp->loc);
		temp=temp->next;
	}
}
void deque(listNode** f)
{
	listNode* temp = (*f)->next;
	printf("%d ", (*f)->loc);
	free(*f);
	*f = temp;
	return;	
}
void enque(listNode** f, listNode** r, int src)
{
	if(*f==NULL && *r==NULL)
	{
		*r = (listNode*)malloc(sizeof(listNode));
		(*r)->loc = src;
		(*r)->next = NULL;
		*f = *r;
		*r = (*r)->next;
		return;
	}
	listNode* temp = *f;
	while(temp->next)
		temp = temp->next;
	*r = (listNode*)malloc(sizeof(listNode));
	(*r)->loc = src;
	(*r)->next = NULL; 
	temp->next = *r;
	(*r) = (*r)->next;
	return;
}
