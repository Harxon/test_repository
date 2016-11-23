#include "net_proj.h"

void* fetch_from_list_handler(void* args){
	/*
	 * 被处理串口数据的线程唤醒后，
	 * 循环从串口数据队列中取出数据，
	 * 取完后刷新到共享内存中
	 */
	while(1){
		pthread_mutex_lock(&mutex_list);
		pthread_cond_wait(&cond_list,&mutex_list);
		printf("fetch_from_list_handler done\n");
		pthread_mutex_unlock(&mutex_list);
	}

	pthread_exit(NULL);
} 
