CC := gcc
AFLAGS := -Wall -c -g
LDFLAGS := -lpthread
#应用程序1的名字
APPNAME := goods_net 
#应用程序2的名字
APPNAME_TEST := get_shm

#第一个应用程序依赖的.o文件
OBJS := main.o 
OBJS += net_proj.o
OBJS += pthread_recv_from_uart.o 
OBJS += pthread_fetch_from_list.o
OBJS += list.o
OBJS += shm.o

#第二个应用程序依赖的.o文件
OBJS_TEST := test_printf_shm.o
OBJS_TEST += net_proj.o

#指定要生成的两个应用程序目标
#'\c'可以实现echo的不换行,'@'加在命令前，在执行命令时，不显示被执行的命令本身
ALLAPPS:$(APPNAME) $(APPNAME_TEST)
	@echo "appname>>  \c"
	@ls $(APPNAME) $(APPNAME_TEST)

#自动化变量'$^'表示搜索到的所有依赖文件，'$@'为目标文件
$(APPNAME):$(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)
#自动化变量'$<'表示搜索到的第一个依赖文件，'$@'为目标文件
$(OBJS):%.o:%.c
	$(CC) $< -o $@ $(AFLAGS)

$(APPNAME_TEST):$(OBJS_TEST)
	$(CC) $^ -o $@ 
$(OBJS_TEST):%.o:%.c
	$(CC) $< -o $@ $(AFLAGS)


.PHONY:clean
clean:
	rm -rf *.o $(APPNAME) $(APPNAME_TEST) a.out
