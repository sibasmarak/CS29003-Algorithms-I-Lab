#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node
{
	int vertex;	//loc
	struct node* next;
}node;
typedef struct Graph
{
	int numVertices;
	struct node** adjLists;
}Graph;
typedef struct Edge
{
	int from;
	int to;
	int weight;
}Edge;

Graph* createGraph(Graph* graph, int vertices, int edges)
{
	graph = (Graph*)malloc(sizeof(Graph));
	graph->numVertices = vertices;
	graph->adjLists = (node**)malloc(vertices*sizeof(node*));
	for(int i=0;i<vertices;i++)
		graph->adjLists[i]= NULL;
	return graph;
}
void addEdges(Graph* graph, int src, int dest);
void prnGraph(Graph* graph);
void addWeightToEdgeArray(Edge* edge, int* inDegreeArray, int edges);	//to modify the weights of different elements of edge array
void buildEdge(Edge* edge, Graph* graph,int edges, int* inDegreeArray);
void mergeFrom(Edge* edge, int mid, Edge* leftEdge, int right, Edge* rightEdge);
void mergeSortFrom(Edge* edge, int low,int high);


void merge(Edge* edge, int l, int m, int h);


int main()
{
	FILE* p = fopen("input.txt","r");
	if(p==NULL)
	{
		printf("FILE not found\n");
		return 0;
	}
	int vertices,edges,src,dest; 
	fscanf(p,"%d",&vertices);	//5
	fscanf(p,"%d",&edges);	//6
	Graph* graph = NULL;
	graph = createGraph(graph, vertices, edges);
	Edge* edge = (Edge*)malloc(edges*sizeof(Edge));	//Array of Edge structures memory allocated
	int* inDegreeArray = (int*)malloc(vertices*sizeof(int));
	for(int i=0;i<5;i++)
		inDegreeArray[i]=0;
	for(int i=0;i<edges;i++)
	{
		fscanf(p, "%d%d", &src, &dest);
		addEdges(graph, src, dest);
		
	}
	buildEdge(edge,graph,edges,inDegreeArray);	//create the edge array
	mergeSortFrom(edge, 0, edges-1);	//sending the array of edge(of Vivid), low(0) and high(edges-1) to sort w.r.t edge[i].from

	printf("\n");
	for(int i=0;i<edges;i++)	//printing of edge array after sorting according to question
		printf("%d %d %d\n", edge[i].from,edge[i].to,edge[i].weight);
	fclose(p);
	return 0;
}
void addEdges(Graph* graph, int src, int dest)
{
	node* newNode = (node*)malloc(sizeof(node));
	newNode->vertex = dest;
	newNode->next = graph->adjLists[src-1];
	graph->adjLists[src-1] = newNode;
}
void prnGraph(Graph* graph)
{
	node* temp;
	for(int i=0;i< graph->numVertices;i++)
	{
		temp = graph->adjLists[i];
		printf("+++ For node %d\nHead", i+1);
		while(temp)
		{
			printf("->%d", temp->vertex);
			temp = temp->next;
		}
		printf("\n");
	}
}
void addWeightToEdgeArray(Edge* edge, int* inDegreeArray,int edges)
{
	int weight;	//to store the sum of inDegrees of edge[i].from and edge[i].to
	for(int i=0;i<edges;i++)
		edge[i].weight = inDegreeArray[edge[i].from-1]+inDegreeArray[edge[i].to-1];
}
void buildEdge(Edge* edge, Graph* graph,int edges, int* inDegreeArray)
{
	node* temp;
	int j=0;
	for(int i=0;i<graph->numVertices;i++)
	{
		temp = graph->adjLists[i];
		while(temp)
		{
			edge[j].from = i+1;	
			edge[j].to = temp->vertex;
			inDegreeArray[temp->vertex-1]++;
			temp=temp->next;
			j++;
		}
	}
	addWeightToEdgeArray(edge, inDegreeArray,edges);
}
/*void mergeSortFrom(Edge* edge, int low,int high)
{
	if(low<high)
	{
		int m = (low+high)/2;
		mergeSortFrom(edge,low,m);
		mergeSortFrom(edge, m+1,high);
		merge(edge,low,m,high);
	}
}
void merge(Edge* edge, int l, int m, int h)
{
	int n1 = m-l+1,n2 = h-m;
	Edge leftEdge[n1], rightEdge[n2];
	for(int i=0;i<n1;i++)
	{
		leftEdge[i] = edge[i+l];
		printf("LEFT EDGE: %d %d %d\n", leftEdge[i].from, leftEdge[i].weight, leftEdge[i].to);
	}
	printf("\n");

	for(int i=0;i<n2;i++)
	{
		rightEdge[i] = edge[i+m+1];
		printf("\n%d %d %d\n", rightEdge[i].from, rightEdge[i].weight, rightEdge[i].to);
	}
	printf("\n");

	int i=0,j=0,k=l;
	while(i<n1 && j<n2)
	{
		if(leftEdge[i].from < rightEdge[j].from)
		{
			edge[k] = leftEdge[i];
			i++;
			k++;
		}
		else if(leftEdge[i].from > rightEdge[j].from)
		{
			edge[k] = rightEdge[j];
			j++;
			k++;
		}
		else if(leftEdge[i].from == rightEdge[j].from)
		{
			if(leftEdge[i].weight == rightEdge[j].weight)
			{
				if(leftEdge[i].to < rightEdge[j].to)
				{ 
					edge[k++] = leftEdge[i++];
				}
				else
				{
					edge[k++] = rightEdge[j++];
				}
			}
			else if(leftEdge[i].weight < rightEdge[j].weight)
			{
				edge[k++] = leftEdge[i++];
			}
			else if(leftEdge[i].weight > rightEdge[j].weight)
			{
				edge[k++] = rightEdge[j++];
			}
		}
	}
	while(i<n1)
	{
		edge[k++] = leftEdge[i++];
	}
	while(j<n2)
	{
		edge[k++] = rightEdge[j++];
	}
}*/
void mergeSortFrom(Edge* edge, int low, int high)
{
	if(low>=high)
		return;
	int mid = (low+high)/2;
	Edge leftEdge[mid-low+1];
	Edge rightEdge[high-mid];
	for(int i=0;i<mid-low+1;i++)
	{
		leftEdge[i] = edge[i+low];
	}
	for(int i=0;i<high-mid;i++)
	{
		rightEdge[i] = edge[i+mid+1];
	}
	
	
	mergeSortFrom(leftEdge,0,mid-low);
	mergeSortFrom(rightEdge,0,high-mid-1);
	mergeFrom(edge,mid-low+1,leftEdge,high-mid,rightEdge);	//to merge and copy back to edge array

}
void mergeFrom(Edge* edge, int mid, Edge* leftEdge, int right, Edge* rightEdge)
{
	int i=0,j=0,k=0;
	while(i<mid && j<right)
	{
		if(leftEdge[i].from < rightEdge[j].from)
		{
			edge[k] = leftEdge[i];
			i++;
			k++;
		}
		else if(leftEdge[i].from > rightEdge[j].from)
		{
			edge[k] = rightEdge[j];
			j++;
			k++;
		}
		else if(leftEdge[i].from == rightEdge[j].from)
		{
			if(leftEdge[i].weight == rightEdge[j].weight)
			{
				if(leftEdge[i].to < rightEdge[j].to)
				{ 
					edge[k++] = leftEdge[i++];
				}
				else
				{
					edge[k++] = rightEdge[j++];
				}
			}
			else if(leftEdge[i].weight < rightEdge[j].weight)
			{
				edge[k++] = leftEdge[i++];
			}
			else if(leftEdge[i].weight > rightEdge[j].weight)
			{
				edge[k++] = rightEdge[j++];
			}
		}
	}
	while(i<mid)
	{
		edge[k++] = leftEdge[i++];
	}
	while(j<right)
	{
		edge[k++] = rightEdge[j++];
	}
}
