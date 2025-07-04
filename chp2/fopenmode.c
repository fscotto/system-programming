#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int fd;
	fd = open("test.txt", O_CREAT | O_EXCL,
		  S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		perror("open");
	close(fd);

	return 0;
}
