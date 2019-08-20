#include <stdio.h>
#include <stdlib.h>
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
void addEdge(Graph* graph, int src, int dest);
void prnGraph(Graph* graph);
void doDFS(Graph* graph, int* visited, listNode** stack, int src);
void topologicalSort(Graph* graph, int src);
int main()
{
	Graph* graph = NULL;
	graph = createGraph(graph,6);
	addEdge(graph,5, 2); 
    addEdge(graph,5, 0); 
    addEdge(graph,4, 0); 
    addEdge(graph,4, 1); 
    addEdge(graph,2, 3); 
    addEdge(graph,3, 1); 
    prnGraph(graph);
    topologicalSort(graph,0);
}
void addEdge(Graph* graph, int src, int dest)
{
	listNode* newListNode = (listNode*)malloc(sizeof(listNode));
	newListNode->loc = dest;
	newListNode->next = graph->arr[src].head;
	graph->arr[src].head = newListNode;
}
void prnGraph(Graph* graph)
{
	int V = graph->V;
	for(int i=0;i<V;i++)
	{
		listNode* temp = graph->arr[i].head;
		printf("+++NODE: %d\nHEAD", i);
		while(temp)
		{
			printf("-->%d",temp->loc);
			temp=temp->next;
		}
		printf("\n");
	}
}
void topologicalSort(Graph* graph, int src)
{
	int V = graph->V;
	listNode* stack = NULL;
	int* visited = (int*)malloc(V*sizeof(int));
	for (int i = 0; i < V; ++i)
		visited[i] = 0;
	for(int i=0;i<V;i++)
	{
		if(visited[i]==0)
		{
			doDFS(graph,visited,&stack,i);
		}
	}
	listNode* T = stack;
	printf("T: %d\n", T);
	while(T)
	{
		printf("%d-->",T->loc);
		T = T->next;		
	}
}
void doDFS(Graph* graph, int* visited, listNode** stack, int src)
{
	visited[src] = 1;
	listNode* temp = graph->arr[src].head;
	while(temp)
	{
		if(visited[temp->loc] == 0)
		{
			doDFS(graph,visited,stack,temp->loc);
		}
		temp=temp->next;
	}
	listNode* T, *new;
	T = *stack;
	if(T==NULL)
	{
		(*stack) = (listNode*)malloc(sizeof(listNode));
		(*stack)->loc = src;
		(*stack)->next = NULL;
	}
	else{
		while(T->next)
			T= T->next;
		new = (listNode*)malloc(sizeof(listNode));
		new->loc = src;
		new->next = NULL;
		T->next = new;
	}
}