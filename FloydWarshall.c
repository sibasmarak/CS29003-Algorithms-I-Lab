#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 99999	//never initialize with INT_MAX, else adding a number to it would bring it back to -INT_MAX
void floydWarshall(int n, int W[n][n], int P[n][n]);
void printPath(int n, int P[n][n], int i, int j);
int main()
{
	int n = 5;
	int W[5][5] = {
			0,1,INF,1,5,
			9,0,3,2,INF,
			INF,INF,0,4,INF,
			INF,INF,2,0,3,
			3,INF,INF,INF,0
	};
	int P[n][n];			//Path matrix to store the vertex through which we can achieve the minimum path length
	memset(P,-1,sizeof(P));
	floydWarshall(n, W, P);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			printf("%d\t", W[i][j]);
		}
		printf("\n");
	}
	printPath(n,P,1,0);
	return 0;
}
void printPath(int n, int P[n][n], int i, int j)
{
	if(P[i][j]!=-1)
	{
		printPath(n,P,i,P[i][j]);
		printf("V%d ", P[i][j]+1);
		printPath(n,P,P[i][j],j);
	}
}
void floydWarshall(int n, int W[n][n], int P[n][n])
{
	for(int k=0;k<n;k++)
	{
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				if(W[i][k]+W[k][j]<W[i][j])		//either you include the kth verex to make 
												//it smallest or else don't include to make the smallest path
				{
					W[i][j] = W[i][k] + W[k][j];
					P[i][j] = k;
				}
			}
		}
	}
}