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
	char recv_buf[UARTDATALEN] = {0};
#if 0
	if((fd = open(ZIGBEE_NODE,O_RDWR)) < 0){
		printf("fd:%d, open %s failed:%s\n",fd,ZIGBEE_NODE,strerror(errno));
		return NULL;
	}

	serial_init(fd);
#endif 
	if(NULL == (hp = create_list_head(&tp))){
		perror("create_list_head failed");
		return NULL;
	}
	while(1){
		pthread_mutex_lock(&mutex_uart);
		//read(fd,recv_buf,sizeof(char)*UARTDATALEN);
	//	sprintf(recv_buf,"st:%c%c0000000",'e',i++);
		transfer_msg_to_buf(recv_buf);


		printf_envmsg(recv_buf);
	
		pthread_mutex_lock(&mutex_list);
		if(!write_to_list_tail(&tp,recv_buf)){
			perror("write_to_list_tail failed");
			break;
		}
		printf_list_long(hp);
		pthread_mutex_unlock(&mutex_list);

		printf("tp:%p, hp:%p\n",tp,hp);
		pthread_mutex_unlock(&mutex_uart);
		/*
		 *串口数据已经缓存到数据链表中
		 * 唤醒处理数据队列中数据的线程
		 * */
		if(pthread_cond_signal(&cond_list)){
			perror("pthread_cond_signal failed");
		}
#if 1
		//大部分时间能唤醒对应的线程,但留一个时间间隔，避免对应线程锁的抢占失败。也可以不延时.
		sleep(1);
#endif
	}

	pthread_exit(NULL);
} 
