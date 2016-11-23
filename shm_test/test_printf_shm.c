#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/user.h>
#include "num.h"
#include "net_proj.h"
#include "shm.h"

void printf_env_info_clien_addr(info* msg){

	int i = 0,j = 0;

	for(i=0;i<STORAGE_NUM;i++)
	{
		puts("################");
		printf("storage[%d]>>",i);
		printf("storage_status:%d\n",msg->storage_no[i].storage_status);
		printf("x:%c, y:%c, z:%c\n",msg->storage_no[i].x,msg->storage_no[i].y,msg->storage_no[i].z);
		printf("Temp:%f, Tmax:%f, Tmmin:%f\n",\
				msg->storage_no[i].temperature,\
				msg->storage_no[i].temperatureMIN,\
				msg->storage_no[i].temperatureMAX);

		printf("Humi:%f, hmax:%f, hmin:%f\n",\
				msg->storage_no[i].humidity,\
				msg->storage_no[i].humidityMIN,\
				msg->storage_no[i].humidityMAX);

		printf("Illu:%f, Imax:%f, Imin:%f\n",\
				msg->storage_no[i].illumination,\
				msg->storage_no[i].illuminationMIN,\
				msg->storage_no[i].illuminationMAX);
		printf("battery:%f\n",msg->storage_no[i].battery);
		printf("adc:%f, adcMIN:%f\n",msg->storage_no[i].adc,msg->storage_no[i].adcMIN);

		for(j=0;j<GOODS_NUM;j++){
			printf("goods_info[%d]>>\n",j);
			printf("goods_type:%c\n",msg->storage_no[i].goods_info[j].goods_type);
			printf("goods_count:%d\n",msg->storage_no[i].goods_info[j].goods_count);
		}
		puts("################");
	}
}

int main(int argc, const char *argv[])
{
	struct env_info_clien_addr* shmaddr;
	//ftok获取
	key_shm = ftok(SHM_PATHNAME, 's');
	//shmget
	printf("env_info_clien_addr size :%d\n",sizeof(struct env_info_clien_addr));
	printf("shmget sizeall: %ld\n",SIZE_SHM*PAGE_SIZE);

	if((shmid = shmget(key_shm,SIZE_SHM,IPC_CREAT | IPC_EXCL|0666)) < 0){
		if(EEXIST == errno){
			if((shmid = shmget(key_shm,SIZE_SHM,0666)) < 0){
				perror("shmget error");
				return -1;
			}
		}else{
			perror("shmget failed");
			return -1;
		}
	}
	printf("shmid:%d\n",shmid);
	//shmat
    if((void*)-1 == (shmaddr = (struct env_info_clien_addr*)shmat(shmid, NULL, 0))){
		perror("shmaddr failed");
		return -1;
	}
	while(1){
		printf_env_info_clien_addr(shmaddr);
		sleep(1);
	}
	return 0;
}
