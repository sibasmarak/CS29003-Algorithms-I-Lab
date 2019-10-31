#include <stdio.h>
#include <stdlib.h>

typedef struct heap
{
	int* head;
	int presentElem;
	int capacity;
}heap;
void convertMaxHeap(int arr[], int sz);
void heapify(heap** H, int index);
heap* buildMaxHeap(heap* h, int capacity);
int main()
{
	// array representing Min Heap 
    int arr[] = {3, 5, 9, 6, 8, 20, 10, 12, 18, 9}; 
    int n = sizeof(arr)/sizeof(arr[0]); 
  
    convertMaxHeap(arr, n); 
  
    return 0; 
}
void convertMaxHeap(int arr[], int sz)
{
	//allocate memory to the heap
	heap* maxHeap = NULL;
	maxHeap = buildMaxHeap(maxHeap, sz);

	//simply build the maxHeap
	//irrespective of the type of array given

	int i;
	//first add all the elements to the maxHeap->head[] from arr[]
	for(i=0;i < sz; i++)
		maxHeap->head[i] = arr[i];

	//now heapify starting from the mid
	//this would assign and thus create the maxHeap structure

	for(i = sz/2; i >= 0; i--)
	{
		heapify(&maxHeap, i);
		//the above call would assign i-th element its correct position
	}

	//now print the maxHeap->head[]
	for(i = 0; i < sz; i++)
		printf("%d ", maxHeap->head[i]);

	return;

}
void heapify(heap** H, int index)
{
	//heapify function for the creation of maxHeap
	heap* h = *H;
	int n = h->capacity;
	int l = 2*index + 1;
	int r = 2*index + 2;
	int largest = index;
	if(l<n && h->head[l] > h->head[largest])
		largest = l;
	if(r<n && h->head[r] > h->head[largest])
		largest = r;

	if(largest!=index)
	{
		//swap the largest and the index and call recursively
		//the function heapify
		int temp = h->head[largest];
		h->head[largest] = h->head[index];
		h->head[index] = temp;
		heapify(H, largest);
	}
	return;
}

heap* buildMaxHeap(heap* h, int capacity)
{
	//assign memory to the heap 
	//and then assign the capacity

	h = (heap*)malloc(sizeof(heap));
	h->capacity = capacity;
	h->head = (int*)malloc(capacity * sizeof(int));
	h->presentElem = 0;
	//presentElem is 0 since there is no element
	//in the h->head[]
	return h;
}