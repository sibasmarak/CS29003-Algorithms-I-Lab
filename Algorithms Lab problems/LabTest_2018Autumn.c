#include <stdio.h>
#include <stdlib.h>

int main()
{
	int N, P;
	printf("Enter N: ");
	scanf("%d", &N);
	printf("Enter P: ");
	scanf("%d", &P);
	float arr[N][P];
	int people[N][P];
	float DP[N][P];
	printf("Enter probabilities: \n");
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < P; ++j)
		{
			scanf("%f", &arr[i][j]);
		}
	}
	
	int i,j,k, maxOccured;
	float max, temp;
	// copy the first row of arr to DP
	for(i = 0; i< P;i++)
		DP[0][i] = arr[0][i];
	for(i=1;i<N;i++)
	{
		for(j=i;j<P;j++)
		{
			max = 0.0;
			if(j==i)
			{
				DP[i][j] = DP[i-1][j-1] * arr[i][0];
				people[i][j] = 1;
			}
			else{
				for(k=0;k<j;k++)
				{
					temp = arr[i][k] * DP[i-1][j-k-1];
					if(max < temp)
					{
						max = temp; 
						maxOccured = k;
					}
				}
				DP[i][j] = max;
				people[i][j] = maxOccured+1;
			}
			
		}
	}
	printf("\nThe maximum success probability is %f", DP[N-1][P-1]);
	/*for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < P; ++j)
		{
			printf("%f %d\t", DP[i][j], people[i][j]);
		}
		printf("\n");
	}*/
	int peopleUsed=0, indexToDiv, assgn[N],l;
	float prob, toFind;
	printf("Assignment of people for max success probability: \n");
	for(i = N-1; i>=0; i--)
	{
		if(i==N-1)
		{
			peopleUsed += people[i][P-1];
			assgn[i] = people[i][P-1];
			prob = arr[i][people[i][P-1]-1];	//0.2
			toFind = DP[i][P-1] / prob;	//0.06
		}

		else if(i==0)
		{
			assgn[i] = P - peopleUsed;
			peopleUsed = P;
		}

		else
		{
			for(l=P-1; l>=0 ;l++)
			{
				if(arr[i][l] == toFind)
					break;
			}
			assgn[i] = people[i][l];
			peopleUsed += people[i][l];
			prob = arr[i][l];
			toFind = DP[i][l] / prob;
		}
	}
	for(i = 0;i<N;i++)
	{
		printf("Component %d: %d\n",i+1, assgn[i]);
	}
	return 0;
}