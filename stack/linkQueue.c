#include <stdio.h>
#include "linkQueue.h"


void initLinkQueue(LinkQueue *queue, LinkQueue **head, LinkQueue **tail)
{
	queue->next = NULL;
	*head = *tail = queue;	
}

int pushLinkQueue(LinkQueue **tail, DataType x)
{
	LinkQueue *p = malloc(sizeof(LinkQueue));
	if(p == NULL){
		printf("LinkQueue malloc fail\n");
		return 0;
	}
	p->data= x;
	p->next = NULL;
	(*tail)->next = p;
	*tail = p;
	return 1;
}

int popLinkQueue(LinkQueue **head, LinkQueue **tail, DataType *x)
{
	LinkQueue *p;
	if(*head == *tail){
		printf("LinkQueue is empty\n");
		return 0;
	}
	if((*head)->next == (*tail)){
		*x = (*head)->next->data;
		p = (*head)->next;
		free(p);
		(*head)->next = NULL;
		*tail = *head;
		return 1;
	}
	p = (*head)->next;
	*x = p->data;
	(*head)->next = p->next;
	free(p);
	return 1;
}

void printLinkQueue(LinkQueue *queue)
{
	LinkQueue *p = queue;
	while(p->next != NULL)
	{
		printf("%d ", p->next->data);
		p = p->next;
	}	
}
void testLinkQueue()
{
	printf("-----LinkQueue test-----\n");
	LinkQueue queue;
	LinkQueue *head, *tail;
	initLinkQueue(&queue, &head, &tail);
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
			       if(pushLinkQueue(&tail, input)){
			       		printf("-----push number:%d-----\n", input);
			       		printf("---------------------\n");
			       		printLinkQueue(&queue);
			       		printf("\n---------------------\n");
       			   }
				   break;
			case 2:if(popLinkQueue(&head, &tail, &output)){
				        printf("-----pop number:%d-----\n", output);
				        printf("---------------------\n");
			       		printLinkQueue(&queue);
			       		printf("\n---------------------\n");
			       }
			       break;
   			default:break;
		} 	
	}
	
}















