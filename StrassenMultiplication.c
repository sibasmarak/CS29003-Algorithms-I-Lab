#include <stdio.h>
#include <string.h>

void doStrassenMultiplication(int n, int A[][n], int B[][n], int C[][n]);
//int** add(int n,int A[][n],int B[][n]);
//int** subtract(int n,int A[][n],int B[][n]);
void add(int n,int A[][n],int B[][n],int R[][n]);
void add(int n,int A[][n],int B[][n],int R[][n]);

int main()
{
	int A[4][4] = {{1,2,3,4},{1,2,3,4},{1,2,3,4},{1,2,3,4}};
	int B[4][4] = {{1,2,3,4},{1,2,3,4},{1,2,3,4},{1,2,3,4}};
	int C[4][4]; int n=4;
	memset(C,0,sizeof(C));
	doStrassenMultiplication(n,A,B,C);
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			printf("%d ", C[i][j]);
		}
		printf("\n");
	}
	return 0;
}
void doStrassenMultiplication(int n, int A[][n], int B[][n], int C[][n])
{
	if(n<=2)
	{
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				for(int k=0;k<n;k++)
				{
					C[i][j] = C[i][j]+A[i][k]*B[k][j];
				}
			}
		}
		return;
	}
	int rightUpperHalfA[n/2][n/2];	//A12
	int leftUpperHalfA[n/2][n/2];	//A11
	int leftLowerHalfA[n/2][n/2];	//A21
	int rightLowerHalfA[n/2][n/2];	//A22
	int rightUpperHalfB[n/2][n/2];	//B12
	int leftUpperHalfB[n/2][n/2];	//B11
	int leftLowerHalfB[n/2][n/2];	//B21
	int rightLowerHalfB[n/2][n/2];	//B22
	for(int i=0;i<n/2;i++)
	{
		for(int j=0;j<n/2;j++)
		{
			leftUpperHalfA[i][j]=A[i][j];
			leftLowerHalfA[i][j]=A[n/2+i][j];
			rightUpperHalfA[i][j]=A[i][n/2+j];
			rightLowerHalfA[i][j]=A[n/2+i][n/2+j];
			leftUpperHalfB[i][j]=B[i][j];
			leftLowerHalfB[i][j]=B[n/2+i][j];
			rightUpperHalfB[i][j]=B[i][n/2+j];
			rightLowerHalfB[i][j]=B[n/2+i][n/2+j];
		}
	}
	int R1[n/2][n/2],R2[n/2][n/2],R3[n/2][n/2],R4[n/2][n/2],R5[n/2][n/2],R6[n/2][n/2],R7[n/2][n/2],R8[n/2][n/2],R9[n/2][n/2],
	R10[n/2][n/2];
	/*int** R1,R2,R3,R4,R5,R6,R7,R8,R9,R10,M1,M2,M3,M4,M5,M6,M7;
	R1 = (int**)malloc((n/2)*(n/2)*sizeof(int));
	R2 = (int**)malloc((n/2)*(n/2)*sizeof(int));
	R3 = (int**)malloc((n/2)*(n/2)*sizeof(int));
	R4 = (int**)malloc((n/2)*(n/2)*sizeof(int));
	R5 = (int**)malloc((n/2)*(n/2)*sizeof(int));
	R6 = (int**)malloc((n/2)*(n/2)*sizeof(int));
	R7 = (int**)malloc((n/2)*(n/2)*sizeof(int));
	R8 = (int**)malloc((n/2)*(n/2)*sizeof(int));
	R9 = (int**)malloc((n/2)*(n/2)*sizeof(int));
	R10 = (int**)malloc((n/2)*(n/2)*sizeof(int));
	M1 = (int**)malloc((n/2)*(n/2)*sizeof(int));
	M2 = (int**)malloc((n/2)*(n/2)*sizeof(int));
	M3 = (int**)malloc((n/2)*(n/2)*sizeof(int));
	M4 = (int**)malloc((n/2)*(n/2)*sizeof(int));
	M5 = (int**)malloc((n/2)*(n/2)*sizeof(int));
	M6 = (int**)malloc((n/2)*(n/2)*sizeof(int));
	M7 = (int**)malloc((n/2)*(n/2)*sizeof(int));*/
	memset(R1,0,sizeof(R1));
	memset(R2,0,sizeof(R2));
	memset(R3,0,sizeof(R3));
	memset(R4,0,sizeof(R4));
	memset(R5,0,sizeof(R5));
	memset(R6,0,sizeof(R6));
	memset(R7,0,sizeof(R7));
	memset(R8,0,sizeof(R8));
	memset(R9,0,sizeof(R9));
	memset(R10,0,sizeof(R10));
	/*R1 = add(n/2,leftUpperHalfA,rightLowerHalfA,R1);	//A11+A22	
	R2 = add(n/2,leftUpperHalfB,rightLowerHalfB,R2);	//B11+B22
 	R3 = add(n/2,leftLowerHalfA,rightLowerHalfA,R3); //A21+A22
	R4 = subtract(n/2,rightUpperHalfB,rightLowerHalfB,R4);	//B12-B22
	R5 = subtract(n/2,leftLowerHalfB,leftUpperHalfB,R5);	//B21-B11
	R6 = add(n/2,leftUpperHalfA,rightUpperHalfA,R6);	//A11+A12
	R7 = subtract(n/2,leftLowerHalfA,leftUpperHalfA,R7);	//A21-A11
	R8 = add(n/2,leftUpperHalfB,rightUpperHalfB,R8);	//B11+B12
	R9 = subtract(n/2,rightUpperHalfA,rightLowerHalfA,R9);	//A12-A22	
	R10 = add(n/2,leftLowerHalfB,rightLowerHalfB,R10); //B21+B22*/
	add(n/2,leftUpperHalfA,rightLowerHalfA,R1);	//A11+A22	
	add(n/2,leftUpperHalfB,rightLowerHalfB,R2);	//B11+B22
 	add(n/2,leftLowerHalfA,rightLowerHalfA,R3); //A21+A22
	subtract(n/2,rightUpperHalfB,rightLowerHalfB,R4);	//B12-B22
	subtract(n/2,leftLowerHalfB,leftUpperHalfB,R5);	//B21-B11
	add(n/2,leftUpperHalfA,rightUpperHalfA,R6);	//A11+A12
	subtract(n/2,leftLowerHalfA,leftUpperHalfA,R7);	//A21-A11
	add(n/2,leftUpperHalfB,rightUpperHalfB,R8);	//B11+B12
	subtract(n/2,rightUpperHalfA,rightLowerHalfA,R9);	//A12-A22	
	add(n/2,leftLowerHalfB,rightLowerHalfB,R10); //B21+B22	
	int M1[n/2][n/2],M2[n/2][n/2],M3[n/2][n/2],M4[n/2][n/2],M5[n/2][n/2],M6[n/2][n/2],M7[n/2][n/2];
	/*for (int i = 0; i < n/2; ++i)
	{
		for (int j = 0; j < n/2; ++i)
		{
			M1[i][j] = 0;
			M2[i][j] = 0;
			M3[i][j] = 0;
			M4[i][j] = 0;
			M5[i][j] = 0;
			M6[i][j] = 0;
			M7[i][j] = 0;
		}
	}*/
	memset(M1,0,sizeof(M1));
	memset(M2,0,sizeof(M2));
	memset(M3,0,sizeof(M3));
	memset(M4,0,sizeof(M4));
	memset(M5,0,sizeof(M5));
	memset(M6,0,sizeof(M6));
	memset(M7,0,sizeof(M7));
	doStrassenMultiplication(n/2, R1,R2,M1);
	doStrassenMultiplication(n/2,R3,leftUpperHalfB,M2);
	doStrassenMultiplication(n/2,leftUpperHalfA,R4,M3);
	doStrassenMultiplication(n/2,rightLowerHalfA,R5,M4);
	doStrassenMultiplication(n/2,R6,rightLowerHalfB,M5);
	doStrassenMultiplication(n/2,R7,R8,M6);
	doStrassenMultiplication(n/2,R9,R10,M7);

	for(int i=0;i<n/2;i++)
	{
		for(int j=0;j<n/2;j++)
		{
			C[i][j] = M1[i][j]+M4[i][j]-M5[i][j]+M7[i][j];
			C[n/2+i][j] = M2[i][j]+M4[i][j];
			C[i][n/2+j] = M3[i][j]+M5[i][j];
			C[n/2+i][n/2+j] = M1[i][j]+M3[i][j]-M2[i][j]+M6[i][j];
		}
	}
	return;
}
void add(int n,int A[][n],int B[][n],int R[][n])
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			R[i][j] = A[i][j]+B[i][j];
		}
	}
}
void subtract(int n,int A[][n],int B[][n],int R[][n])
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			R[i][j] = A[i][j]-B[i][j];
		}
	}
}	

