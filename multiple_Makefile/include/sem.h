#ifndef __SEM_H__
#define __SEM_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

extern int init_sem(int semid, int num, int val);
extern int sem_p(int semid, int num);
extern int sem_v(int semid, int num);

#endif
