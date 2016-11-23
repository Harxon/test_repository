#include <pthread.h>
#include <sys/types.h>

pthread_t thread_uart;
pthread_t thread_fetch;

pthread_mutex_t mutex_list;
pthread_mutex_t mutex_uart;

pthread_cond_t cond_list;

key_t key_shm;
int shmid;
int semid;
