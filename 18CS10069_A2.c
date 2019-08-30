#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10
typedef struct Stack
{
	char opr;
}Stack;
Stack*  createStack(int length_of_given_expression);
int isEmpty(Stack* stack);
char peek(Stack* stack, int length);
char pop(Stack* stack, int length);
void push(Stack* stack, char op, int length);

int main()
{
	/*FILE* in = fopen("input.txt","r");
	if(in==NULL)
	{
		printf("FILE DOESNOT EXISTS\n");
		return 0;
	}
	char expr[SIZE],x;
	int line=1,i,j;
	while((x=getc(in))!=EOF)
	{
		if(x == '\n')
			line++;
	}						//I obtained number of line, so the next loop would run line number of times, to scan the exprs;
	rewind(in);				//extremely important now the file pointer is at EOF!
	for(i=0;i<line;i++)
	{
		fscanf(in,"%s",&expr);		//I obtained the first expression
		Stack* stack = createStack(strlen(expr));
		convert(stack,expr);
	}*/
	int x = 56;
	char c = (int)x;
	printf("%c\n", c);
	return 0;
}
void convert(Stack* stack, char* expr)
{
	int stackTop = -1, length = strlen(expr),i=0;
	FILE* out = fopen("part1_output.txt","w");
	while(i<length)
	{
		printf("HI\n");
		if(isOperand(&expr[i])==1)		//if expr[i] is operand
			fprintf(out,"%c",expr[i]);

		else if(expr[i] == '(')	//if expr[i] is left parentheses
		{
			push(stack, expr[i],length);
			stackTop++;
		}

		else if(expr[i] == ')')	//if expr[i] is right parentheses
		{
			int j=stackTop;
			while(stackTop!=-1 && expr[j]!='(')
			{
				fprintf(out, "%c", pop(expr[j],stackTop));
				stackTop--;
				j--;
			}
		}

		else
		{
			int a = expr[i++];
			while(i<length && isOperand(&expr[i])!=1)
				a = a*10 + expr[i++];
			i--;
			push(stack, a, length);
		}
		i++;
	}
	while(stackTop!=-1)
	{
		fprintf(out, "%c", pop(stack,stackTop));
		stackTop--;
	}
	fprintf(out, "\n");
	return;
}
int isOperand(char* opd)
{
	if(*opd == '+' ||*opd == '*' ||*opd == '-' ||*opd == '/' ||*opd == '%')
		return 1;
	else 
		return 0;
}
Stack*  createStack(int length_of_given_expression)
{
	int i;
	Stack* stack = (Stack*)malloc(length_of_given_expression*sizeof(Stack));
	return stack;
}
int isEmpty(Stack* stack)
{
	return (stack==NULL)?1:0;
}
char peek(Stack* stack, int length)
{
	int i=0,j=0;
	while(j!=length && stack[i].opr!=0)
	{
		j=i;
		i++;
	}
	return stack[j].opr;
}
char pop(Stack* stack, int stackTop)
{
	char retChar = stack[stackTop].opr;
	stack[stackTop].opr = 0;
	return retChar;
}
void push(Stack* stack, char op, int length)
{
	int i=0,j=0;
	while(j!=length && stack[i].opr!=0)
	{
		j=i;
		i++;
	}
	if(j==length)
	{
		printf("STACK IS FULL< NO MORE SPACE\n");
		return;
	}
	stack[i].opr = op;
	return;
}
