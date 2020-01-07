#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

uint32_t addNode(NODE **root,uint32_t val)
{

	NODE *node=NULL;

#if defined(HEAD_INSERT)
	NODE *temp=NULL;
#endif

	if(*root == NULL)	
	{
		node = malloc(sizeof(NODE));

		if(node == NULL)
		{
			printf("malloc\n");
			return -1;
		}
		else
		{
			node->next=NULL;
			node->val = val;
			*root = node;
		}

		return 1;
	}
	else
	{
		node = malloc(sizeof(NODE));

		if(node == NULL)
		{
			printf("malloc\n");
			return -1;
		}
		else
		{



#if defined(TAIL_INSERT) 
			node->val= val;
			node->next=*root;

			*root =node;
#elif defined(HEAD_INSERT)

			node->val= val;
			if((*root)->next == NULL)
			{
				node->val= val;
				node->next=NULL;

				(*root)->next = node; 
			}
			else
			{
				temp = (*root)->next;

				(*root)->next = node;
				node->next = temp;
			}
#endif









		}
	}

}



uint32_t delNode(NODE **root,uint32_t val)
{

	NODE *cur=*root;
	NODE *pre=NULL;


	while(cur->val != val )
	{
		pre = cur;
		cur= cur->next;
	}

	if(pre == NULL)
	{
		*root = cur->next;
		free(cur);
		return 1;
	}
	else
	{

		pre->next = cur->next;
		free(cur);
		return 1;

	}

	if(cur == NULL)
	{
		printf("not found!\n");
		return 1;

	}


}



uint32_t trv(NODE *root)
{
	NODE *cur=root;
	printf("==================\n");

	if(cur == NULL)
	{
		printf("root is NULL\n");
		return -1;

	}



	while(cur != NULL)
	{
		printf("%d\n",cur->val);

		cur= cur->next;

	}


}


int main(int argc, char*argv[])
{


	NODE *root =NULL;

	addNode(&root,12);
	addNode(&root,14);
	addNode(&root,142);
	//addNode(&root,1882);


	trv(root);
#if 0
	delNode(&root,1882);
	trv(root);

	delNode(&root,14);
	trv(root);

	delNode(&root,142);
	trv(root);



	delNode(&root,12);
	trv(root);
#endif

}


