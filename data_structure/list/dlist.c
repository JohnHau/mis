#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
	struct node *next;
	struct node *prev;
	int key;

}NODE;


NODE dlist;//dlist is NODE struct using only next and prev pointers

int insert2end(NODE *list,int key)
{

	NODE *p, *q;
	//printf("insert2end: key=%d\n",key);
	p = (NODE*)malloc(sizeof(NODE));
	p->key = key;
	p->prev = 0;

	q= list->prev;//to last element

	p->next =  q->next;
	q->next->prev = p;

	q->next = p;
	p->prev = q;



}



int insert2front(NODE*list,int key)
{

	NODE *p,*q;
	//printf("insert2front key = %d\n",key);

	p = (NODE*)malloc(sizeof(NODE));

	p->key = key;
	p->prev =0;

	q = list->next;
	p->prev = q->prev;
	q->prev->next = p;
	q->prev = p;
	p->next = q;

}


void printForward(NODE*list)
{

	NODE *p =list->next;
	printf("list forward =");

	while(p != list) // detect end of list
	{
		printf("[%d]->",p->key);
		p = p->next;

	}

	printf("NULL\n");


}




void printBackward(NODE*list)
{

	NODE *p =list->prev;
	printf("list backward =");

	while(p != list) // detect end of list
	{
		printf("[%d]->",p->key);
		p = p->prev;

	}

	printf("NULL\n");


}




NODE*search(NODE*list,int key)
{

	NODE *p =list->next;
	printf("list backward =");

	while(p != list) // detect end of list
	{
		if(p->key == key)
		{
			printf("found %d at %x\n",key,(unsigned int)p);
			return p;

		}
		p = p->next;

	}

	return 0;

}



int delete(NODE*list, NODE *p)
{
	p->prev->next = p->next;
	p->next->prev = p->prev;
	free(p);
}




int main(int argc, char*argv[])
{

	int i,key;
	NODE*p;

	printf("dlist program #3\n");

	printf("insert to END");

	dlist.next = dlist.prev = &dlist;//empty dlist


	for(i=0;i<8;i++)
	{
		insert2end(&dlist,i);
	}

	printForward(&dlist);
	printBackward(&dlist);

	printf("insert to frong");

	dlist.next = dlist.prev = &dlist;//empty dlist


	for(i=0;i<8;i++)
	{
		insert2front(&dlist,i);
	}

	printForward(&dlist);
	printBackward(&dlist);



	printf("do deletion\n");

	while(1)
	{

		printf("enter key to delete: ");

		scanf("%d",&key);


		if(key < 0)
			exit(0);//exit if key negative


		p = search(&dlist,key);

		if(p == 0)
		{

			printf("key %d not found\n",key);
			continue;

		}

		delete(&dlist,p);
		printForward(&dlist);
		printBackward(&dlist);
	}









}








