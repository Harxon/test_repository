#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/user.h>
#include <signal.h>
#include "num.h"
#include "net_proj.h"
#include "list.h"
#include "shm.h"
#include "sem.h"

void ifk_handler(int signum){
	printf("signum:%d\n",signum);
	//shmdt
	if(shmdt(shmaddr)){
		perror("shmdt failed");
	}else{
		puts("shmaddr was unmapped");
	}
	//shmctl
	if(shmctl(shmid,IPC_RMID,NULL)){
		printf("shmctl for %d faild:%s\n",shmid,strerror(errno));
	}else{
		printf("%d of shm was deleted",shmid);
	}

	exit(-1);
	//pthread_exit(NULL);
}

void* fetch_from_list_handler(void* args){

	char recv_buf[UARTDATALEN] = {0};

	/*
	 * 被处理串口数据的线程唤醒后，
	 * 循环从串口数据队列中取出数据，
	 * 取完后刷新到共享内存中
	 */
	//创建共享内存
	//ftok获取
	key_shm = ftok(SHM_PATHNAME, 'i');
	printf("key_shm:%d\n",key_shm);
	//shmget 
	printf("env_info_clien_addr size :%d\n",sizeof(struct _env_info_clien_addr));
	printf("shmget sizeall: %d\n",SIZE_SHM*PAGE_SIZE);

	if((shmid = shmget(key_shm,SIZE_SHM,IPC_CREAT | IPC_EXCL | 0666)) < 0){
		if(EEXIST == errno){
			if((shmid = shmget(key_shm,SIZE_SHM,0666)) < 0){
				perror("shmget error");
				return NULL;
			}
		}else{
			perror("shmget failed");
			return NULL;
		}
	}
	printf("shmid:%d\n",shmid);

	//shmat 
    if((void*)-1 == (shmaddr = (info*)shmat(shmid, NULL, 0))){
		perror("shmaddr failed");
	}

	//键盘中断信号的处理
	if(signal(SIGINT,ifk_handler) == SIG_ERR){
		perror("SIGINT handle failed");
	}

	//semget
	if((semid = semget(key_shm,NUMS_SEM,IPC_CREAT|IPC_EXCL|0666)) < 0){
		if(EEXIST == errno){
			if((semid = semget(key_shm,NUMS_SEM,0666)) < 0){
				perror("semget error");
				return NULL;
			}
		}else{
			perror("semget error");
			return NULL;
		}

	}
	printf("semid:%d\n",semid);
	//init_sem
	init_sem(semid,NUMS_SEM,1);

	while(1){
		pthread_mutex_lock(&mutex_list);
		pthread_cond_wait(&cond_list,&mutex_list);

		if(read_from_list_head(hp,&tp,recv_buf)){
			pthread_mutex_unlock(&mutex_list);
			printf("hp:%p, tp:%p\n",tp,hp);

			sem_p(semid,0);
			fflush_buf_to_shm(shmaddr,recv_buf,sizeof(char)*UARTDATALEN);
			printf_info_msg(shmaddr);
			sem_v(semid,0);

		}else{
			pthread_mutex_unlock(&mutex_list);
			puts("no datas.................");
			printf_list_long(hp);
			printf("hp:%p, tp:%p\n",tp,hp);
		}
	}

	//shmdt
	if(shmdt(shmaddr)){
		perror("shmdt failed");
	}else{
		puts("shmaddr was unmapped");
	}
	//shmctl
	if(shmctl(shmid,IPC_RMID,NULL)){
		printf("shmctl for %d faild:%s\n",shmid,strerror(errno));
	}else{
		printf("%d of shm was deleted",shmid);
	}
	//semctl 
	semctl(semid,NUMS_SEM,IPC_RMID,NULL);
	//
	pthread_exit(NULL);
} 
