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
	struct listNode* head; 
}list;
typedef struct Graph
{
	int V;
	list* arr;
}Graph;
Graph* createGraph(Graph* graph, int V)
{
	graph = (Graph*)malloc(sizeof(Graph));
	graph->V=V;
	graph->arr = (list*)malloc(V*sizeof(list));
	for(int i=0;i<V;i++)
		graph->arr[i].head = NULL;
	return graph;
}
void addEdge(Graph* graph, int src, int dest);
void prnGraph(Graph* graph);
void createTC(Graph* graph);
void DFS(Graph* graph, int* visited, int i,int j,  int vertices,int tc[][vertices]);
int main()
{
	int V=4;
	Graph* graph = NULL;
	graph = createGraph(graph, V);
	addEdge(graph, 0, 1); 
    addEdge(graph,0, 2); 
    addEdge(graph,1, 2); 
    addEdge(graph,2, 0); 
    addEdge(graph,2, 3); 
    addEdge(graph,3, 3);
    //prnGraph(graph);
    createTC(graph);
	return 0;
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
void createTC(Graph* graph)
{
	int vertices = graph->V;
	int* visited = (int*)malloc(vertices*sizeof(int));
	//int tc[4][4];
	int** tc = (int**)malloc(vertices*sizeof(int*));
	for(int i=0;i<vertices;i++)
	{
		tc[i] = (int*)malloc(vertices*sizeof(int));
	}
	memset(tc,0,sizeof(tc));
	for(int i=0;i<vertices;i++)
	{
		for(int i=0;i<vertices;i++)
		visited[i] = 0;
		printf("%d\n",i);
		if(visited[i]==0)
		{
			DFS(graph,visited,i,i,vertices, tc);
		}
	}
	for(int i=0; i<4;i++)
    {
    	for(int j=0;j<4;j++)
    	{
    		printf("%d ", tc[i][j]);
    	}
    	printf("\n");
    }
    for(int i=0;i<vertices;i++)
	{
		free(tc[i]);
	}
    free(tc);
}
void DFS(Graph* graph, int* visited, int i,int j,  int vertices,int tc[][vertices])
{
	printf("%d %d\n", i, j);
	tc[j][i] = 1;
	visited[i] = 1;
	listNode* temp = graph->arr[i].head;
	while(temp)
	{
		if(visited[temp->loc]==0)
		{	
		
			DFS(graph, visited, temp->loc,j,vertices, tc);
		}
		temp = temp->next;
	}
}