#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
void findMin(int n, int DP[n+1][n+1], int P[n+1][n+1], int d[]);
int main()
{
	int d[] = {5,2,3,4,5,7,8};
	int n = sizeof(d)/sizeof(int) , i,j;
	int DP[n][n];
	int P[n][n];
	for(i=0;i<n;i++)
		DP[i][i] = 0;	//DP holds the minimum number of multiplication required
	findMin(n,DP,P,d);
	printf("MIN REQD: %d\n", DP[0][5]);
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d\t",DP[i][j]);
		}
		printf("\n");
	}
	return 0;
}
void findMin(int n, int DP[n+1][n+1], int P[n+1][n+1], int d[])
{
	int i,j,diagonal,k,new;
	for(diagonal = 0;diagonal<n;diagonal++)
	{
		for(i=1;i<n-diagonal;i++)
		{
			j = i+diagonal;
			int min = INT_MAX;
			for(k=i;k<j;k++)
			{
				new = DP[i-1][k-1] + DP[k][j-1] + d[i-1]*d[k]*d[j];
				if(new < min)
				{
					P[i][j] = k+1;
					min = new;
				} 
			}
			DP[i-1][j] = min;
		}
	}
}