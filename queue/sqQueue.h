#ifndef _SQQUEUE_H
#define _SQQUEUE_H

#include "include.h"
#define MAXLEN 10

typedef struct Snode{
	DataType data[MAXLEN];
	int head;
	int tail;
}SqQueue;

void testSqQueue();
void initSqQueue(SqQueue *queue);
int pushSqQueue(SqQueue *queue, DataType x);
int popSqQueue(SqQueue *queue, DataType *x);

#endif

