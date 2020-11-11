//NAME: SIBA SMARAK PANIGRAHI
//ROLL NO.: 18CS10069
//PC NO.: 66


/*
ALGORITHM PARADIGM - 
	Using dynamic programming -
	int DP[K+1][N-1][N]; 
	//define DP[k][i][j] as follow -  first stock bought on i-th day, 
	//last stock sold on j-th day
	//and the number of maximum transactions used is k

	//now for K=0 transactions everything should be zero, since no transactions are done

	//first compute K=1 now, when only maximum of 1 transaction is allowed
	//the diagonals of K=1, with DP[1][i][i+1] is just going to be the difference of adjacent elements of stockArr
	//else it would be zero
	//now for the rest of the elements of DP[1][][], we have to do:
	//DP[1][i][j] = maximum(DP[1][i][l] + DP[0][l][j],stockArr[j] - stockArr[i]); 
	//and l can vary from i to j-1 (j>i)

	//DP[k][i][j] would be evaluated as follows: 
	//DP[k][i][j] = maximum( DP[x][i][l] + DP[k-x][l+1][j] ) 
	//when x can vary from 0 to k
	//and l can vary from i to j-1 (j>i)

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Efficient solution
int main()
{
	//N denotes the number of days
	//K denotes the number of maximum transaction
	//stockArr[] contains the stock price of each day
	int i,j,k,N,K, diagonal,l,x;
	scanf("%d", &N);
	int stockArr[N];
	for(i=0;i<N;i++)
		scanf("%d", &stockArr[i]);

	scanf("%d", &K);

	//Now declare a 3-D array as DP[k][i][j]
	//here i is the start day
	//here j is the end day
	//here k is the number of transaction
	//DP[k][i][j] implies that first stock bought on i-th day, 
	//last stock sold on j-th day
	//and the number of maximum transactions used is k

	//N-1 because in any case you can't buy on N-th day, since the transaction would be then incomplete
	int DP[K+1][N-1][N];
	//initialising every element of DP as 0
	for(k=0;k<K+1;k++)
	{
		for(i=0;i<N-1;i++)
		{
			for(j=0;j<N;j++)
			{
				DP[k][i][j] = 0;
			}
		}
	}

	//now for K=0 transactions everything should be zero, since no transactions are done
	//first compute K=1 now, when only maximum of 1 transaction is allowed

	//the diagonals of K=1, with DP[1][i][i+1] is just going to be the difference of adjacent elements of stockArr
	//else it would be zero

	for(i=0;i<N-1;i++)
	{
		DP[1][i][i+1] = (0 > (stockArr[i+1]-stockArr[i])) ? 0 : stockArr[i+1]-stockArr[i];
	}

	//now for the rest of the elements of DP[1][][], we have to do:
	//DP[1][i][j] = maximum(DP[1][i][l] + DP[0][l][j],stockArr[j] - stockArr[i]); (j>i)
	//compute it diagonally as it was done in Matrix Chain Multiplication

	for(diagonal = 2; diagonal<N; diagonal++)
	{
		for(i=0;i<N-diagonal;i++)
		{
			j = i+diagonal;
			int temp = DP[1][i][j];
			for(l=i;l<j;l++)//l can max go upto j-1
			{
				int T = DP[1][i][l] + DP[0][l][j];
				if(T > temp)
					temp = T;
			}
			int mayBeMax = stockArr[j] -  stockArr[i];
			if(temp > mayBeMax)
				mayBeMax = temp;
			//else mayBeMax will be assigned
			DP[1][i][j] = mayBeMax;
		}
	}

	//till now for only K=0 and for K=1 we have computed successfully
	//now we have to compute for the rest of the transaction values
	//DP[k][i][j] would be evaluated as follows: 
	//DP[k][i][j] = maximum( DP[x][i][l] + DP[k-x][l+1][j] ) when x can vary from 0 to k
	//and l can vary from i to j-1

	//we have to perform the above in a way similar to the Matrix Chain Multiplication
	//that is we have to perform diagonally

	//loop for a particular transaction beginning from 2
	for(k=2;k<K+1;k++)
	{
		//for that particular transaction, pick the diagonal from diagonal number 1;
		for(diagonal = 1; diagonal<N; diagonal++)
		{
			//now for the i-th index
			for(i=0;i<N-diagonal;i++)
			{
				j = i+diagonal;
				int temp = DP[k][i][j];

				for(x=0;x<=k;x++)
				{
					for(l=i;l<j;l++)//l should be atleast i and maximum can go upto j-1
					{
						int T = DP[x][i][l] + DP[k-x][l][j];
						if(T > temp)
							temp = T;
					}
				}

				DP[k][i][j] = temp;
			}
		}
	}
	//checking for the final values
	FILE* fout = fopen("18CS10069-lt-output.txt","w");
	fprintf(fout, "%d", DP[K][0][N-1]);

	//to check the entire DP[][][]
	//God , brother please help me
	//Thank you so much, god! I ma now very very very happy, thank you!
	//So sorry that I can't write these very lines and submit
	//but back in hall I would add these lines and edit in GitHub
	/*for(k=0;k<K+1;k++)
	{
		for(i=0;i<N-1;i++)
		{
			for(j=0;j<N;j++)
			{
				printf("%d\t", DP[k][i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}*/
	return 0;
}