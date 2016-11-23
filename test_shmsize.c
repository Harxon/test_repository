#include <stdio.h>
#include <sys/user.h>

int main(int argc, const char *argv[])
{	
	//PAGE_SIZE : 1UL << 12
	printf("PAGE_SIZE:hex:%#x (%ld)\n",PAGE_SIZE,PAGE_SIZE);
	return 0;
}
