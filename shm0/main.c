#include "net_proj.h"

int main(int argc, const char *argv[])
{
	int err = 0;
	/*
	 *初始化线程锁
	 * */
	pthread_mutex_init(&mutex_list,NULL);
	/*
	 *初始化条件变量
	 * */
	pthread_cond_init(&cond_list,NULL);
	/*
	 *开启各个功能线程
	 * */
	if((err = pthread_create(&thread_uart,NULL,recv_from_uart_handler,NULL)) < 0){
		perror("pthread_create uart_thread failed");
		return -1;
	}else{
		printf("pthread_create uart_thread ok\n");
	}

	if((err = pthread_create(&thread_fetch,NULL,fetch_from_list_handler,NULL)) < 0){
		perror("pthread_create fetch_thread failed");
		return -1;
	}else{
		printf("pthread_create fetch_thread ok\n");
	}

	/*回收线程*/
	pthread_join(thread_uart,NULL);
	pthread_join(thread_fetch,NULL);

	return 0;
}
