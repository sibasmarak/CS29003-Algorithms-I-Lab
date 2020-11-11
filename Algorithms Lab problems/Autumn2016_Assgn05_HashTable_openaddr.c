#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY '\0'
#define DELETED '\0'

typedef struct pair{
char x[21], y[21]; /* Pair of NULL-terminated strings */
} pair;

typedef struct htnode{
char att[21]; /* The attibute name: a NULL-terminated string */
int nassoc; /* Number of attibute associations in the other table */
int assoc[10]; /* Array of indices of the associated attibutes */
} htnode;

typedef struct hashtable{
int S; /* Size of A and B */
htnode *A, *B; /* attribute arrays : A stores x and B stores y*/
} hashtable;

hashtable* inittable(hashtable* T, int S);
void searchatt(hashtable* T, char z[], int a);
void searchpair(hashtable* T, pair p);
hashtable* insertpair(hashtable* T, pair p);
hashtable* deletepair(hashtable* T, pair p);

int main()
{
	int S,n;
	scanf("%d", &S);
	hashtable* T = NULL;
	T = inittable(T,S);
	pair p; 
	char x[10], y[10];
	do
	{
		printf("\n0 to exit");
		printf("\n1 to search on first attibute");
		printf("\n2 to search on first attibute");
		printf("\n3 to search a pair");
		printf("\n4 to insert a pair");
		printf("\n5 to delete a pair");
		printf("\nEnter choice: ");
		scanf("%d", &n);
		switch(n)
		{
			case 0: return 0; break;

			case 1: 
					scanf("%s", x);
					searchatt(T, x,1); break;

			case 2:	
					scanf("%s", y);
					searchatt(T, y,1);break;

			case 3:	
					scanf("%s%s", x ,y);
					p.x = x;p.y =y;
					searchpair(T, p); break;

			case 4:	
					scanf("%s%s", x ,y);
					p.x = x; p.y =y;//basically copy, better if you would have used char*
					T = insertpair(T, p); break;

			case 5:	
					scanf("%s%s", x ,y);
					p.x = x; p.y =y;
					T = deletepair(T, p); break;

			default : break;
		}
	}while(n!=0);
	return 0;
}
hashtable* deletepair(hashtable* T, pair p)
{
	//char x[10] = (char [])p.x;
	//char y[10] = p.y;
	//hash function to use : HS(a0a1a2 ...al−1) = 128×HS(a0a1a2 ...al−2) +ASCII(al−1) (mod S).
	int S = T->S, flagX = 0, flagY = 0;
	int hashKeyX = (int)p.x[0], length = strlen(p.x);

	//obtain the hashKey to which the given string has been mapped to in the hash table
	for(int i=1;i<length;i++)
		hashKeyX = ((int)p.x[i] + hashKeyX  * 128) % S;

	int hashKeyY = (int)p.y[0], length = strlen(y);

	//obtain the hashKey to which the given string has been mapped to in the hash table
	for(int i=1;i<length;i++)
		hashKeyY = ((int)p.y[i] + hashKeyY  * 128) % S;
	
	//hashKeyX contains the key for x[]
	//hashKeyY contains the key for y[]
	//indexX would be the location where x[] has been deleted
	//indexY would be the location where y[] has been deleted
	//flagX would contain if deleted in array A
	//flagY would contain if deleted in array B

	//now delete - 1. if nassoc is 1 then replace by DELETED
	//2. else just delete the corresponding from the assoc[] just which would be enough

	if(strcmp(T->A[hashKeyX].att,p.x)==0)
	{
		indexX = hashKeyX;//which means just remove the indexX from assoc[] from 
						 //corresponding B array
		if(T->A[hashKeyX].nassoc == 1)
			T->A[hashKeyX].att = DELETED;
			T->A[hashKeyX].nassoc = 0;
	}
	else{
	hashKey = (hashKeyX + 1)%S;
	while(hashKey!=hashKeyX && strcmp(T->A[hashKey].att, p.x) != 0)
		hashKey = (hashKey + 1)%S;	

	if(hashKey!=hashKeyX)
	{
		//succesfully can be deleted
		indexX = hashKey;
		//now if nassoc is 1, then mark it as DELETED
		if(T->A[hashKeyX].nassoc == 1)
			T->A[hashKeyX].att = DELETED;
			T->A[hashKeyX].nassoc = 0;
	}
	}

	//for y
	if(strcmp(T->B[hashKeyY].att,p.y)==0)
	{
		indexY = hashKeyY;//which means just remove the indexX from assoc[] from 
						 //corresponding B array
		if(T->B[hashKeyY].nassoc == 1)
			T->B[hashKeyY].att = DELETED;
			T->B[hashKeyY].nassoc = 0;
	}
	else{
	hashKey = (hashKeyY + 1)%S;
	while(hashKey!=hashKeyY && strcmp(T->B[hashKey].att, p.y) != 0)
		hashKey = (hashKey + 1)%S;	

	if(hashKey!=hashKeyY)
	{
		//succesfully can be deleted
		indexY = hashKey;
		//now if nassoc is 1, then mark it as DELETED
		if(T->B[hashKeyY].nassoc == 1)
			T->B[hashKeyY].att = DELETED;
			T->B[hashKeyY].nassoc = 0;
	}
	}

	if(T->A[indexX].nassoc > 0)
	{
		int l;
		for(l = 0; l<T->A[indexX].nassoc;l++)
		{
			if(T->A[indexX].assoc[l] == indexY)
				break;
		}
		if(l == nassoc-1)
			T->A[indexX].assoc[l] = -1;
		else
		{
			T->A[indexX].assoc[l] = T->A[indexX].assoc[nassoc-1];
			T->A[indexX].assoc[nassoc-1] = -1;
		}
	}

	if(T->B[indexY].nassoc > 0)
	{
		int l;
		for(l = 0; l<T->B[indexY].nassoc;l++)
		{
			if(T->B[indexY].assoc[l] == indexX)
				break;
		}
		if(l == nassoc-1)
			T->B[indexY].assoc[l] = -1;
		else
		{
			T->B[indexY].assoc[l] = T->B[indexY].assoc[nassoc-1];
			T->B[indexY].assoc[nassoc-1] = -1;
		}
	}
	return T;
}

