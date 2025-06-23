#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(void)
{
	int fd;
	fd = open("test.txt", O_CREAT | O_EXCL);
	if (fd == -1)
		perror("First open");
	close(fd);

	fd = open("test.txt", O_CREAT | O_EXCL);
	if (fd == -1)
		perror("Second open");
	close(fd);

	fd = open("test.txt", O_CREAT | O_EXCL);
	if (fd == -1)
		perror("Third open");
	close(fd);
	
	fd = open("test.txt", O_CREAT);
	if (fd == -1)
		perror("Fourth open");
	close(fd);

	return 0;
}
