#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

/*定义一个链表节点*/
typedef struct _UART_NODE{
	char data[UARTDATALEN];
	struct _UART_NODE* next;
}linknode,*linklistp;

typedef struct ENV_MSG{
	unsigned char head[3];
	unsigned char type;
	unsigned char snum;
	unsigned char temp[2];
	unsigned char hum[2];
	unsigned char x;
	unsigned char y;
	unsigned char z;
	unsigned int lux;
	unsigned int bat;
	unsigned int adc;
}uart_msg;

/*链表长度判断*/
extern int list_cnt;

extern linklistp hp,tp;
/*创建一个接受uart数据的链表队列的队列头*/
extern linklistp create_list_head(linklistp* tailp);
/*向链表队列中添加数据，因为想要达到先进先出的效果，所以要从尾部添加数据*/
extern int write_to_list_tail(linklistp* tailp,char* s);
/*从队列中取出数据*/
extern int read_from_list_head(linklistp hp,linklistp* tailp,char* buf);

extern int printf_list_long(linklistp hp);

extern void printf_envmsg(char* recv_buf);
extern int transfer_msg_to_buf(char* buf);
extern uart_msg* transfer_buf_to_msg(char* recv_buf);

#endif
