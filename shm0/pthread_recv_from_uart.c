#include "num.h"
#include "net_proj.h"
#include "list.h"

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
	//接受串口数据的数组
	char recv_buf[UARTDATALEN];

	if((fd = open(ZIGBEE_NODE,O_RDWR)) < 0){
		printf("fd:%d, open %s failed:%s\n",fd,ZIGBEE_NODE,strerror(errno));
		return NULL;
	}

	serial_init(fd);

	if(NULL == (hp = create_list_head(&tp))){
		perror("create_list_head failed");
		return NULL;
	}
	while(1){
		pthread_mutex_lock(&mutex_list);

		read(fd,recv_buf,sizeof(char)*UARTDATALEN);

		printf_envmsg(recv_buf);

		if(!write_to_list_tail(&tp,recv_buf)){
			perror("write_to_list_tail failed");
			break;
		}
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
