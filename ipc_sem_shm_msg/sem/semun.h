#ifndef _SEMUN_H
#define _SEMUN_H


union semun
{

	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct seminfo *__buf;

};


#endif
