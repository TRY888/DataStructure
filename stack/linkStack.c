#include <stdio.h>

typedef int DataType;

typedef struct linkStack{
	DataType data;
	struct linkStack *next; 
}LinkStack;

void initLinkStack(LinkStack **pStack)
{
	*pStack = NULL; 
}

int pushLinkStack(LinkStack **pStack, DataType x)
{
	LinkStack *p = malloc(sizeof(LinkStack));
	if(p == NULL){
		printf("malloc failed\n");
		return 0;
	}
	p->data = x;
	p->next = *pStack;
	*pStack = p;
	return 1;
}

int popLinkStack(LinkStack **pStack, DataType *x)
{
	LinkStack *p = *pStack;
	if(*pStack  == NULL){
		printf("LinkStack empty\n");
		return 0;
	} 
	*x = (*pStack)->data;
	*pStack = (*pStack)->next;
	free(p);
	return 1;
}

void testLinkStack()
{
	printf("-----LinkStack test-----\n");
	LinkStack *stack;
	initLinkStack(&stack);
	int choose; 
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
			       if(pushLinkStack(&stack, input)){
			       		printf("-----push number:%d-----\n", input);
       			   }
				   break;
			case 2:if(popLinkStack(&stack, &output)){
				        printf("-----pop number:%d-----\n", output);
			       }
			       break;
   			default:break;
		} 	
	}
	
}

