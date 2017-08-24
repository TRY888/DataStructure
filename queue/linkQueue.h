#ifndef _LINKQUEUE_H
#define _LINKQUEUE_H

#include "include.h"

typedef struct node{
	DataType data;
	struct node *next;
}LinkQueue;

#endif
