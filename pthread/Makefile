CC := gcc
AFLAGS := -Wall -c -g
LDFLAGS := -lpthread
APPNAME := goods_net

OBJS := main.o 
OBJS += net_proj.o
OBJS += pthread_recv_from_uart.o 
OBJS += pthread_fetch_from_list.o

$(APPNAME):$(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)
	@ls $(APPNAME) 
$(OBJS):%.o:%.c
	$(CC) $< -o $@ $(AFLAGS)

.PHONY:clean
clean:
	rm -rf *.o a.out goods_net
