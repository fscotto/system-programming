#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <alloca.h>

#define MAX_LEN 1024
#define SYSCONF_DIR "/etc"

int open_sysconf(const char *, int, int);

int main(void)
{
	int fd = open_sysconf("/passwd", O_RDONLY, 0644);
	if (fd == -1) {
		perror("open");
		return -1;
	}

	int len;
	if ((len = lseek(fd, 0, SEEK_END)) == -1) {
		perror("lseek");
		return -1;
	}

	if (lseek(fd, 0, SEEK_SET) == -1) {
		perror("lseek");
		return -1;
	}

	char buffer[len + 1];
	memset(buffer, 0, sizeof(buffer));

	ssize_t ret;
	size_t bytes_read_total = 0;
	while (bytes_read_total < len && (ret = read(fd, buffer + bytes_read_total, len - bytes_read_total)) != 0) {
		if (ret == -1) {
			if (errno == EINTR) continue;
			perror("read");
			break;
		}
		bytes_read_total += ret;	
	}
	
	buffer[bytes_read_total] = '\0';
	printf("%s", buffer);

	close(fd);

	return 0;
}

int open_sysconf(const char *file, int flags, int mode)
{
	const char *etc = SYSCONF_DIR;
	char *name = alloca(strlen(etc) + strlen(file) + 1);
	strcpy(name, etc);
	strcat(name, file);
	return open(name, flags, mode);	
}