hashtable* insertpair(hashtable* T, pair p)
{ 
	char x[10] = p.x;
	char y[10] = p.y;
	//hash function to use : HS(a0a1a2 ...al−1) = 128×HS(a0a1a2 ...al−2) +ASCII(al−1) (mod S).
	int S = T->S, flagX = 0, flagY = 0;
	int hashKeyX = (int)x[0], length = strlen(x);

	//obtain the hashKey to which the given string has been mapped to in the hash table
	for(int i=1;i<length;i++)
		hashKeyX = ((int)x[i] + hashKeyX  * 128) % S;

	int hashKeyY = (int)y[0], length = strlen(y);

	//obtain the hashKey to which the given string has been mapped to in the hash table
	for(int i=1;i<length;i++)
		hashKeyY = ((int)y[i] + hashKeyY  * 128) % S;
	
	//hashKeyX contains the key for x[]
	//hashKeyY contains the key for y[]
	//indexX would be the location where x[] enters
	//indexY would be the location where y[] enters
	//flagX would contain if inserted in array A
	//flagY would contain if inserted in array B

	//insert in array A, update the indexX and update flagX
	indexX = hashKeyX;
	if(T->A[indexX].att != EMPTY || T->A[indexX].att != DELETED){
		T->A[indexX].att = x;
		flagX = 1;
		// so that incrementing later would nullify the effect, and thus correct posn of x remains
		indexX = (indexX-1)%S;
	}
	indexX = (indexX+1)%S;
	
	else{
		while(indexX != hashKeyX && T->A[indexX].att != EMPTY || T->A[indexX].att != DELETED)
			indexX = (indexX+1)%S;
		if(indexX != hashKeyX){
			T->A[indexX].att = x;
			flagX = 1;
		}
	}

	//insert in array B, update the indexY and update flagY
	indexY = hashKeyY;
	if(T->B[indexY].att != EMPTY || T->B[indexY].att != DELETED){
		T->B[indexY].att = y;
		flagY = 1;
		// so that incrementing later would nullify the effect, and thus correct posn of x remains
		indexY = (indexY-1)%S;
	}
	index = (index+1)%S;
	
	else{
		while(indexY != hashKeyY && T->B[indexY].att != EMPTY || T->B[indexY].att != DELETED)
			indexY = (indexY+1)%S;
		if(indexY != hashKeyY){
			T->B[indexY].att = y;
			flagY = 1;
		}
	}

	//now update for the nassoc value and assoc array
	if(flagY == 1)
	{
		//meaning y has been successfully inserted
		//update the A array

		T->A[indexX].nassoc += 1;
		T->A[T->A[indexX].nassoc-1] = indexY;

	}

	if(flagX == 1)
	{
		//meaning x has been successfully inserted
		//update the B array

		T->B[indexY].nassoc += 1;
		T->B[T->B[indexY].nassoc-1] = indexX;
	}

	//hash = (7,4), insertion at (8,4)
	printf("hash = (%d,%d), insertion at (%d,%d)", hashKeyX, hashKeyY, indexX, indexY);
	return T;
}

