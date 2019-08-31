#include <stdio.h>
#include <stdlib.h>
#define SIZE 150
int ugly(int n);
int min(int a, int b)
{
	if(a<b)
		return a;
	else 
		return b;
}
int main()
{
	int N;
	scanf("%d", &N);
	int uglyN = ugly(N);
	printf("%d\n", uglyN);
	return 0;
}
int ugly(int n)
{
	int* uglyArr = (int*)malloc(SIZE*sizeof(int));
	uglyArr[0] = 1;
	int index2, index3, index5,i,mult2,mult5,mult3,j;
	index2=  index3 = index5 = 0;
	mult2 = 2;
	mult3 = 3;
	mult5 = 5;
	for(i=1;i<n;i++)
	{
		int nextUglyArr = min(mult5,min(mult3,mult2));
		uglyArr[i] = nextUglyArr; 
		if(nextUglyArr == mult2){
			index2 = index2+1;
			mult2 = 2*uglyArr[index2];
		}
		if(nextUglyArr == mult3){
			index3 = index3+1;
			mult3 = 3*uglyArr[index3];
		}
		if(nextUglyArr == mult5){
			index5  = index5+1;
			mult5 = 5*uglyArr[index5];
		}
	}
	return uglyArr[n-1];
}