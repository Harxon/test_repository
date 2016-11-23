#include "num.h"
#include "shm.h"

info* shmaddr;

//把数据刷到共享内存
int fflush_buf_to_shm(info* shmaddr, char* buf, size_t size){

	if(sizeof(char)*UARTDATALEN != size){
		puts("Wrong size of buf or somthing");
		return -1;
	}
	//仓库编号
	unsigned char snum = 0;
	//数据类型
	unsigned char type = '0';
	type = buf[3];
	snum = buf[4];
	//判断刷新类型
	//刷新环境信息
	if('e' == type){
		puts("fflush env info...");
		shmaddr->storage_no[snum].temperature = buf[6]/256;
		shmaddr->storage_no[snum].temperature += buf[5];

		shmaddr->storage_no[snum].humidity = buf[8];
		shmaddr->storage_no[snum].humidity = buf[7] + shmaddr->storage_no[snum].humidity/256;

		shmaddr->storage_no[snum].illumination = buf[12];

		shmaddr->storage_no[snum].x = buf[9];
		shmaddr->storage_no[snum].y = buf[10];
		shmaddr->storage_no[snum].z = buf[11];

		shmaddr->storage_no[snum].battery = buf[13];
		shmaddr->storage_no[snum].adc = buf[14];
	}else if('r' == type){
		puts("fflush goods info ...");
	}else{
		puts("wrong format data...");
	}

	return 0;
}
