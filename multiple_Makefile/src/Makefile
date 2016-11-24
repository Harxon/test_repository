#CC := gcc
CC := arm-none-linux-gnueabi-gcc
AFLAGS := -Wall -c -g
LDFLAGS := -lpthread
#应用程序1的名字
APPNAME := storage_mamage
CODES_DIR := src
OBJS_STO_DIR := obj 

#第一个应用程序依赖的.o文件
OBJS := main.o 
OBJS += net_proj.o
OBJS += pthread_recv_from_uart.o 
OBJS += pthread_fetch_from_list.o
OBJS += list.o
OBJS += shm.o
OBJS += sem.o

all:$(OBJS)

#自动化变量'$<'表示搜索到的第一个依赖文件，'$@'为目标文件
$(OBJS):%.o:%.c
	$(CC) $< -o $@ $(AFLAGS)
	mv *.o ../$(OBJS_STO_DIR)
