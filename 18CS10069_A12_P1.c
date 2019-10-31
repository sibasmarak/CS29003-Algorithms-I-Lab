//NAME: SIBA SMARAK PANIGRAHI
//ROLL NO.: 18CS10069

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structure to store the details about heap
typedef struct heap
{
	int jobID;//unique number for each process
	int processBurstTime;//total amount of time required to complete the process
	int processRemainingTime;//the amount of time remaining to complete the process
	int processArrivalTime;//time at which the process was submitted to the system
	int processPriority;//priority assigned to the process

}heap;
//structure which basically contians an array of heap data structure
typedef struct bigHeap
{
	heap* head;
	int presentElem;
	int capacity;
}bigHeap;
//structure to store the array of 5 heaps
typedef struct superHeap
{
	bigHeap* fiveHeaps;//array of five pointers to the array of heaps
	int counter;//store the present time of the system; not required though

}superHeap;

//structure to store the output information
typedef struct out
{
	int jobID;
	int processArrivalTime;
	int processEndTime;//time at which the process was entirely completed
}out;


int parent(int i);
superHeap* addToSuperHeap(superHeap* sh, heap h);
void heapify(superHeap** SH, int i, int index);
heap* getMin(superHeap* sh);
heap* extractMin(superHeap** SH);
int main()
{
	int i;
	FILE* in = fopen("Input.txt", "r");
	if(in == NULL)
	{
		printf("Not Found the File Path\n");
		return 0;
	}
	//create an array of 5 priorities with each being a pointer to a min_heap
	superHeap* sh = (superHeap*)malloc(sizeof(superHeap));
	sh->fiveHeaps = (bigHeap*)malloc(5 * sizeof(bigHeap));
	

	//we have thus far created the sH which is as in the diagram in the copy
	//now we have to read the input file and create the arrays

	int N, totalTimeCPU = 0;//totalTimeCPU would contain the time uits to be used to be used
	fscanf(in, "%d", &N);
	//create an array of heap data_structure so as to store the information of file
	heap jobInfoArr[N];
	for(i = 0; i < N; i++)
	{
		fscanf(in, "%d%d%d%d", &jobInfoArr[i].jobID, &jobInfoArr[i].processArrivalTime, &jobInfoArr[i].processBurstTime, 
			&jobInfoArr[i].processPriority);
		jobInfoArr[i].processRemainingTime = jobInfoArr[i].processBurstTime - jobInfoArr[i].processArrivalTime;
		totalTimeCPU += jobInfoArr[i].processBurstTime;
	}

	for(i=0;i<5;i++)
	{
		sh->fiveHeaps[i].presentElem = 0;
		sh->fiveHeaps[i].capacity = N;
	}
	//considering the worst case that all N jobs have the same priority
	for(i = 0; i < 5; i++)
		sh->fiveHeaps[i].head = (heap*)malloc(N * sizeof(heap));

	// for(i = 0; i < N; i++)
	// {
	// 	printf("%d %d %d %d\n", jobInfoArr[i].jobID, jobInfoArr[i].processArrivalTime, jobInfoArr[i].processBurstTime, 
	// 		jobInfoArr[i].processPriority);
	// }


	//successfully got the info about jobs!

	//now remove each job from the jobInfoArr[]
	//and add it to the sh as per its priority
	//this would initialise the sh

	for(i = 0; i < N; i++)
	{
		sh = addToSuperHeap(sh, jobInfoArr[i]);
	}

	for(i = 0;i<5;i++)
	{
		for(int j = 0;j<sh->fiveHeaps[i].presentElem;j++)
			printf("%d ", sh->fiveHeaps[i].head[j].jobID);
		printf("\n");
	}
	// for(i = 0; i < N; i++)
	//  {
	//  	printf("%d %d %d %d\n", jobInfoArr[i].jobID, jobInfoArr[i].processArrivalTime, jobInfoArr[i].processBurstTime, 
	//  		jobInfoArr[i].processPriority);
	//  }

	//successfully inserted the jobs!

	//create the output Array
	out outputArr[N];

	int time;
	heap *inCPU, *previousInCPU;
	inCPU = extractMin(&sh);
	printf("inCPU: %d %d\n",inCPU->jobID, inCPU->processPriority);
	previousInCPU = inCPU;
	inCPU->processArrivalTime = 0;
	for(time = 1; time < totalTimeCPU;time++)
	{
		
		//as time increments 
		//decrease the remaining time of that particular heap until it reaches zero
		//then getMin from the sh
		//compare the priority > processRemainingTime > jobID
		//if at any point the getMin wins then change the inCPU to getMin
		//extract the minimum of all the five heaps 
		//then add the previousInCPU to the sh
		//assume it to be in the CPU
		//change its processArrivalTime to the current time

		//decrementing the processRemainingTime
		//if processRemainingTime becomes zero, then make inCPU and previousInCPU both NULL
		//renew inCPU

		sh->counter = time;
		inCPU->processRemainingTime--;
		int processRemainingTime = inCPU->processRemainingTime;
		if(processRemainingTime == 0)
		{
			//the job has ended 
			//do the above necessary steps
			//first add that to out array, as per jobID
			int ID = inCPU->jobID-1;
			outputArr[ID].jobID = inCPU->jobID;
			outputArr[ID].processArrivalTime = inCPU->processArrivalTime;
			outputArr[ID].processEndTime = time;
			//added to the output array
			inCPU = NULL;
			previousInCPU = NULL;
			inCPU = extractMin(&sh);
			//continue;
		} 
		else
		{
			heap* tempCPU = getMin(sh);
			if(tempCPU->processPriority <= inCPU->processPriority)
			{
				//something needs to be done
				//as a lower priority process comes
				if(tempCPU->processPriority == inCPU->processPriority)
				{
					//check their remaining time
					//if comes out to be the same check their jobID
					if(tempCPU->processRemainingTime == inCPU->processRemainingTime)
					{
						//check their jobID
						if(tempCPU->jobID < inCPU->jobID)
						{
							//we need to change the inCPU
							sh = addToSuperHeap(sh, *(inCPU));
							inCPU = extractMin(&sh);
							inCPU->processArrivalTime = time;
							//continue;
						}
					}
					else if(tempCPU->processRemainingTime < inCPU->processRemainingTime)
					{
						//we need to change the inCPU
						sh = addToSuperHeap(sh, *(inCPU));
						inCPU = extractMin(&sh);
						inCPU->processArrivalTime = time;
						//continue;
					}
				}
				else if(tempCPU->processPriority < inCPU->processPriority)
				{
					//we need to change the inCPU
					sh = addToSuperHeap(sh, *(inCPU));
					inCPU = extractMin(&sh);
					inCPU->processArrivalTime = time;
					//continue;
				}
			}
		}
	}

	FILE* fout = fopen("Output.txt", "w");
	if(fout == NULL)
	{
		printf("Not Found Path\n");
		return 0;
	}

	for(i=0;i<N;i++)
	{
		fprintf(fout, "%d %d %d\n", outputArr[i].jobID, outputArr[i].processArrivalTime, outputArr[i].processEndTime);
	}
	return 0;
}
heap* getMin(superHeap* sh)
{
	//returns the minimum heap's address
	int i;
	heap* toReturn = NULL;
	for(i=0;i<5;i++)
	{
		if(sh->fiveHeaps[i].presentElem!=0)
		{
			//means the min of this is the most priority element
			//do not delete it
			heap min = sh->fiveHeaps[i].head[0];
			toReturn = &min;
			break;
		}
	}
	return toReturn;
}
heap* extractMin(superHeap** SH)
{
	//returns the min heap element(i.e. process)
	//checks the priorities one by one
	//wherever first gets a mimimum element (if presentElem == 0) then skip for that priority
	//deletes that and heapifies that particular min_heap array
	//returns the extracted heap's address
	int i;
	heap* toReturn = NULL;
	superHeap* sh = *SH;
	for(i=0;i<5;i++)
	{
		if(sh->fiveHeaps[i].presentElem!=0)
		{
			//means the min of this is the most priority element
			//delete it and then heapify
			heap min = sh->fiveHeaps[i].head[0];
			toReturn = &min;
			int presentElem = sh->fiveHeaps[i].presentElem - 1;
			if(presentElem == 0)
			{
				sh->fiveHeaps[i].presentElem--;
				return toReturn;
			}
			sh->fiveHeaps[i].head[0] = sh->fiveHeaps[i].head[presentElem];
			//now carry the heapification of the root
			int index = 0;
			heapify(&sh, i, 0);
			break;
		}
	}
	return toReturn;
}
void heapify(superHeap** SH, int i, int index)
{
	//to heapify index of sh->fiveHeaps[i].head
	superHeap* sh = *SH;
	int n = sh->fiveHeaps[i].presentElem;
	int l = 2*index+1;
	int r = 2*index + 2;
	int smallest = index;
	if(l<n && sh->fiveHeaps[i].head[l].processPriority <= sh->fiveHeaps[i].head[smallest].processPriority)
	{
		if(sh->fiveHeaps[i].head[l].processPriority < sh->fiveHeaps[i].head[smallest].processPriority)
			smallest = l;
		else
		{
			//check their remaining time
			if(sh->fiveHeaps[i].head[l].processRemainingTime == sh->fiveHeaps[i].head[smallest].processRemainingTime)
			{
				//check jobIDs
				if(sh->fiveHeaps[i].head[l].jobID < sh->fiveHeaps[i].head[smallest].jobID)
					smallest = l;
			}
			else if(sh->fiveHeaps[i].head[l].processRemainingTime < sh->fiveHeaps[i].head[smallest].processRemainingTime)
			{
				smallest = l;
			}
		}
	}
	if(r<n && sh->fiveHeaps[i].head[r].processPriority <= sh->fiveHeaps[i].head[smallest].processPriority)
	{
		if(sh->fiveHeaps[i].head[r].processPriority < sh->fiveHeaps[i].head[smallest].processPriority)
			smallest = r;
		else
		{
			//check their remaining time
			if(sh->fiveHeaps[i].head[r].processRemainingTime == sh->fiveHeaps[i].head[smallest].processRemainingTime)
			{
				//check jobIDs
				if(sh->fiveHeaps[i].head[r].jobID < sh->fiveHeaps[i].head[smallest].jobID)
					smallest = r;
			}
			else if(sh->fiveHeaps[i].head[r].processRemainingTime < sh->fiveHeaps[i].head[smallest].processRemainingTime)
			{
				smallest = r;
			}
		}
	}
	if(smallest!=index)
	{
		//swap the index with the smallest
		//recursively heapify with smallest
		heap temp = sh->fiveHeaps[i].head[index];
		sh->fiveHeaps[i].head[index] = sh->fiveHeaps[i].head[smallest];
		sh->fiveHeaps[i].head[smallest] = temp;
		heapify(SH, i, smallest);
	}
}
int parent(int i)
{
	return (i<=0) ? 0 : (i-1)/2;
}

