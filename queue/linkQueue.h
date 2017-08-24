#ifndef _LINKQUEUE_H
#define _LINKQUEUE_H

#include "include.h"

typedef struct Lnode{
	DataType data;
	struct Lnode *next;
}LinkQueue;

void initLinkQueue(LinkQueue *queue, LinkQueue **head, LinkQueue **tail);
int pushLinkQueue(LinkQueue **tail, DataType x);
int popLinkQueue(LinkQueue **head, LinkQueue **tail, DataType *x);
void testLinkQueue();

#endif
