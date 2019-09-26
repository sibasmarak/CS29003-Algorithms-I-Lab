#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Job
{
		char ch;
		int deadline;
		int profit;
}Job;
void printJobScheduling(Job arr[], int n);
int Find(int p, int parent[]);
void Union(int a, int i, int size[], int parent[]);
int MaxD(Job arr[], int n);

int main() 
{ 
	Job arr[] =  { { 'c', 1, 40 },  
                   { 'd', 1, 30 },  
                   { 'b', 1, 10 },{'a',4,20} };
    /*Job arr[] =  { { 'a', 2, 100 },  
                   { 'c', 2, 27 },  { 'd', 1, 25 }, { 'b', 1, 19 },  
                   { 'e', 3, 15 } };*/ // we have to sort the array first w.r.t the profits, sorted manually here
    int n = sizeof(arr) / sizeof(arr[0]); 
    printJobScheduling(arr, n); 
    return 0; 
    return 0; 
} 
void printJobScheduling(Job arr[], int n)
{
	int maxDeadLine = MaxD(arr,n);
	int parent[n+1];
	for (int i = 0; i < n+1; ++i)
		parent[i] = i;
	int size[n+1];
	char Ans[maxDeadLine+1];
	memset(size,1,sizeof(size));
	memset(Ans,' ',sizeof(Ans));
	for(int i=0;i<n;i++)
	{
		int avalSlot = Find(arr[i].deadline, parent);	//Find the latest slot available, which the root
		if(avalSlot>0)
		{
			Union(avalSlot-1, parent[arr[i].deadline], size, parent);//Do the union of avalSlot-1(as parent) with the existing parent of arr[i].deadline
			Ans[avalSlot-1] = arr[i].ch;
		}
	}
	printf("%s\n", Ans);
}
int MaxD(Job arr[], int n)
{
	int max = -1;
	for (int i = 0; i < n; ++i)
	{
		if(max<arr[i].deadline)
			max = arr[i].deadline;
	}
	return max;
}
int Find(int p, int parent[])
{
	if(p==parent[p])
		return p;
	else
	{
		parent[p] = parent[parent[p]];
		return Find(parent[p] , parent);
	}
}
void Union(int a, int i, int size[], int parent[])
{
	parent[i] = a;
	size[a] += size[i];
}