#include <stdio.h>
#define GOODS_NUM  1
#define STORAGE_NUM 1


struct rfid_info
{
	unsigned char rfid_type;	
	unsigned char goods_no;
	unsigned char goods_count;
};

struct data_all
{
	unsigned char dev_no;
	unsigned char msg_type;
	float temperature;
	float humidity;
	float illumination;
	struct rfid_info goods_info;
	short crc;
};

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
	char samplingTime[20];
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

typedef struct env_info_clien_addr
{
	storage_info storage_no[STORAGE_NUM];	
}info;


extern info* shmaddr;//映射内存地址到进程空间地址的起始地址
extern void printf_info_msg(info* msg);
extern int fflush_buf_to_shm(info* msg, char* buf, size_t size);
