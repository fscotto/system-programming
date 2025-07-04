#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

	if (argc < 2) {
		fprintf(stderr, "usage: %s <file>\n", argv[0]);
		return 1;
	}

	int fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		perror("open");
		return 1;
	}

	struct stat sb;
	if (fstat(fd, &sb) == -1) {
		perror("fstat");
		return 1;
	}

	if (!S_ISREG(sb.st_mode)) {
		fprintf(stderr, "%s is not a file\n", argv[1]);
		return 1;
	}

	char *p = (char *)mmap(0, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (p == MAP_FAILED) {
		perror("mmap");
		return 1;
	}

	if (close(fd) == -1) {
		perror("close");
		return 1;
	}

	for (int len = 0; len < sb.st_size; len++) {
		putchar(p[len]);
	}

	if (munmap(p, sb.st_size) == -1) {
		perror("munmap");
		return 1;
	}

	return 0;
}
