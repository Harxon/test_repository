#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/user.h>
#include <signal.h>
#include "num.h"
#include "net_proj.h"
#include "list.h"
#include "shm.h"

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

	unsigned char i= 0;
	char recv_buf[UARTDATALEN] = {0};

	/*
	 * 被处理串口数据的线程唤醒后，
	 * 循环从串口数据队列中取出数据，
	 * 取完后刷新到共享内存中
	 */
	//创建共享内存
	//ftok获取
	key_shm = ftok(SHM_PATHNAME, 's');
	//shmget
	printf("env_info_clien_addr size :%d\n",sizeof(struct env_info_clien_addr));
	printf("shmget sizeall: %ld\n",SIZE_SHM*PAGE_SIZE);

	if((shmid = shmget(key_shm,SIZE_SHM,IPC_CREAT | IPC_EXCL|0666)) < 0){
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
    if((void*)-1 == (shmaddr = (struct env_info_clien_addr*)shmat(shmid, NULL, 0))){
		perror("shmaddr failed");
	}

	//键盘中断信号的处理
	if(signal(SIGINT,ifk_handler) == SIG_ERR){
		perror("SIGINT handle failed");
	}

	while(1){
		pthread_mutex_lock(&mutex_list);
		pthread_cond_wait(&cond_list,&mutex_list);
		read_from_list_head(hp,tp,recv_buf);
		printf("fetch_from_list_handler done\n");
		printf("fflush to shm...\n");
		fflush_buf_to_shm(shmaddr,recv_buf,sizeof(char)*UARTDATALEN);
		puts("fflush done");
		pthread_mutex_unlock(&mutex_list);
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
	//
	pthread_exit(NULL);
} 
