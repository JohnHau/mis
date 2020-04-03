#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

typedef struct tnode
{
	uint32_t num;
	struct tnode *next;

}TNODE,*pTNODE;



pTNODE insert_tnode(pTNODE root,uint32_t n)
{

	pTNODE node=(pTNODE)malloc(sizeof(TNODE));


	if(node == NULL)
	{
		perror("malloc failed!\n");
		exit(EXIT_FAILURE);
	}

	node->num = n;

	if(root == NULL)
	{
		node->next = NULL;
		root = node;
	}
	else
	{
		 node->next = root;
		 root = node;
	}


	return root;

}


pTNODE delete_tnode(pTNODE root,uint32_t n)
{
	pTNODE prev = NULL; 
	pTNODE cur = root; 

	pTNODE temp = NULL; 
	while(cur && cur->num != n )
	{
		prev = cur;
		cur = cur->next;

	}



	if(cur == NULL)
	{

		return root;
	}



	if(prev == NULL)
	{
		temp = cur;
		root = root->next;

	}
	else if(cur->next == NULL)
	{
		temp = cur;
		prev->next = NULL;


	}
	else
	{

		temp = cur;

		prev->next = cur->next;

	}

	free(temp);

	return root;

}

uint32_t tllist(pTNODE root)
{

	while(root)
	{

		printf("%d\n",root->num);
		root = root->next;

	}


	return 0;


}



int main(int argc,char* argv[])
{


	pTNODE root = NULL;



	for(int m=0;m<8;m++)
	{

		root = insert_tnode(root,m+1);
	}

	printf("========================\n");
	tllist(root);



	printf("========================\n");
	root = delete_tnode(root,5);
	tllist(root);

	printf("========================\n");
	root = delete_tnode(root,9);
	tllist(root);

	printf("========================\n");
	root = delete_tnode(root,1);
	tllist(root);

	printf("========================\n");
	root = delete_tnode(root,10);
	tllist(root);
	return 0;




}
