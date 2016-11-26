#注意使用“=”的好处，"wildcard *.o"是选中当前目录中以".o"结尾的文件，“=”赋值方式，让Makefile在检索完整后，才开始给变量赋值，保证数据的完整性
OBJS = $(wildcard *.o)

#自动化变量'$^'表示搜索到的所有依赖文件，'$@'为目标文件
../bin/$(APPNAME):$(OBJS)
	@echo $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)
