#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void getMinimumPenalty(char gene1[], char gene2[], int misMatchPenalty, int gapPenalty, int DP[strlen(gene1)+1][strlen(gene1)+1]);
void printTheSeq(char gene1[], char gene2[],int len1, int len2, int DP[len1][len2]);

int MIN(int a, int b)
{
	return (a<b)?a:b;
}
int main()
{
	char gene1[] = "AGGGCT";//"AACAGTTACC"; 
	char gene2[] = "AGGCA";//"TAAGGTCA";
	int misMatchPenalty = 3;
	int gapPenalty = 2;
	int len1 = strlen(gene1);	//len1 = 10
	int len2 = strlen(gene2);	//len2 = 8
	int dp[len1+1][len2+1],i,j;
	getMinimumPenalty(gene1, gene2,  
        misMatchPenalty, gapPenalty, dp); 
	for(i=0;i<=len1;i++)
	{
		for(j=0;j<=len2;j++)
		{
			printf("%d\t", dp[i][j]);
		}
		printf("\n");
	}
	printf("MINIMUM PENALTY: %d\n", dp[0][0]);
	printTheSeq(gene1, gene2,len1, len2, dp);
	return 0;
}
void printTheSeq(char gene1[], char gene2[],int len1, int len2, int DP[len1][len2])
{
	int i=0, j=0,G1=0,G2=0;	//len1 = 10, len2 = 8;
	char newGene1[len1+1]; 
	char newGene2[len2+1];
	while(i<=len1 && j<=len2)
	{
		int min = MIN(DP[i+1][j+1],MIN(DP[i+1][j], DP[i][j+1]));
		if(min == DP[i+1][j+1])
		{
			newGene1[G1++] = gene1[i++];
			newGene2[G2++] = gene2[j++];
		}
		else if(min == DP[i][j+1])
		{
			newGene1[G1++] = gene1[i++];
			newGene2[G2++] = '_';
			/*newGene1[G1++] = '_';
			newGene2[G2++] = gene2[j++];*/
		}
		else if(min == DP[i+1][j])
		{
			newGene1[G1++] = '_';
			newGene2[G2++] = gene2[j++];
			/*newGene1[G1++] = gene1[i++];
			newGene2[G2++] = '_';*/
		}
	}
	while(i<=len1)
	{
		newGene1[G1++] = gene1[i++];
		newGene2[G2++] = '_';
	}
	while(j<=len2)
	{
		newGene1[G1++] = '_';
		newGene2[G2++] = gene2[j++];
	}
	printf("G1: %d     G2: %d\n", G1, G2);
	printf("newGene1 : %s\n", newGene1);
	printf("newGene2 : %s\n", newGene2);
}
void getMinimumPenalty(char gene1[], char gene2[], int misMatchPenalty, 
		int gapPenalty, int DP[strlen(gene1)+1][strlen(gene2)+1])
{
	int i,j,G1=9,G2=7,penalty;
	int len1 = strlen(gene1);	//len1 = 10
	int len2 = strlen(gene2);	//len2 = 8
	for(i=0;i<=len1;i++)
		DP[len1-i][len2] = i*gapPenalty;		//base case 1(if a gene ends then we have to manage with gaps only!)
	for(i=0;i<=len2;i++)
		DP[len1][len2-i] = i*gapPenalty;		//base case 2(if a gene ends then we have to manage with gaps only!)
	for(i=len1-1;i>=0;i--)
	{
		for(j=len2-1;j>=0;j--)
		{
			if(gene1[i] == gene2[j])
				penalty = 0;	//if the two match
			else
				penalty = misMatchPenalty;	//if the two mismatch

			DP[i][j] = MIN(DP[i+1][j+1] + penalty, MIN(DP[i][j+1] + 2, DP[i+1][j]+2));	//if the minimum is obtained when we replace a gap, 
																						//instead of taking the misMatch Penanlty
		}
	}
	return;
}