#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define numVertices 3
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
	int V;
	list* arr;
}Graph;
int Find(int p, int parent[]);
Graph* addEdge(Graph* graph, int src, int dest, int parent[], int size[]);
void prnGraph(Graph* graph);
Graph* createGraph(Graph* graph, int vertices);


int main()  
{  
    Graph* graph = NULL;
    graph = createGraph(graph,numVertices);  
  	int parent[numVertices];
  	int size[numVertices];
  	for (int i = 0; i < numVertices; ++i)
  	{
  		parent[i] = i;
  		size[i] = 1;
  	}
    graph = addEdge(graph,0,1,parent,size);//addEdge functions just like Union as well addEdge normal
    graph = addEdge(graph,1,2,parent,size);  
    graph = addEdge(graph,0,2,parent,size);  
  	return 0;
}
int Find(int p, int parent[])
{
	if(parent[p] == p)
		return p;
	else
	{
		parent[p] = parent[parent[p]];
		return Find(parent[p], parent);
	}
}
Graph* addEdge(Graph* graph, int src, int dest, int parent[], int size[])
{
	listNode* temp = graph->arr[src].head;
	if(temp==NULL)
	{
		listNode* newListNode = (listNode*)malloc(sizeof(listNode));
		newListNode->loc = dest;
		newListNode->next = NULL;
		temp = newListNode;
	}
	else
	{
		while(temp->next!= NULL)
			temp = temp->next;
		listNode* newListNode = (listNode*)malloc(sizeof(listNode));
		newListNode->loc = dest;
		newListNode->next = NULL;
		temp->next = newListNode;
	}
	int i = Find(src, parent);
	int j = Find(dest, parent);
	if(size[i] > size[j])
	{
		parent[j] = i;
		size[i] += size[j];
	}
	else
	{
		if(i == j)
			printf("Cycle detected! @ SRC: %d DEST: %d\n", src,dest);
		parent[i] = j;
		size[j] += size[i];
	}

	return graph;
}
void prnGraph(Graph* graph)
{
	int i;
	for (i = 0; i < graph->V; ++i)
	{
		listNode* temp = graph->arr[i].head;
		while(temp!=NULL)
		{
			printf("%d\t",temp->loc);
			temp = temp->next;
		}
		printf("\n");
	}
}
Graph* createGraph(Graph* graph, int vertices)
{
	int i; 	
	graph = (Graph*)malloc(sizeof(Graph));
	graph->V = vertices;
	graph->arr = (list*)malloc((graph->V)*sizeof(list));
	for (i = 0; i < graph->V; ++i)
		graph->arr[i].head = NULL;
	return graph;
}  