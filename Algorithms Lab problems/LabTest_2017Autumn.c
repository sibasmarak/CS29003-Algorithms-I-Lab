#include <stdio.h>
#include <stdlib.h>

float esexchange(float A[], float B[], int i, int j, int n);
float grexchange(float A[], float B[], int n);
float dpexchange(float A[], float B[], int n);
float max(float a, float b);
int main()
{
	int n,i,j;
	printf("Input n: ");
	scanf("%d", &n);
	float A[n],B[n];

	for(i=0;i<n;i++)
		scanf("%f", &A[i]);
	for(j=0;j<n;j++)
		scanf("%f", &B[j]);

	float es = esexchange(A,B,0,0,n);
	printf("+++Exhaustive search\n");
	printf("Maximum exchange =  %0.2f\n", es);

	float gr = grexchange(A,B,n);
	printf("+++Greedy search\n");
	printf("Maximum exchange =  %0.2f\n", gr);

	float dp = dpexchange(A,B,n);
	printf("+++Dynamic Programming\n");
	printf("Maximum exchange =  %0.2f\n", dp);

	return 0;
}
float max(float a, float b)
{
	return (a>b)?a:b;
}
float dpexchange(float A[], float B[], int n)
{
	int i,j;
	float T[n+1][n+1], max3;
	float max1,max2;

	T[n][n] = 0;

	float exchrate = 100 + 11*(2*n-1);
	for(i=n-1;i>=0;i--)
	{
		T[n][i] = T[n][i+1] + B[i] * exchrate;
		T[i][n] = T[i+1][n] + A[i] * exchrate;
		exchrate -= 11;
	}

	//can do the above procedure, one by one for the two arrays, the required max string is itself getting formed in the T[][]
	/*float exchrate = 100 + 11*(2*n-1);
	for(i=n-1;i>=0;i--)
	{
		T[i][n] = T[i+1][n] + A[i] * exchrate;
		exchrate -= 11;
	}*/

	//finally going to be a symmetric matrix, thus I had thought correct, but that allocating array of n+1 size,
	//a coding practice couldn't think of, just loved it!

	for(i=n-1;i>=0;i--)
	{
		for(j=n-1;j>=0;j--)
		{
			max1 = T[i+1][j] + A[i] * (100 + 11*(i+j));
			max2 = T[i][j+1] + B[j] * (100 + 11*(i+j));
			T[i][j] = max(max1,max2);
		}
	}
	return T[0][0];
}

float grexchange(float A[], float B[], int n)
{
	if(n==1)
	{
		float max1 = 100* A[0] + 111 * B[0];
		float max2 = 100* B[0] + 111 * A[0];
		return (max2 > max1) ? max2 : max1;
	}

	float max=0;
	int i=0,j=0;
	while(i<n && j<n)
	{
		if(A[i] <= B[j])
		{
			max += A[i] * (100 + 11*(i+j));
			i++;
		}
		else
		{
			max += B[j] * (100 + 11*(i+j));
			j++;
		}
	}

	while(i<n)	//j==n
	{
		max += A[i] * (100 + 11*(i+j));
		i++;
	}

	while(j<n)	//i==n
	{
		max += B[j] * (100 + 11*(i+j));
		j++;
	}
	return max;
}


float esexchange(float A[], float B[], int i, int j, int n)
{
	if(i>=n && j>=n)
		return 0.0;

	float max1 = 0.0, max2 = 0.0;
	if(i<n)
		max1 = esexchange(A,B,i+1,j,n) + A[i] * (100 + 11*(i+j));
	
	if(j<n)
		max2 = esexchange(A,B,i,j+1,n) + B[j] * (100 + 11*(i+j));

	return (max2>max1)?max2:max1;
}