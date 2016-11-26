OBJS := pthread_recv_from_uart.o
OBJS += pthread_fetch_from_list.o
OBJS += main.o
all:$(OBJS)
$(OBJS):%.o:%.c
	$(CC) $< -o $@ $(AFLAGS)
	mv *.o ../$(OBJS_STO_DIR)/
