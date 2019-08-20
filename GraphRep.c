#include <stdio.h>
#include <stdlib.h>

typedef struct AdjListNode
{
	int dest;
	struct AdjListNode* next;
}AdjListNode;
typedef struct AdjList
{
	struct AdjListNode* head;
}AdjList;
typedef struct Graph
{
	int V;
	struct AdjList* array;
}Graph;

Graph* createGraph(Graph* graph, int V);
void addEdge(Graph* graph, int src, int dest);
AdjListNode* newAdjListNode(int dest);
void printGraph(Graph* graph);

int main()
{
	struct Graph* graph = NULL;
	int V = 5;
	graph = createGraph(graph, V);
	addEdge(graph, 0, 1); 
    addEdge(graph, 0, 4); 
    addEdge(graph, 1, 2); 
    addEdge(graph, 1, 3); 
    addEdge(graph, 1, 4); 
    addEdge(graph, 2, 3); 
    addEdge(graph, 3, 4);

    printGraph(graph);
}
void printGraph(Graph* graph)
{
	int v;
	for(v=0; v<graph->V;v++)
	{
			struct AdjListNode* pCrawl = graph->array[v].head;
			printf("Adjacency of vertex %d:\n head", v);
			while(pCrawl)
			{
				printf("-->%d", pCrawl->dest);
				pCrawl = pCrawl->next;
			}
			printf("\n");
	} 
}
AdjListNode* newAdjListNode(int dest)
{
	struct AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
	newNode->dest = dest;
	newNode->next = NULL;
	return newNode;
}
void addEdge(Graph* graph, int src, int dest)
{
	struct AdjListNode* newNode = newAdjListNode(dest);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;

	newNode = newAdjListNode(src);
	newNode->next = graph->array[dest].head;
	graph->array[dest].head = newNode;
}
Graph* createGraph(Graph* graph, int V)
{
	graph = (Graph*)malloc(sizeof(Graph));
	graph->V = V;
	graph->array = (AdjList*)malloc(V*sizeof(AdjList));
	for(int i=0;i<V;i++)
			graph->array[i].head = NULL;
	return graph;
}