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
		int f=0,r=0;// front and rear for queue
		int queue[6], in[6], out[6];
		int i,k=0,m,l=0,n,flag=0;
		scanf("%d", &n);
		queue[r++] = n;
		in[l++] = n;
		while(f!=r)
		{
			out[k] = queue[f];
			f++;
			n = out[k++];
			for(i=0;i<6;i++)
			{
				if(ad[n][i] == 1)
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
						queue[r++] = i;
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