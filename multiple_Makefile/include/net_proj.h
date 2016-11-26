#ifndef __NET_PROJ_H__
#define __NET_PROJ_H__

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>


extern pthread_mutex_t mutex_list;//用于串口数据的相关队列
extern pthread_mutex_t mutex_uart;//用于串口的使用上

extern pthread_cond_t cond_list;//用于串口数据的相关队列操作线程的唤醒
 
extern pthread_t thread_uart;//和串口交互的线程号
extern pthread_t thread_fetch;

extern key_t key_shm;//用于共享内存的标号
extern int shmid;//用于接受获取的共享内存段的信息ID 
extern int semid;//用于接受获取的信号灯集ID

extern void* recv_from_uart_handler(void* args);
extern void* fetch_from_list_handler(void* args);

#endif
