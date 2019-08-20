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
Graph* reverseGraph(Graph** g);
void doDFS(Graph* graph, int* visited, listNode** stack, int src);
void pushStack(listNode** stack, int src);
void printSCC(Graph* graph);
void doDFS2(Graph* graph, listNode** stack, int* visited);
void doDFSPrint(Graph* graph, int* visited, int src);
listNode* pop(listNode** stack);
int main()
{
	Graph* graph = NULL;
	graph = createGraph(graph,5);
	addEdge(graph,0,4);
	addEdge(graph,1,3);
	addEdge(graph,2,1);
	addEdge(graph,3,2);
	addEdge(graph,3,0);
	//prnGraph(graph);
	printSCC(graph);
}
void printSCC(Graph* graph)
{
	int V = graph->V;
	int* visited = (int*)malloc(V*sizeof(int));
	for(int i=0;i<V;i++)
		visited[i]=0;
	listNode* stack=NULL;
	for (int i = 0; i < V; ++i)
	{
		if(visited[i]==0)
		{
			doDFS(graph,visited,&stack,i);
		}
	}
	listNode* temp = stack;
	for(int i=0;i<V;i++)
		visited[i]=0;
	graph = reverseGraph(&graph);			//reverse the connections in the graph
	doDFS2(graph,&stack,visited);		//each element of stack used will give the connected components 
}
void doDFS2(Graph* graph, listNode** stack, int* visited)
{
	while(*stack)
	{
		listNode* popped = pop(stack);
		if(visited[popped->loc]==0)
		{
			
			doDFSPrint(graph,visited,popped->loc);
			printf("\n");
		}
	}
}
listNode* pop(listNode** stack)
{
	listNode* temp = *stack,*pre;
	if(temp->next == NULL)
	{
		*stack = NULL;
		return temp;
	}
	while(temp->next)
	{
		pre = temp;
		temp = temp->next;
	}
	pre->next = NULL;
	return temp;
}
void doDFSPrint(Graph* graph, int* visited, int src)
{
	visited[src] = 1;
	printf("%d ",src);
	listNode* temp = graph->arr[src].head;
	while(temp)
	{
		if(visited[temp->loc]==0)
			doDFSPrint(graph,visited,temp->loc);
		temp = temp->next;
	} 
}
void doDFS(Graph* graph, int* visited, listNode** stack, int src)
{

	visited[src] = 1;
	listNode* temp = graph->arr[src].head;
	while(temp)
	{
		if(visited[temp->loc]==0)
			doDFS(graph,visited,stack,temp->loc);
		temp = temp->next;
	} 
	//now push the src into the stack after it is finished
	pushStack(stack, src);
}
void pushStack(listNode** stack, int src)
{
	listNode* temp = *stack;
	if(temp==NULL)
	{
		(*stack) = (listNode*)malloc(sizeof(listNode));
		(*stack)->loc = src;
		(*stack)->next = NULL;
		return;
	}
	while(temp->next)
		temp = temp->next;
	listNode* new = (listNode*)malloc(sizeof(listNode));
	new->loc = src;
	new->next = NULL;
	temp->next = new;
}
Graph* reverseGraph(Graph** g)
{
	Graph* graph = *g,*newGraph = NULL;
	int V = graph->V;
	newGraph = createGraph(newGraph,V);
	listNode* temp;
	for(int i=0;i<V;i++)
	{
		temp = graph->arr[i].head;
		while(temp)
		{
			addEdge(newGraph,temp->loc,i);
			temp = temp->next;
		}
	}
	return newGraph;
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