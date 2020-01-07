#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _queue
{
	uint32_t head;
	uint32_t tail;
	uint32_t*  buf;

}Queue;


#define qSize 8
Queue qa;
uint32_t  myBuffer[qSize+1]={0};


int32_t initQueue(Queue *q,uint32_t *buffer)
{
	q->head =0;
	q->tail = q->head;
	q->buf=buffer;

	return 0;

}


int32_t enQueue(Queue*q,uint32_t n)
{
	if((q->tail +1)%(qSize+1) == q->head)
	{
		printf("The queue has been full!\n");
		return -1;

	}

	q->buf[q->tail] = n;
	q->tail = (q->tail +1)%(qSize+1);

	return 0;	

}



int32_t deQueue(Queue*q,uint32_t *val)
{
	if(q->tail == q->head)
	{
		printf("The Queue has been empty\n");
		return -1;
	}

	*val = q->buf[q->head];
	q->head= (q->head +1)%(qSize+1);

	return 0;	

}



int32_t compareArray(uint32_t *sArray,uint32_t *dArray,uint32_t len)
{

	uint32_t i;
	for(i=0;i<len;i++)
	{

		if(sArray[i] != dArray[i])
		{
			return -1;

		}

	}

	return 1;


}


uint32_t enlist[qSize]={0};
uint32_t delist[qSize]={0};

int main(int argc ,char*argv[])
{
	int32_t rv=0;
	int32_t i=0;

	srand(time(NULL));

	uint32_t vlist[16]={0};

	initQueue(&qa,myBuffer);

	for(i=0;i<qSize;i++)
	{
		vlist[i] = rand()%0xffff;
	}


	for(i=0;i<qSize;i++)
	{
		enQueue(&qa,enlist[i]);
	}

	for(i=0;i<qSize;i++)
	{
		deQueue(&qa,&delist[i]);
	}


	if(compareArray(enlist,delist,qSize) ==1)
	{

		printf("success\n");

		return 0;

	}
	else
	{

		printf("error\n");

		return -1;
	}

	return 0;


}