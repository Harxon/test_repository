#include <string.h>
#include "num.h"
#include "shm.h"
#include "list.h"

info* shmaddr;

//把数据刷到共享内存
int fflush_buf_to_shm(info* msg, char* buf, size_t size){
	
	int snum = 0;

	if(sizeof(char)*UARTDATALEN != size){
		puts("Wrong size of buf or somthing");
		return -1;
	}
	/*接受结构体*/
	uart_msg* buf_msg = malloc(sizeof(*buf_msg));
	if(NULL == buf_msg){
		perror("uart_msg failed");
		return -1;
	}
	memcpy(buf_msg,buf,sizeof(char)*UARTDATALEN);
#if 1
	msg->rt_status.storage_no[snum].storage_status = buf_msg->snum - 48;
#endif
	//判断刷新类型
	//刷新环境信息
	if('e' == buf_msg->type){
		puts("fflush env info...");
		msg->rt_status.storage_no[snum].temperature = (buf_msg->temp[1] - 48)/256;
		msg->rt_status.storage_no[snum].temperature += buf_msg->temp[0] - 48;

		msg->rt_status.storage_no[snum].humidity = (buf_msg->hum[1] - 48)/256;
		msg->rt_status.storage_no[snum].humidity += buf_msg->hum[0] - 48;

		msg->rt_status.storage_no[snum].illumination = buf_msg->lux;

		msg->rt_status.storage_no[snum].x = buf_msg->x - 48;
		msg->rt_status.storage_no[snum].y = buf_msg->y - 48;
		msg->rt_status.storage_no[snum].z = buf_msg->z - 48;

		msg->rt_status.storage_no[snum].battery = buf_msg->bat;
		msg->rt_status.storage_no[snum].adc = buf_msg->adc;
	}else if('r' == buf_msg->type){
		puts("fflush goods info ...");
	}else{
		puts("wrong format data...");
	}
	
	free(buf_msg);

	return 0;
}

void printf_info_msg(info* msg){

	int i = 0,j = 0;
	
	puts("################");
	for(i=0;i<STORAGE_NUM;i++)
	{
		puts("-------------------");
		printf("storage[%d]>>",i);
		printf("storage_status:%d\n",msg->rt_status.storage_no[i].storage_status);
		printf("x:%c, y:%c, z:%c\n",msg->rt_status.storage_no[i].x,msg->rt_status.storage_no[i].y,msg->rt_status.storage_no[i].z);
		printf("Temp:%f, Tmax:%f, Tmmin:%f\n",\
				msg->rt_status.storage_no[i].temperature,\
				msg->rt_status.storage_no[i].temperatureMIN,\
				msg->rt_status.storage_no[i].temperatureMAX);

		printf("Humi:%f, hmax:%f, hmin:%f\n",\
				msg->rt_status.storage_no[i].humidity,\
				msg->rt_status.storage_no[i].humidityMIN,\
				msg->rt_status.storage_no[i].humidityMAX);

		printf("Illu:%f, Imax:%f, Imin:%f\n",\
				msg->rt_status.storage_no[i].illumination,\
				msg->rt_status.storage_no[i].illuminationMIN,\
				msg->rt_status.storage_no[i].illuminationMAX);
		printf("battery:%f\n",msg->rt_status.storage_no[i].battery);
		printf("adc:%f, adcMIN:%f\n",msg->rt_status.storage_no[i].adc,msg->rt_status.storage_no[i].adcMIN);

		for(j=0;j<GOODS_NUM;j++){
			printf("goods_info[%d]>>\n",j);
			printf("goods_type:%c\n",msg->rt_status.storage_no[i].goods_info[j].goods_type);
			printf("goods_count:%d\n",msg->rt_status.storage_no[i].goods_info[j].goods_count);
		}
		puts("-------------------");
	}
		puts("################");
}
