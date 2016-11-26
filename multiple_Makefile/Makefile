#CC := gcc
CC := arm-none-linux-gnueabi-gcc
export AFLAGS := -Wall -c -g -I ../include/
export LDFLAGS := -lpthread
#应用程序1的名字
export APPNAME := storage_mamage
CODES_DIR:=src main 
export OBJS_STO_DIR:=obj
export BIN_DIR:=bin



all:$(CODES_DIR) CHECK_DIR
	@make -C $(OBJS_STO_DIR)
	ls $(BIN_DIR)
CHECK_DIR:
	-@mkdir $(BIN_DIR)

#自动化变量'$^'表示搜索到的所有依赖文件，'$@'为目标文件
$(CODES_DIR):ECHO 
	@make -C $@
ECHO:
	@echo $(CODES_DIR)
#自动化变量'$<'表示搜索到的第一个依赖文件，'$@'为目标文件 
#使用vpath来指定，当前目录中搜索不到相关类型文件后的搜索文件的目录
#vpath %.c src


.PHONY:clean
clean:
	rm -rf $(BIN_DIR) $(OBJS_STO_DIR)/*.o
