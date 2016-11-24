#CC := gcc
CC := arm-none-linux-gnueabi-gcc
AFLAGS := -Wall -c -g
LDFLAGS := -lpthread
#应用程序1的名字
APPNAME := storage_mamage
CODES_DIR := src
OBJS_STO_DIR := obj 

#自动化变量'$^'表示搜索到的所有依赖文件，'$@'为目标文件
$(APPNAME):*.o
	$(CC) $^ -o $@ $(LDFLAGS)
