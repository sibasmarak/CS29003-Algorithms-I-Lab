#include <stdio.h>
#include <stdlib.h>

typedef struct heap{
	int* head;//stores the pointer to the head of the int arr
	int capacity;//stores the maximum number of elements that can be stored
	int presentElem;//gives the value of the number of elements present in the array
}heap;

heap* BuildHeap(heap* h, int capacity);
int deleteMin(heap** H);
void heapify(heap** H,int index);
void printArray(int arr[], int n);
void sortK(int arr[], int n, int k);
int parent(int i);
heap* insertKey(heap* heap, int data);

int main() 
{ 
    int k = 3; 
    int arr[] = { 2, 6, 3, 12, 56, 8 }; 
    int n = sizeof(arr) / sizeof(arr[0]); 
    sortK(arr, n, k);
    n = sizeof(arr) / sizeof(arr[0]); 
	printArray(arr, n);
    return 0; 
} 
void printArray(int arr[], int n)
{
	int idx;
	for (idx = 0; idx < n; idx++)
		printf("%d ", arr[idx]);
	return;
}

void sortK(int arr[], int n, int k)
{
	//add first k+1 valules into h->head[], then heapify them
	heap* h = NULL;
	h = BuildHeap(h,k+1);
	int i;


	for(i = 0; i<k+1;i++)
		h->head[i] = arr[i];
	h->presentElem = k+1;
	int tempK = k;
	for(int z=tempK/2;tempK>=0;tempK--)
		heapify(&h, z); 

	int tempArr[n], idx = 0, id;

	for(id=1;id<n;id++)
	{
		if(i>=n)
			break;

		int min = deleteMin(&h);
		arr[idx++] = min;
		h = insertKey(h,arr[i]);
		i = i+1;
	}
	for(id = 0; id <= k+1; id++)
	{
		int min = deleteMin(&h);
		arr[idx++] = min;
	}
	return;
}

int parent(int i)
{
	//return the parent of the elem index
	//0 is the parent of itself
	//else (i-1)/2 is the parent of i
	return (i<=0) ? 0 : (i-1)/2;
}
heap* insertKey(heap* heap, int data)
{
	int presentElem = heap->presentElem;
	int capacity = heap->capacity;
	if(presentElem == capacity)
	{
		printf("No more data could be stored\n");
		return heap;
	}
	heap->head[presentElem] = data;
	heap->presentElem++;
	while(parent(presentElem) > 0)
	{
		int par = parent(presentElem);
		if(heap->head[par] > heap->head[presentElem])
		{
			//then the min_heap property has been
			//violated, and we have to sift up the inserted element
			//until the heap property is no more violated
			int temp = heap->head[par];
			heap->head[par] = heap->head[presentElem];
			heap->head[presentElem] = temp;
		}
		presentElem = par;
	}
	int par = parent(presentElem);
	if(heap->head[par] > heap->head[presentElem])
	{
		int temp = heap->head[par];
		heap->head[par] = heap->head[presentElem];
		heap->head[presentElem] = temp;	
	}
	return heap;
}


int deleteMin(heap** H)
{

	heap* h = *H;
	int siftToFirst = h->head[h->capacity - 1];
	int toBeReturned  = h->head[0];
	h->head[0] = siftToFirst; 
	heapify(H, 0);
	h->presentElem--;
	return toBeReturned;
}
void heapify(heap** H,int index)
{
	heap* h = *H;
	int l = 2*index + 1;
	int r = 2*index + 2;
	int n = h->capacity;
	int smallest = index;

	if(l<n && h->head[l] < h->head[smallest])
		smallest = l;
	if(r<n && h->head[r] < h->head[smallest])
		smallest = r;
	if(smallest!=index)
	{
		//swap the index
		//with the present smallest
		int temp = h->head[smallest];
		h->head[smallest] = h->head[index];
		h->head[index] = temp;
		heapify(H, smallest);
	}
}
heap* BuildHeap(heap* h, int capacity)
{
	h = (heap*)malloc(sizeof(heap));
	h->capacity = capacity;
	h->head = (int*)malloc(capacity*sizeof(int));
	h->presentElem = 0;
	return h;
}
