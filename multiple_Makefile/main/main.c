#include "net_proj.h"

int main(int argc, const char *argv[])
{
	int err = 0;
	/*
	 *初始化线程锁
	 * */
	pthread_mutex_init(&mutex_list,NULL);
	pthread_mutex_init(&mutex_uart,NULL);
	/*
	 *初始化条件变量
	 * */
	pthread_cond_init(&cond_list,NULL);
	/*
	 *开启各个功能线程
	 * */
	/*线程1，开启从串口读数据的线程*/
	if((err = pthread_create(&thread_uart,NULL,recv_from_uart_handler,NULL)) < 0){
		perror("pthread_create uart_thread failed");
		return -1;
	}else{
		printf("pthread_create thread_uart ok\n");
	}
	/*线程2，开启从链表中读取环境信息的线程*/
	if((err = pthread_create(&thread_fetch,NULL,fetch_from_list_handler,NULL)) < 0){
		perror("pthread_create thread_fetch failed");
		return -1;
	}else{
		printf("pthread_create thread_fetch ok\n");
	}

	/*回收线程*/
	pthread_join(thread_uart,NULL);
	pthread_join(thread_fetch,NULL);

	return 0;
}
