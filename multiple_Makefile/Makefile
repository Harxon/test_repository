#CC := gcc
CC := arm-none-linux-gnueabi-gcc
AFLAGS := -Wall -c -g
LDFLAGS := -lpthread
#应用程序1的名字
APPNAME := storage_mamage
CODES_DIR := src
OBJS_STO_DIR := obj

#指定要生成的两个应用程序目标
#'\c'可以实现echo的不换行,'@'加在命令前，在执行命令时，不显示被执行的命令本身
ALLAPPS:CHANGE1 CHANGE2
	@echo "appname>>  \c"
	@ls $(APPNAME) 
	@rm *.o 
#	mv $(APPNAME) /source/rootfs 

CHANGE2:
	make -C $(OBJS_STO_DIR)
	echo $(OBJS_STO_DIR)

CHANGE1:
	make -C $(CODES_DIR)
	echo $(CODES_DIR)


.PHONY:clean
clean:
	rm -rf *.o $(APPNAME) a.out
