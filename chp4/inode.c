#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

/* get_inode - returns the inode of the file associated
 * with the given file descriptor, or -1 on failure.
 */
int get_inode(int fd);

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s <file>\n", argv[0]);
		return 1;
	}

	int fd = open(argv[1], O_RDONLY);
	if (fd < 0) {
		perror("open");
		return 1;
	}

	int inode = get_inode(fd);
	printf("%d\n", inode);

	return 0;
}

int get_inode(int fd)
{
	struct stat buf;

	int ret = fstat(fd, &buf);
	if (ret < 0) {
		perror("fstat");
		return -1;
	}
	return buf.st_ino;
}
