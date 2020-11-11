#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

int main()
{
	int T,i,j=0,k=0,row=0,col=0;
	FILE* in = fopen("input.txt", "r");
	if(in==NULL)
	{
		printf("File Does not exists\n");
		return 0;
	}

	fscanf(in, "%d", &T);
	char clauses[200];
	char x;i=0;
	char clauses2D[T+1][100];
	char literalsInClauses[26];
	int literalsInClausesVar = 0;
	memset(clauses2D, '\0', sizeof(clauses2D));	
	while((x=getc(in))!=EOF)
	{
		if(x == '\n')
		{
			clauses2D[row][col] = '\0';
			row = row+1;
			col = 0;
		}
		else
		{
			clauses2D[row][col++] = x;
			if(x>=97 && x<= 122)
			{
				int flag = 0; //means literal is not present in the literal Arr
				for(int k_ = 0;k_ < literalsInClausesVar ;k_++)
				{
					if(x == literalsInClauses[k_])
						flag = 1;
				}
				if(flag == 0)
				{
					literalsInClauses[literalsInClausesVar] = x;
					literalsInClausesVar++;
				}
			}
		}
	}

	//checking that if the clauses2D[][] has taken the correct parse format which is used later
	/*for(row = 0;row<T+1;row++)
	{
		for(col = 0; col<100;col++)
		{
			if(clauses2D[row][col] == '\0'){
				break;
			}
			printf("%c", clauses2D[row][col]);
		}
		printf("\n");
	}*/


	//checking if correct literals are there or not
	//for(int k_ = 0; k_ < literalsInClausesVar; k_++)
	//	printf("%c ", literalsInClauses[k_]);

	//to store the literals value, use the alphabet[]
	int alphabet[26];
	memset(alphabet, FALSE, sizeof(alphabet));

	//this below segment fixes the value of perfect implication literals as TRUE
	for(i=1;i<T+1;i++)
	{
		if(clauses2D[i][0] == 'I')
		{
			int v = (int)clauses2D[i][4] - 97;
			if(!alphabet[v])
				alphabet[v] = TRUE;
		}
	}
	

	int count = 0;

	for(i=1;i<T+1;i++)
	{
		if(clauses2D[i][0] >= 97 && clauses2D[i][0] <= 122)
		{
			char andArr[26];
			andArr[0] = clauses2D[i][0];
			int go = 1,j, andArrVar = 1;
			//store all the literals till we hit the letter 'I', cause next would be the implied variable
			while(clauses2D[i][go]!= 'I')
			{
				if(clauses2D[i][go]>= 97 && clauses2D[i][go] <= 122)
				{
					andArr[andArrVar] = clauses2D[i][go];
					andArrVar++; 
				}
				go++;
			}
			//all the anded literals are now with me, I have to make them FALSE as much as possible

			for(j=0;j<i;j++)
			{
				int ch = (int)andArr[j] - 97;
				if(alphabet[ch] == 1)
					count++;
			}
			int c = (int)clauses2D[i][go+4] - 97;
			if(count == i)
			{
				if(!alphabet[c])
					alphabet[c] = TRUE;
			}
			//else it is already is zero, we are happy!
		}
	}

	//the above code does the maximum false assignment as possible to the implied statements!
	//maintain a fixed array which fixes the value of literals till now
	//thus if we found satisfiable, then it is stisfiable
	//else sorry we have say that it would be unsatisfiable

	int fixArr[26];
	memset(fixArr, TRUE, sizeof(fixArr));

	//now just check the NEG statements, if they satisfy with the above fixed alphabet array assignment
	//if they do thus satisfiable
	//else non-satisfiable

	int satisfiable[T+1];
	memset(satisfiable, TRUE, sizeof(satisfiable));

	//if somewhere found unsatisfiable, then the satisfiable[] would be updated
	//at that particular index we would change it to FALSE
	//finally check the satisfiable[], if all are TRUE, then satisfiable
	//else not satisfiable

	count = 0;
	for(i=1;i<T+1;i++)
	{
		if(clauses2D[i][0] == 'N')
		{
			char arr[26];
			int go=0,arrVar = 0;
			while(clauses2D[i][go]!= '\0')
			{
				if(clauses2D[i][go]>= 97 && clauses2D[i][go] <= 122)
				{
					arr[arrVar] = clauses2D[i][go];
					arrVar++; 
				}
				go++;
			}
			//I have all the literals in the Negation statement.
			//Now check the literals and those of them which are TRUE, ideally should be less
			//than the total literals present in the negation statement (arrVar)

			for(go = 0;go<arrVar;go++)
			{
				int ch = (int)arr[go] - 97;
				if(alphabet[ch] == TRUE)
					count++;

			}

			//check the count with arrVar, if both matches then all the literals have fixed value of TRUE
			//thus the negation statement would not be satisfiable, thus corressponding index
			//in satisfiable[] would be converted to FALSE!

			if(count == arrVar)
				satisfiable[i] = FALSE;
		}
	}
	//check for the unsatisfiablilty
	//if for any one of the index, we find that in the satisfiable[] is false
	//then it is unsatisfiable
	for(int ind = 0; ind<T+1; ind++)
	{
		if(satisfiable[ind] == FALSE)
		{
			printf("Not satisfiable\n");
			return 0;
		}
	}

	//else satisfiable
	printf("Satisfiable: \n");
	//pick out the literals in the clauses2D i.e. literalsInClauses[], then print their values

	for(int k_ = 0; k_ < literalsInClausesVar; k_++)
	{
		int ch = (int)literalsInClauses[k_] - 97;
		int v = alphabet[ch];
		if(v)
			printf("%c = TRUE\n", literalsInClauses[k_]);
		else
			printf("%c = FALSE\n", literalsInClauses[k_]);

	}	
	return 0;
}