superHeap* addToSuperHeap(superHeap* sh, heap h)
{
	printf("h.jobID: %d\n", h.jobID);
	int priority = h.processPriority;
	int presentElem = sh->fiveHeaps[priority - 1].presentElem;
	int capacity = sh->fiveHeaps[priority - 1].capacity;
	if(presentElem >= capacity)//if the capacity is already full
	{
		printf("Can't Insert!\n");
		return sh;
	}

	sh->fiveHeaps[priority - 1].head[presentElem] = h;//the data now inserted , now just heapify the particular array
	sh->fiveHeaps[priority - 1].presentElem++;
	//do the sift up to situate the inserted element at the correct place
	int index = presentElem - 1;
	int par = parent(index);

	while(par > 0)
	{
		if(sh->fiveHeaps[priority-1].head[par].processPriority 
		> sh->fiveHeaps[priority-1].head[index].processPriority)//compare the priorities
		{
			//sift up the inserted element 
			heap temp = sh->fiveHeaps[priority-1].head[par];
			sh->fiveHeaps[priority-1].head[par] = sh->fiveHeaps[priority-1].head[index];
			sh->fiveHeaps[priority-1].head[index] = temp;
		}
		//now if the priorities are the same
		//then insert on the basis of processRemainingTime

		else if(sh->fiveHeaps[priority-1].head[par].processPriority == 
											sh->fiveHeaps[priority-1].head[index].processPriority)//compare the priorities
		{
			if(sh->fiveHeaps[priority-1].head[par].processRemainingTime > 
			sh->fiveHeaps[priority-1].head[index].processRemainingTime)//compare the priorities
			{
				//sift up the inserted element 
				heap temp = sh->fiveHeaps[priority-1].head[par];
				sh->fiveHeaps[priority-1].head[par] = sh->fiveHeaps[priority-1].head[index];
				sh->fiveHeaps[priority-1].head[index] = temp;
			}
		}
		par = parent(par);
	}

	par = parent(index);//to complete the heapify process for the upper three elements
	if(sh->fiveHeaps[priority-1].head[par].processPriority 
		>= sh->fiveHeaps[priority-1].head[index].processPriority)//compare the priorities
	{
			if(sh->fiveHeaps[priority-1].head[par].processRemainingTime > 
			sh->fiveHeaps[priority-1].head[index].processRemainingTime)//compare the priorities
			{
				//sift up the inserted element 
				heap temp = sh->fiveHeaps[priority-1].head[par];
				sh->fiveHeaps[priority-1].head[par] = sh->fiveHeaps[priority-1].head[index];
				sh->fiveHeaps[priority-1].head[index] = temp;
			}
			else
			{
				//sift up the inserted element 
				heap temp = sh->fiveHeaps[priority-1].head[par];
				sh->fiveHeaps[priority-1].head[par] = sh->fiveHeaps[priority-1].head[index];
				sh->fiveHeaps[priority-1].head[index] = temp;
			}
	}
	return sh;
}
