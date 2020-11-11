#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Value
{
	//here i is the number of planes loaded
	//here u is the length used in the left block
	//here v is the length used in the right block
	int i;
	int u;
	int v;
	struct Value* next;
}Value;

typedef struct Key
{
	int key;
	Value* head;
}Key;

typedef struct Hashtable
{
	int size;//n*L
	Key* arr;//to point the array of keys
}Hashtable;

int exhsearch(int i, int u, int v, int L, int lengthArr[], int n);
Hashtable* init(Hashtable* hash, int n, int L); //to create an empty Hashtable 
int search(Hashtable* hash,int i, int u, int v); //if a particular set (i,u,v) is present then return 1, else return 0
Hashtable* insert(Hashtable* hash, int i, int u, int v);//to insert a set (i,u,v) if not present
int hashsearch(int i, int u, int v, int L, int lengthArr[], int n,Hashtable* hash);

int main()
{
	int L,n;
	scanf("%d%d", &L, &n);
	int lengthArr[n];
	for (int i = 0; i < n; ++i)
		scanf("%d", &lengthArr[i]);
	clock_t c1, c2;
	double runtime;

	//for Exhaustive Search
	c1 = clock();
	/* Beginning of code whose running time you want to measure */
	int k = exhsearch(0,0,0,L,lengthArr,n);
	/* End of code whose running time you want to measure */
	c2 = clock();
	runtime = (double)(c2 - c1) / (double)CLOCKS_PER_SEC;
	printf("+++Exhaustive search\n");
	printf("k = %d\n", k-1);
	printf("Search time = %lf seconds\n", runtime);

	//for Hash based search
	Hashtable* hash = NULL;
	hash = init(hash, n , L);

	c1 = clock();
	/* Beginning of code whose running time you want to measure */
	int h = hashsearch(0,0,0,L,lengthArr,n,hash);
	/* End of code whose running time you want to measure */
	c2 = clock();
	runtime = (double)(c2 - c1) / (double)CLOCKS_PER_SEC;
	printf("\n+++Hash-based search\n");
	printf("Hash table of size %d initialised\n", n*L);
	printf("k = %d\n", h-1);
	printf("Search time = %lf seconds\n", runtime);
	return 0;
}

int hashsearch(int i, int u, int v, int L, int lengthArr[], int n,Hashtable* hash)
{
	//much similar to the recursive exhsearch
	//insert the set (i,u,v)
	//if we find a certain set (i+1, u+lengthArr[i], v) OR (i+1, u, v+lengthArr[i]) already in the hashTable
	//then the insert would just search and would return
	//this would fasten the search process and would not consider again 

	//if u == L or v==L then all the entire length of the left or right deck has been used of
	//thus return 0
	if(u>=L || v>=L)
		return 0;

	//if i == n, then all the air planes are used
	//now thus return 0;
	if(i>=n)
		return 0;

	int res = search(hash, i ,u , v);
	if(res == 1)
		return 0;	//the element has already been covered no need to follow the same path again

	//if the element is not present then a needed new path
	//thus the recursive call is made
	//this reduces the overlapping cases
	//insert the set and then make the recursive call 
	hash = insert(hash,i,u,v);
	int maxLeft = 1 + hashsearch(i+1, u+lengthArr[i] , v, L, lengthArr, n, hash);
	int maxRight = 1 + hashsearch(i+1, u , v+lengthArr[i], L, lengthArr, n, hash);
	return (maxRight > maxLeft) ? maxRight : maxLeft;
}

Hashtable* insert(Hashtable* hash, int i, int u, int v)
{
	int size = hash->size;
	int hashKey = (7*i+3*u+5*v) % size;//the key to which the set (i,u,v) would map to
	Value* newValue = (Value*)malloc(sizeof(Value));
	newValue->i = i;
	newValue->u = u;
	newValue->v = v;
	newValue->next = hash->arr[hashKey].head;
	hash->arr[hashKey].head = newValue;
	return hash; 
}

int search(Hashtable* hash, int i, int u, int v)
{
	int size = hash->size;
	int hashKey = (7*i + 3*u + 5*v) % size;
	Value* ll = hash->arr[hashKey].head;
	if(ll == NULL)
		return 0;	//indicating that the set (i,u,v) is not present in the hashtable

	while(ll)
	{
		if(ll->i == i && ll->u == u && ll->v == v)
			return 1;	//search successful, we found the required the set (i,u,v)

		ll = ll->next;
	}
	return 0;//the search over, but we could not find the set (i,u,v)
}

Hashtable* init(Hashtable* hash, int n, int L)
{
	hash = (Hashtable*)malloc(sizeof(Hashtable));
	hash->size = n*L;
	hash->arr = (Key*)malloc((hash->size)*sizeof(Key));
	for(int i = 0;i<n*L;i++)
	{
		hash->arr[i].key = i;
		hash->arr[i].head = NULL; 
	}
	return hash;
}

int exhsearch(int i, int u, int v, int L, int lengthArr[], int n)
{
	//here i is the number of planes loaded
	//here u is the length used in the left block
	//here v is the length used in the right block
	//here L is the maximum capacity available with each block
	//here lengthArr[] is the array which contains the lengths of the airplanes
	//here n is the size of the lengthArr[]

	//if u == L or v==L then all the entire length of the left or right deck has been used of
	//thus return 0
	if(u>=L || v>=L)
		return 0;

	//if i == n, then all the air planes are used
	//now thus return 0;
	if(i>=n)
		return 0;

	//if above simple base conditions are not used 
	//then add 1 indicating that the ith airplane is added
	//recurse on the remainnig part of the array
	
	int maxLeft = 	1 + exhsearch(i+1, u+lengthArr[i], v, L, lengthArr, n);
	int maxRight = 	1 + exhsearch(i+1, u, v+lengthArr[i], L, lengthArr, n);

	return (maxRight > maxLeft) ? maxRight : maxLeft;
}