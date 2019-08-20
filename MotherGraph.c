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

Graph* createGraph(Graph* graph, int V)	//V is number of vertices
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
int findMother(Graph* graph);
void DFS(Graph* graph, int* visited, int i);
int main()
{
	Graph* graph = NULL;
	graph = createGraph(graph,7);
	addEdge(graph, 0, 1); 
    addEdge(graph, 0, 2); 
    addEdge(graph, 1, 3); 
    addEdge(graph, 4, 1); 
    addEdge(graph, 6, 4); 
    addEdge(graph, 5, 6); 
    addEdge(graph, 5, 2);
    addEdge(graph, 6, 0);
    printf("+++Graph Created+++\n");
    prnGraph(graph);

    int mother = findMother(graph);
    printf("+++ The mother of the graph: %d +++\n", mother);
}
void DFS(Graph* graph, int* visited, int i)
{
	visited[i]=1;
	listNode* temp = graph->arr[i].head;
	while(temp)		
	{
		if(visited[temp->loc]==0)
		{
			DFS(graph,visited,temp->loc);
		}
		temp = temp->next;
	}
}
int findMother(Graph* graph)
{
	int mother = 0, vertices = graph->V;
	int* visited = (int*)malloc(vertices*sizeof(int));
	memset(visited,0,sizeof(visited));
	for(int i=0;i<vertices;i++)
	{
		if(visited[i]==0)
		{
			DFS(graph, visited, i);
			mother = i;
		}
	}
	//do DFS and then send mother by checking
	return mother;
}
void prnGraph(Graph* graph)
{
	int vertices = graph->V;
	for(int i=0;i<vertices;i++)
	{
		listNode* temp = graph->arr[i].head;
		printf("+++Node %d\nHead", i);
		while(temp)
		{
			printf("->%d", temp->loc);
			temp = temp->next;
		}
		printf("\n");
	}
	
}
void addEdge(Graph* graph, int src, int dest)
{
	listNode* newListNode = (listNode*)malloc(sizeof(listNode));
	newListNode->loc = dest;
	newListNode->next = graph->arr[src].head;
	graph->arr[src].head = newListNode; 
}