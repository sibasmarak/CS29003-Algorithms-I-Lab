#include <stdio.h>
int merge(int [], int [], int , int , int []);
int mergeSort(int [], int );

int main() 
{ 
    int arr[] = { 1, 20, 6, 4, 5,23,7 }; 
    printf(" Number of inversions are %d \n", mergeSort(arr, 7)); 
    getchar(); 
    return 0; 
} 
int mergeSort(int arr[], int n)
{
	if(n==1)
		return 0;
	int m = (n)/2;
	int arr1[n];
	int a = mergeSort(arr,m);
	int b = mergeSort(arr+m,n-m);
	int c = merge(arr,arr+m,m,n-m,arr1);
	return (a+b+c);
}
int merge(int A[], int B[], int m, int h, int arr1[])
{
	int C[m+h];
	int i=0,j=0,k=0,count=0;
	while(i<m && j<h)
	{
		if(A[i]<B[j]) 
		{
			C[k] = A[i];
			i++;k++;
		}
		else if(A[i]>B[j])
		{
			while(A[i]>B[j])
			{
				count++;
				C[k] = B[j];
				j++;k++; 
			}
		}
	}
	while(i<m)
	{
		C[k] = A[i];
		i++;k++;
	}
	while(j<h)
	{
		C[k] = B[j];
		j++;k++;
	}
	for (i = 0; i < m+h; ++i)
	{
		arr1[i] = C[i];
	}
	return count;
}