#ifndef __SHM_H__
#define __SHM_H__

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define GOODS_NUM  1
#define STORAGE_NUM 1

typedef struct STORAGE_GOODS_INFO
{
	unsigned char goods_type;
	unsigned int goods_count;
}storage_goods_info;

typedef struct STORAGE_INFO
{
	unsigned char storage_status;				// 0:open 1:close
	unsigned char led_status;
	unsigned char buzzer_status;
	unsigned char fan_status;
	unsigned char seg_status;
	signed char x;
	signed char y;
	signed char z;
	float temperature;
	float temperatureMIN;
	float temperatureMAX;
	float humidity;
	float humidityMIN;
	float humidityMAX;
	float illumination;
	float illuminationMIN;
	float illuminationMAX;
	float battery;
	float adc;
	float adcMIN;
	storage_goods_info goods_info[GOODS_NUM];
}storage_info;

typedef struct _env_info_clien_addr
{
	storage_info storage_no[STORAGE_NUM];	
}env_info_clien_addr;


// 共享内存结构体
typedef struct _SHM_ADDR
{
	char cgi_status;
	char qt_status;
	env_info_clien_addr rt_status;
}info;

extern info* shmaddr;//映射内存地址到进程空间地址的起始地址
extern void printf_info_msg(info* msg);
extern int fflush_buf_to_shm(info* msg, char* buf, size_t size);

#endif
