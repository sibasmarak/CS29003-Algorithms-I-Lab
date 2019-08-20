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
	for (int i = 0; i < V; ++i)
		graph->arr[i].head = NULL;
	return graph;
}
void doDFSTraversal(Graph* graph, int*visited, int src);
void prnGraph(Graph* graph);
void addEdge(Graph* graph, int src, int dest);
void identifyCycle(Graph* graph,int* visited);
void doModifiedDFS(Graph* graph, int* visited, int src);
int main()
{
	Graph* graph = NULL;
	graph = createGraph(graph, 4);
    addEdge(graph,0, 1); 
    addEdge(graph,0, 2); 
    addEdge(graph,1, 2); 
    addEdge(graph,2, 0); 
    addEdge(graph,2, 3); 
    addEdge(graph,3, 3); 
    prnGraph(graph);
	int V = graph->V;
	int* visited = (int*)malloc(V*sizeof(int));
	//for(int i=0;i<V;i++)
	//	visited[i] = 0;
    //doDFSTraversal(graph,visited, 2);
    for(int i=0;i<V;i++){
		visited[i] = 0;
    }
    identifyCycle(graph,visited);
    return 0;
}
void identifyCycle(Graph* graph,int* visited)
{
	listNode* stack = NULL;
	int V = graph->V;
	for(int i=0;i<V;i++)
	{
		printf("HELLO\n");
		doModifiedDFS(graph,visited,i);
		for(int i=0;i<V;i++)
			visited[i] = 0;
	}
}
void doModifiedDFS(Graph* graph, int* visited, int src)
{
	printf("SRC: %d\n", src);
	visited[src] = 1;
	listNode* temp = graph->arr[src].head;
	while(temp)
	{
		printf("TEMP LOC: %d\n", temp->loc);
		if(visited[temp->loc]==1){
			printf("CYCLE EXISTS\n");
			return;
		}
		if (visited[temp->loc]==0)
		{
			doModifiedDFS(graph,visited,temp->loc);
		}
		temp = temp->next;
	}
	return;
}
void addEdge(Graph* graph, int src, int dest)
{
	listNode* newListNode = (listNode*)malloc(sizeof(listNode));
	newListNode->loc = dest;
	newListNode->next = graph->arr[src].head;
	graph->arr[src].head = newListNode;
}
void doDFSTraversal(Graph* graph, int*visited, int src)
{
	visited[src] = 1;
	printf("%d ", src);
	listNode* temp = graph->arr[src].head;
	while(temp)
	{
		if(visited[temp->loc]==0)
		{
			doDFSTraversal(graph, visited, temp->loc);
		}
		temp = temp->next;
	}
}
void prnGraph(Graph* graph)
{
	int V = graph->V;
	for(int i=0;i<V;i++)
	{
		listNode* temp = graph->arr[i].head;
		printf("+++Node: %d\nHead", i);
		while(temp)
		{
			printf("-->%d ", temp->loc);
			temp = temp->next;
		}
	}
}