void searchpair(hashtable* T, pair p)
{
	char x[10] = p.x;
	char y[10] = p.y;
	//hash function to use : HS(a0a1a2 ...al−1) = 128×HS(a0a1a2 ...al−2) +ASCII(al−1) (mod S).
	int S = T->S;
	int hashKey = (int)x[0], length = strlen(x);

	//obtain the hashKey to which the given string has been mapped to in the hash table
	for(int i=1;i<length;i++)
		hashKey = ((int)x[i] + hashKey  * 128) % S;

		//first find x in array A
		//then search for y in the array B using assoc[] 
		htnode node = T->A[hashKey];
		int index = hashKey;
		if(strcmp(node.att, x) == 0)
		{
			//thus the node.att and the input z are the same
			int Nassoc = node.nassoc;
			while(Nassoc)
			{
				int indexForB = node.nassoc - Nassoc;
				if(strcmp(y, T->B[indexForB].att) == 0)
				{
					printf("(%s, %s) Found at (%d, %d)\n", x,y,index, indexForB);
					return;
				}
				Nassoc--;
			}
			printf("(%s, %s) Not Found\n", x,y);
			return;
		}

		index = (index+1) % S;

		while(index!=hashKey)
		{
			//since we are following linear probing
			//thus we move as index is incremented in the above lines
			//till we reach the required node, whose att is equal to z
			if(strcmp(node.att, x) == 0)
			{
				//thus the node.att and the input z are the same
				int Nassoc = node.nassoc;
				while(Nassoc)
				{
					int indexForB = node.nassoc - Nassoc;
					if(strcmp(y, T->B[indexForB].att) == 0)
					{
						printf("(%s, %s) Found at (%d, %d)\n", x,y,index, indexForB);
						return;
					}
					Nassoc--;
				}	
				printf("(%s, %s) Not Found\n", x,y);
				return;
			}
			index = (index+1) % S;
		}
}

void searchatt(hashtable* T, char z[], int a)
{
	//hash function to use : HS(a0a1a2 ...al−1) = 128×HS(a0a1a2 ...al−2) +ASCII(al−1) (mod S).
	int S = T->S;
	int hashKey = (int)z[0], length = strlen(z);

	//obtain the hashKey to which the given string has been mapped to in the hash table
	for(int i=1;i<length;i++)
		hashKey = ((int)z[i] + hashKey  * 128) % S;

	//If a = 1, print all the strings y such that (z, y) is stored in T
	if(a==1)
	{
		//(Yellow,-) is associated with: Pen Shirt Table
		//search in the array A
		printf("(%s,-) is associated with: ", z);
		htnode node = T->A[hashKey];
		int index = hashKey;
		if(strcmp(node.att, z) == 0)
		{
			//thus the node.att and the input z are the same
			int Nassoc = node.nassoc;
			while(Nassoc)
			{
				int indexForB = node.nassoc - Nassoc;
				printf(" %s ", T->B[indexForB].att);
				Nassoc--;
			}
			printf("\n");
			return;
		}
		index = (index+1) % S;

		while(index!=hashKey)
		{
			//since we are following linear probing
			//thus we move as index is incremented in the above lines
			//till we reach the required node, whose att is equal to z
			if(strcmp(node.att, z) == 0)
			{
				//thus the node.att and the input z are the same
				int Nassoc = node.nassoc;
				while(Nassoc)
				{
					int indexForB = node.nassoc - Nassoc;
					printf(" %s ", T->B[indexForB].att);
					Nassoc--;
				}
				printf("\n");
				return;
			}
			index = (index+1) % S;
		}
	}


	//If a = 2, print all the strings x such that (x,z) is stored in T.
	else
	{
		//(-,Shirt) is associated with: Red Yellow Black Gray
		//search in array B
		printf("(-, %s) is associated with: ", z);
		htnode node = T->B[hashKey];
		int index = hashKey;
		if(strcmp(node.att, z) == 0)
		{
			//thus the node.att and the input z are the same
			int Nassoc = node.nassoc;
			while(Nassoc)
			{
				int indexForA = node.nassoc - Nassoc;
				printf(" %s ", T->A[indexForA].att);
				Nassoc--;
			}
			printf("\n");
			return;
		}
		index = (index+1) % S;

		while(index!=hashKey)
		{
			//since we are following linear probing
			//thus we move as index is incremented in the above lines
			//till we reach the required node, whose att is equal to z
			if(strcmp(node.att, z) == 0)
			{
				//thus the node.att and the input z are the same
				int Nassoc = node.nassoc;
				while(Nassoc)
				{
					int indexForA = node.nassoc - Nassoc;
					printf(" %s ", T->A[indexForA].att);
					Nassoc--;
				}
				printf("\n");
				return;
			}
			index = (index+1) % S;
		}
	}
}

hashtable* inittable(hashtable* T, int S)
{
	T = (hashtable*)malloc(sizeof(hashtable));
	T->S = S;
	T->A = (htnode*)malloc(S*sizeof(htnode));
	T->B = (htnode*)malloc(S*sizeof(htnode));
	for(int i = 0;i <S;i++)
	{
		T->A[i].att = EMPTY;
		T->A[i].nassoc = 0;
		T->B[i].att = EMPTY;
		T->B[i].nassoc = 0;
		memset(T->A[i].assoc, 0 , sizeof(T->A[i].assoc));
		memset(T->B[i].assoc, 0 , sizeof(T->B[i].assoc));
	}
	return T;
}