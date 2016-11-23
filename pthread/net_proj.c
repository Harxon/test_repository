#include <pthread.h>
pthread_t thread_uart;
pthread_t thread_fetch;

pthread_mutex_t mutex_list;

pthread_cond_t cond_list;
