#ifndef _LINKSTACK_H
#define _LINKSTACK_H

#include "include.h"

typedef struct linkStack{
	DataType data;
	struct linkStack *next; 
}LinkStack;

void testLinkStack();
void initLinkStack(LinkStack **pStack);
int pushLinkStack(LinkStack **pStack, DataType x);
int popLinkStack(LinkStack **pStack, DataType *x);
int isLinkStackEmpty(LinkStack **pStack);
int frontLinkStack(LinkStack **pStack, DataType *x);

#endif

