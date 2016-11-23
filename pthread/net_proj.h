#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <term.h>
#include <errno.h>
#include <string.h>
#define ZIGBEE_NODE "./Makefile"

extern pthread_mutex_t mutex_list;//用于串口数据的相关队列

extern pthread_cond_t cond_list;//用于串口数据的相关队列操作线程的唤醒

extern pthread_t thread_uart;//和串口交互的线程号
extern pthread_t thread_fetch;

extern void* recv_from_uart_handler(void* args);
extern void* fetch_from_list_handler(void* args);

