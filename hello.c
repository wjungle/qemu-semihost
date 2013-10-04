#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>

#define READ_COUNTER_ADDR 0x40050000

#define COUNTER_TIMES 5
int32_t *read_counter = (int32_t *) READ_COUNTER_ADDR;
int main(void)
{
	//printf("This is a test program for QEMU counter device\n");
	//printf("See http://github.com/krasin/qemu-counter for more details\n\n");
	//printf("Let's check if the Read Counter device presented\n");
	for (int i = 0; i < COUNTER_TIMES; i++) {
		printf("The device has been accessed for %"PRId32" times!\n", *read_counter);
	}
	int32_t now = *read_counter;
	if (now == 0) {
		printf("ERROR - No Read Counter detected\n");
	}
	else if (now == COUNTER_TIMES + 1) {
		printf("OK - Read Counter works as intended\n");
	}
	else {
		printf("ERROR - Something is wrong with Read Counter\n");
	}
	
	/* test semihost call: open, read, close */
	int in_fd = open("/tmp/uname", O_RDONLY);
	char buf[100] = { 0, };
	int bytesRead = read(in_fd, buf, 100);
	printf("read from your PC: \033[1;33m%s\033[0m\n", buf);
	close(in_fd);
	
	return 0;
}
