#ifndef _SQSTACK_H
#define _SQSTACK_H

#include "include.h"

#define maxLen 10

typedef struct sqStack{
	DataType data[maxLen];
	int top;
}SqStack;

void testStack();
int stackPush(SqStack *pStack, DataType x);
int stackPop(SqStack *pStack, DataType *x);

#endif
