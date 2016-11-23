#include "num.h"
#include "list.h"

linklistp hp,tp;

void printf_envmsg(char* recv_buf){

	uart_msg* msg = NULL;
	if(NULL == (msg = malloc(sizeof(*msg)))){
		perror("EnvMsg malloc failed");
		return;
	}
	bzero(msg,sizeof(*msg));
	memcpy(msg,recv_buf,sizeof(char)*UARTDATALEN);

	printf("head[3]:%c%c%c\n",msg->head[0],msg->head[1],msg->head[2]);	//标识位st:
	printf("type:%c\n",msg->type);//数据类型
	printf("snum:%d\n",msg->snum);		//仓库编号
	printf("temp:%d%d\n",msg->temp[0],msg->temp[1]);	//温度
	printf("hum:%d%d\n",msg->hum[0],msg->hum[1]);	//湿度
	printf("x:%d\n",msg->x);		//三轴信息
	printf("y:%d\n",msg->y);		
	printf("z:%d\n",msg->z);		
	printf("lux:%d\n",msg->lux);		//光照
	printf("bet:%d\n",msg->bet);		//电池电量
	printf("adc:%d\n",msg->adc);		//电位器信息

	free(msg);
}
/*
 *创建一个接受uart数据的链表队列的队列头
 * */
linklistp create_list_head(linklistp* tailp){

	linklistp p = NULL;
	if(NULL == (p = malloc(sizeof(*p)))){
		perror("Malloc linklist mem failed");
		return NULL;
	}else{
		bzero(p->data,sizeof(char)*UARTDATALEN);
		p->next = NULL;
		//通过二级指针传递尾指针的值
		*tailp = p;
		puts("create_list_head ok");
	}
	return p;
}
/*向链表队列中添加数据，因为想要达到先进先出的效果，所以要从尾部添加数据*/
bool write_to_list_tail(linklistp* tailp,char* s){
		linklistp p = malloc(sizeof(*p));
		if(NULL == p){
			perror("malloc a new node failed");
			return false;
		}
		(*tailp)->next = p;
		bzero(p->data,sizeof(char)*UARTDATALEN);
		memcpy(p->data,s,sizeof(char)*UARTDATALEN);
		p->next = NULL;
		//通过二级指针改变尾指针的值
		*tailp = p;
		return true;
}
/*从队列中取出数据*/
bool read_from_list_head(linklistp hp,linklistp tailp,char* buf){

	linklistp p = hp->next;
	//判断是否有数据
	if(NULL == p){
		puts("The list is empty");
		return false;
	}else{
		//先从列表中取出紧挨表头的节点
		hp->next = p->next;
		//从节点中取出数据
		bzero(buf,sizeof(char)*UARTDATALEN);
		memcpy(buf,p->data,sizeof(char)*UARTDATALEN);
		//删除取出数据的链表节点，初始化指针，防止内存资源浪费和信息泄漏
		p->next = NULL;
		free(p);
	}
	return true;
}
