OBJS := list.o
OBJS += shm.o
OBJS += sem.o
OBJS += net_proj.o
#使用all该伪目标的目的是想让“$(OBJS)”都能生成
all:$(OBJS)

#自动化变量'$<'表示搜索到的第一个依赖文件，'$@'为目标文件 
#使用vpath来指定，当前目录中搜索不到相关类型文件后的搜索文件的目录
#vpath %.c src
$(OBJS):%.o:%.c
	$(CC) $< -o $@ $(AFLAGS)
	mv *.o ../$(OBJS_STO_DIR)/
