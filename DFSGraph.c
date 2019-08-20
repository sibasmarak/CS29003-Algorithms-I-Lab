#include <stdio.h>
#include <stdlib.h>

int main()
{
	int ad[6][6] = {
		1,1,1,0,1,0,
		0,1,0,1,0,1,
		0,0,1,1,1,0,
		0,0,0,1,1,1,
		0,1,0,1,1,0,
		0,0,0,0,0,1
			};
		int in[6], out[6], stack[6],n, j=-1,k=0,i,l=0,m,flag = 0;
		scanf("%d", &n);
		in[l] = n;l++;//l for input, k for output, j for stack
		stack[++j] = n;
		while(j>=0)			//While stack not empty
		{
			out[k] = stack[j--];
			n=out[k];
			k++;
			for(i=0;i<6;i++)
			{
				if(ad[n][i]==1)
				{
					for(m=0;m<l;m++)
					{
						if(in[m] == i)
						{
							flag = 1;
							break;
						}
					}
					if(flag == 0)
					{
						stack[++j] = i;
						in[l++] = i;
					}
				}
				flag = 0;
			}
		} 
		for(i=0;i<k;i++)
		{
			printf("%c", out[i]+65);
		}
	return 0;
}