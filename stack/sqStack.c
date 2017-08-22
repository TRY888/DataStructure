#include <stdio.h> 
#include "sqStack.h"


void initStack(SqStack *pStack)
{
	pStack->top = 0;	
}

int stackPush(SqStack *pStack, DataType x)
{
	if((pStack->top+1) > maxLen){
		printf("sqStack over flow\n");
 		return 0;
	}
	pStack->data[pStack->top] = x;
	pStack->top++;
	return 1;
}

int stackPop(SqStack *pStack, DataType *x)
{
	if((pStack->top-1) < 0){
 		printf("sqStack empty\n");
		return 0;
	}
	pStack->top--;
	*x = pStack->data[pStack->top];
	return 1;
}

void testStack()
{
	printf("-----Stack test-----\n");
	SqStack stack;
	initStack(&stack);
	int choose = 1;
	DataType input;
	DataType output;
	
	while(choose)
	{
		printf("1-push\n2-pop\n0-exit\n");
		scanf("%d", &choose);
		switch(choose)
		{
			case 1:printf("input number\n");
			       scanf("%d", &input);
			       if(stackPush(&stack, input)){
			       		printf("-----push number:%d-----\n", input);
       			   }
				   break;
			case 2:if(stackPop(&stack, &output)){
				        printf("-----pop number:%d-----\n", output);
			       }
			       break;
   			default:break;
		} 
	} 
}
