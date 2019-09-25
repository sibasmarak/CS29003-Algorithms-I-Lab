#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define numElem 5
void Union(int p, int q, int parent[], int size[]);
int Find(int p, int parent[]);
int main() 
{
	//int numElem;
	//scanf("%d", &numElem); 
    int parent[numElem];	//stores the parent id of i-th element
    int size[numElem];	//stores the size of the rooted tree with i as the root
    int i;
    for(i = 0;i<numElem;i++)
    {
    	parent[i] = i;	//everyone is the parent of itself
    	size[i] = 1;	//initially all rooted trees are of unity size
    }

    Union(0, 2,parent, size); 
   	Union(4, 2,parent, size); 
   	Union(3, 1,parent, size); 
    if (Find(4,parent) == Find(0,parent)) 
         printf("YES\n");
    else
         printf("NO\n");
    if (Find(1,parent) == Find(0,parent)) 
         printf("YES\n");
    else
         printf("NO\n");
    return 0; 
} 
void Union(int p, int q, int parent[], int size[])
{
	int i = Find(p,parent);
	int j = Find(q,parent);
	if(size[i]>size[j])
	{
		parent[j] = i;
		size[i] += size[j];
	}
	else
	{
		parent[i] = j;
		size[j] += size[i];
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