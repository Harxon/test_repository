#include <stdio.h>
#include "list.h"

int main(int argc, const char *argv[])
{
	char buf[24] = "st:e1000200030004000500";
	char recv_buf[24] = {0};

	linklistp hp,tp;

	hp = create_list_head(&tp);

	printf("buf:%s\n",buf);
	proj_write_to_list_tail(&tp,buf);
	strcpy(buf,"123");
	printf("buf:%s\n",buf);
	proj_write_to_list_tail(&tp,buf);
	printf("buf:%s\n",buf);
	strcpy(buf,"abc");
	proj_write_to_list_tail(&tp,buf);

	read_from_list_head(hp,tp,recv_buf);
	printf("recv_buf:%s\n",recv_buf);
	read_from_list_head(hp,tp,recv_buf);
	printf("recv_buf:%s\n",recv_buf);
	read_from_list_head(hp,tp,recv_buf);
	printf("recv_buf:%s\n",recv_buf);
	return 0;
}
