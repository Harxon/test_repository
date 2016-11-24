//#include <stdio.h>
#include <string.h>
#include "num.h"
#include "list.h"

int list_cnt;
linklistp hp,tp;
/*
 *创建一个接受uart数据的链表队列的队列头
 * */
linklistp create_list_head(linklistp* tailp){

	linklistp p = NULL;
	if(NULL == (p = malloc(sizeof(*p)))){
		perror("Malloc linklist mem failed");
		return NULL;
	}else{
		list_cnt = 0;

		bzero(p->data,sizeof(char)*UARTDATALEN);
		p->next = NULL;
		//通过二级指针传递尾指针的值
		*tailp = p;
		puts("create_list_head ok");
	}
	return p;
}
/*向链表队列中添加数据，因为想要达到先进先出的效果，所以要从尾部添加数据*/
int write_to_list_tail(linklistp* tailp,char* s){
		linklistp p = malloc(sizeof(*p));
		if(NULL == p){
			perror("malloc a new node failed");
			return -1;
		}


		(*tailp)->next = p;
		bzero(p->data,sizeof(char)*UARTDATALEN);
		memcpy(p->data,s,sizeof(char)*UARTDATALEN);
		p->next = NULL;
		//通过二级指针改变尾指针的值
		*tailp = p;

		list_cnt ++;
		printf("write_to_list_tail list_cnt:%d\n",list_cnt);
		return 0;
}
/*从队列中取出数据*/
int read_from_list_head(linklistp hp,linklistp* tp,char* buf){

	linklistp p = hp->next;
	//判断是否有数据
	if((hp == *tp) || (NULL == p)){
		puts("The list is empty");
		return -1;
	}else{

		//先从列表中取出紧挨表头的节点
		hp->next = p->next;
		//判断是否是最后一个数据,处理好尾指针位置
		if(NULL == p->next){
			printf("last one has bee read\n");
			*tp = hp;
		}
		//从节点中取出数据
		bzero(buf,sizeof(char)*UARTDATALEN);
		memcpy(buf,p->data,sizeof(char)*UARTDATALEN);
		//删除取出数据的链表节点，初始化指针，防止内存资源浪费和信息泄漏
		p->next = NULL;
		free(p);
		p = NULL;

		list_cnt--;
		printf("read_to_list_tail list_cnt:%d\n",list_cnt);
		return 0;
	}

	return 0;
}
/*打印整个链表的数据*/
int printf_list_long(linklistp hp){
	linklistp p = hp->next;
	puts("#############");
	while(NULL != p){
		printf("%p->data:%s\n",p,p->data);
		p = p->next;
	}
	puts("#############");
	return 0;
}
/*
 *打印uart环境的信息
 * */
void printf_envmsg(char* recv_buf){
//	char temp_buf[UARTDATALEN] = {0};
	uart_msg* msg = NULL;
	if(NULL == (msg = malloc(sizeof(*msg)))){
		perror("EnvMsg malloc failed");
		return;
	}
	printf("recv_buf:%s\n",recv_buf);
	bzero(msg,sizeof(*msg));
	memcpy(msg,recv_buf,sizeof(char)*UARTDATALEN);
//	memcpy(temp_buf,msg,sizeof(char)*UARTDATALEN);
//	printf("temp_buf:%s\n",temp_buf);
	puts("recv_buf's detiles");
	printf("head[3]:%c%c%c\n",msg->head[0],msg->head[1],msg->head[2]);	//标识位st:
	printf("type:%c\n",msg->type);//数据类型
	printf("snum:%c\n",msg->snum);		//仓库编号
	printf("temp:%c%c\n",msg->temp[0],msg->temp[1]);	//温度
	printf("hum:%c%c\n",msg->hum[0],msg->hum[1]);	//湿度
	printf("x:%c\n",msg->x);		//三轴信息
	printf("y:%c\n",msg->y);		
	printf("z:%c\n",msg->z);		
	printf("lux:%d\n",msg->lux);		//光照
	printf("bat:%d\n",msg->bat);		//电池电量
	printf("adc:%d\n",msg->adc);		//电位器信息

	free(msg);
}

uart_msg* transfer_buf_to_msg(char* recv_buf){
	uart_msg* msg = NULL;
	if(NULL == (msg = malloc(sizeof(*msg)))){
		perror("EnvMsg malloc failed");
		return NULL;
	}
	bzero(msg,sizeof(*msg));
	memcpy(msg,recv_buf,sizeof(char)*UARTDATALEN);
	return msg;
}

int transfer_msg_to_buf(char* buf){
	uart_msg* msg = malloc(sizeof(*msg));
	if(NULL == msg){
		perror("malloc msg fiald in transfer_msg_to_buf");
		printf("%s, %s, %d\n",__FILE__,__FUNCTION__,__LINE__);
		return -1;
	}
	memcpy(msg->head,"st:e",4);
	msg->snum = '2';
	memcpy(msg->temp,"24",2);
	memcpy(msg->hum,"12",2);

	msg->x = '1';
	msg->y = '1';
	msg->z = '1';

	msg->lux = 250;
	msg->bat = 5;
	msg->adc = 5;

	memcpy(buf,msg,sizeof(char)*UARTDATALEN);
	
	free(msg);
	msg = NULL;

	return 0;
}
