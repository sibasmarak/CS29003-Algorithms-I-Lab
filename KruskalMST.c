#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Size 5	
#define V 4
typedef struct edge
{
	int src;
	int dest;
	int weight;
	struct edge* next;
}Edge;
Edge* addEdge(Edge* arr, int src, int dest, int weight);
void Union(int p, int q, int parent[], int size[]);
int Find(int p, int parent[]);
void KruskalMST(Edge*);

int main()
{
	Edge* arr = NULL;
	arr = addEdge(arr,0,1,10);
	arr = addEdge(arr,0,2,6);
	arr = addEdge(arr,0,3,5);
	arr = addEdge(arr,1,3,15);
	arr = addEdge(arr,2,3,4);
	
 	KruskalMST(arr);
}
void Union(int p, int q, int parent[], int size[])
{
	if(size[p] > size[q])
	{
		parent[q] = p;
		size[p] += size[q];
	}
	else
	{
		parent[p] = q;
		size[q] += size[p];
	}
	return;
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
void KruskalMST(Edge* arr)
{
	Edge* temp = arr, *pre;
	int parent[V];
	int size[V];
	Edge* MST = NULL;
	for (int i = 0; i < V; ++i)
	{
		parent[i] = i;
		size[i] = 1;
	}
	while(temp)
	{
		int p = Find(temp->src, parent);
		int q = Find(temp->dest, parent);
		if(p!=q)	//belong to disjoint Sets, perform Union
		{
			MST = addEdge(MST, temp->src, temp->dest, temp->weight);
			Union(p,q,parent, size);
		}
		temp = temp->next;
	}

	temp = MST;
	while(temp)
	{
		printf("%d %d %d\n", temp->src, temp->dest, temp->weight);
		temp = temp->next;
	}
}
Edge* addEdge(Edge* arr, int src, int dest, int weight)
{
	Edge* temp = arr;
	if(arr==NULL)
	{
		arr = (Edge*)malloc(sizeof(Edge));
		arr->src = src;
		arr->dest = dest;
		arr->weight = weight;
		arr->next = NULL;
		return arr;
	}
	Edge* pre;
	if(weight<temp->weight)
	{
		arr = (Edge*)malloc(sizeof(Edge));
		arr->src = src;
		arr->dest = dest;
		arr->weight = weight;
		arr->next = temp;
		return arr;
	}
	while(temp && weight>temp->weight)
	{
		pre = temp;
		temp = temp->next;
	}
	Edge* newEdge = (Edge*)malloc(sizeof(Edge));
	pre->next = newEdge;
	newEdge->src = src;
	newEdge->dest = dest;
	newEdge->weight = weight;
	newEdge->next = temp;
	return arr;
}