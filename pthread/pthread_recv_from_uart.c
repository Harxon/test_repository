#include "net_proj.h"

void serial_init(int fd)
{
	struct termios options;
	tcgetattr(fd, &options);
	options.c_cflag |= ( CLOCAL | CREAD );
	options.c_cflag &= ~CSIZE;
	options.c_cflag &= ~CRTSCTS;
	options.c_cflag |= CS8;
	options.c_cflag &= ~CSTOPB; 
	options.c_iflag |= IGNPAR;
	options.c_iflag &= ~(ICRNL | IXON);
	options.c_oflag = 0;
	options.c_lflag = 0;

	cfsetispeed(&options, B115200);
	cfsetospeed(&options, B115200);
	tcsetattr(fd,TCSANOW,&options);
}
void* recv_from_uart_handler(void* args){
	int fd = -1;

	if((fd = open(ZIGBEE_NODE,O_RDWR)) < 0){
		printf("fd:%d, open %s failed:%s\n",fd,ZIGBEE_NODE,strerror(errno));
		return NULL;
	}
	serial_init(fd);
	while(1){
		pthread_mutex_lock(&mutex_list);
		printf("recv_from_uart_handler done\n");
		sleep(1);
		pthread_mutex_unlock(&mutex_list);
		/*
		 *串口数据已经缓存到数据链表中
		 * 唤醒处理数据队列中数据的线程
		 * */
		pthread_cond_signal(&cond_list);
		//大部分时间能唤醒对应的线程,但留一个时间间隔，避免对应线程锁的抢占失败。也可以不延时.
		sleep(1);
	}

	pthread_exit(NULL);
} 
