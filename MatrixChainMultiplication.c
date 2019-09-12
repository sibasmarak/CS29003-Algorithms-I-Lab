#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
void findMin(int n, int DP[n+1][n+1], int P[n+1][n+1], int d[]);
void printOrder(int n, int P[n][n], int i, int j);
int main()
{
	int d[] = {5,2,3,4,5,7,8};	//contains the row and column of subsequent matrices i.e. here three matrices, say A0, A1, A2
	int n = sizeof(d)/sizeof(int)-1 , i,j;
	int DP[n][n];
	int P[n][n];
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			DP[i][j] = 0;
			P[i][j] = 0;
		}
	}
	findMin(n,DP,P,d);
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d ",  P[i][j]);
		}
		printf("\n");
	}
	printf("MIN REQD: %d\n", DP[0][5]);
	printOrder(n,P,0,5);
	return 0;
}
void printOrder(int n, int P[n][n], int i, int j)
{
	if(i==j)
	{
		printf("A%d", j+1);
		return;
	}
	printf("(");
	int k = P[i][j];
	printOrder(n,P,i,k);
	printOrder(n,P,k+1,j);
	printf(")");
}
void findMin(int n, int DP[n][n], int P[n][n], int d[])
{
	int i,j,diagonal,k,new;
	for(diagonal = 1;diagonal<n;diagonal++)
	{
		for(i=0;i<n-diagonal;i++)
		{
			j = i+diagonal;
			int min = INT_MAX;
			for(k=i;k<j;k++)
			{
				new = DP[i][k] + DP[k+1][j] + d[i]*d[k+1]*d[j+1];
				if(new < min)
				{
					P[i][j] = k;
					min = new;
				} 
			}
			DP[i][j] = min;
		}
	}
}