#include <stdio.h>
void quickSort(int arr[], int l, int h);
int findPivotIndex(int arr[], int l, int h);
int main()
{
	int arr[] = {10, 7, 8, 9, 1, 5};
	int size = sizeof(arr)/sizeof(arr[0]);
	quickSort(arr,0,size-1);
	for (int i = 0; i < size; ++i)
	{
		printf("%d ", arr[i]);
	}
}
void quickSort(int arr[], int l, int h)
{
	if(l<h)
	{
		int p = findPivotIndex(arr,l,h);	//pivot position
		quickSort(arr,l,p-1);
		quickSort(arr,p+1,h);
	}
}
int findPivotIndex(int arr[], int l, int h)
{
	int pivotPos = l, pivotValue=arr[l],temp;
	int j=pivotPos;
	for(int i=j+1;i<=h;i++)
	{
		if(arr[i]<pivotValue)
		{
			j++;
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;

		}
	}
		pivotPos = j;
	temp = arr[l];
	arr[l] = arr[pivotPos];
	arr[pivotPos] = temp;
	return pivotPos;
}