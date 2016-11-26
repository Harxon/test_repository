#CC := gcc
CC := arm-none-linux-gnueabi-gcc 
#"export"能让当前定义的变量，应用在子目录中,否则在子目录中没有相关变量的值
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
#‘@’来隐藏命令的显示，‘-’来关闭执行命令出错的退出Makefile功能,
CHECK_DIR:
	-@mkdir $(BIN_DIR)

$(CODES_DIR):ECHO 
	@make -C $@
ECHO:
	@echo $(CODES_DIR)


.PHONY:clean
clean:
	rm -rf $(BIN_DIR) $(OBJS_STO_DIR)/*.o
