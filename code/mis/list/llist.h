#ifndef __SLIST_H__
#define __SLIST_H__

#define TAIL_INSERT


typedef struct _node
{

uint32_t val;
struct _node *next;	

}NODE;

extern uint32_t addNode(NODE **root,uint32_t val);

extern uint32_t delNode(NODE **root,uint32_t val);


extern uint32_t trv(NODE *root);

#endif
