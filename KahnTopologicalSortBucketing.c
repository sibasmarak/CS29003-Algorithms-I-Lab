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
void addEdge(Graph* graph, int src, int dest);
void prnGraph(Graph* graph);
void createInDegreeArray(Graph* graph, int* inDegreeArray);
void topologicalSort(Graph* graph, int* inDegreeArray, listNode** f, listNode** r, int* numVisited);
void addQueue(listNode** f, listNode** r, int i);
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
    //prnGraph(graph);
    int* inDegreeArray = (int*)malloc(6*sizeof(int));
    for (int i = 0; i < 6; ++i)
    	inDegreeArray[i] = 0;
    createInDegreeArray(graph, inDegreeArray);
    listNode* f = NULL, *r = NULL;
    int numVisited = 0;
    topologicalSort(graph,inDegreeArray,&f,&r,&numVisited);
    listNode* temp = f;
    while(temp)
    {
    	printf("%d ",temp->loc);
    	temp = temp->next;
    }
}
void topologicalSort(Graph* graph, int* inDegreeArray, listNode** f, listNode** r, int* numVisited)
{
	printf("numVisited: %d ",*numVisited);
	int V = graph->V;
	int visitArr[V];
	for(int i=0;i<V;i++)
		visitArr[i]=-1;
	if((*numVisited)==V)
		return;
	listNode* temp;
	for (int i = 0; i < V; ++i)
	{
		if(inDegreeArray[i]==0)
		{
			addQueue(f,r,i);
			(*numVisited)++;
			visitArr[i] = 0;
		}
	}
	for(int i=0;i<V;i++)
	{
		if(visitArr[i]==0)
		{
			temp = graph->arr[i].head;
			while(temp)
			{
				inDegreeArray[temp->loc]--;
				temp = temp->next;
			}
			visitArr[i] = -1;
			inDegreeArray[i]=99;
		}
	}
	printf("inDegreeArray: ");
	for(int i=0;i<V;i++)
		printf("%d  ",inDegreeArray[i]);
    topologicalSort(graph,inDegreeArray,f,r, numVisited);
}
void addQueue(listNode** f, listNode** r, int i)
{
	if(*f==NULL)
	{
		*r = (listNode*)malloc(sizeof(listNode));
		(*r)->loc = i;
		(*r)->next = NULL;
		(*f) = *r;
		(*r) = (*r)->next;
		return;
	}
	listNode* temp = *f;
	while(temp->next)
		temp = temp->next;
	*r = (listNode*)malloc(sizeof(listNode));
	(*r)->loc = i;
	(*r)->next = NULL;
	temp->next = *r;
	(*r) = (*r)->next;

}
void createInDegreeArray(Graph* graph, int* inDegreeArray)
{
	int V = graph->V;
	for(int i=0;i<V;i++)
	{
		listNode* temp = graph->arr[i].head;
		while(temp)
		{
			inDegreeArray[temp->loc]++;
			temp=temp->next;
		}
	}
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
		printf("+++NODE: %d\nHead", i);
		while(temp)
		{
			printf("-->%d", temp->loc);
			temp = temp->next;
		}
		printf("\n");
	}
}