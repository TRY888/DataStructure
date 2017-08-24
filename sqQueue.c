#include "sqQueue.h"
#include <stdio.h>

void initSqQueue(SqQueue *queue)
{
	queue->head = 0;
	queue->tail= 0;	
}

int pushSqQueue(SqQueue *queue, DataType x)
{
	if((queue->tail+1) % MAXLEN == queue->head){
		printf("SqQueue is full\n");
		return 0;
	}
	queue->data[queue->tail] = x;
	queue->tail = (queue->tail + 1) % MAXLEN;
	return 1;
}

int popSqQueue(SqQueue *queue, DataType *x)
{
	if(queue->head == queue->tail){
		printf("SqQueue is empty\n");
		return 0;
	}
	*x = queue->data[queue->head];
	queue->head = (queue->head + 1) % MAXLEN;
	return 1;
}

void printSqQueue(SqQueue *queue)
{
	if(queue->head == queue->tail)
		return;
	int head = queue->head;
	int tail = queue->tail;
	while(head != tail)
	{
		printf("%d ",queue->data[head]);
		head = (head + 1) % MAXLEN;
	}
} 

void testSqQueue()
{
	printf("-----SqQueue test-----\n");
	SqQueue queue;
	initSqQueue(&queue);
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
			       if(pushSqQueue(&queue, input)){
			       		printf("-----push number:%d-----\n", input);
			       		printf("---------------------\n");
			       		printSqQueue(&queue);
			       		printf("\n---------------------\n");
       			   }
				   break;
			case 2:if(popSqQueue(&queue, &output)){
				        printf("-----pop number:%d-----\n", output);
				        printf("---------------------\n");
			       		printSqQueue(&queue);
			       		printf("\n---------------------\n");
			       }
			       break;
   			default:break;
		} 	
	}
	
}
