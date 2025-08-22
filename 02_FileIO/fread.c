/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Fabio Scotto di Santolo
 */


#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	printf("Try to open file read.txt\n");
	int fd = open("read.txt", O_RDONLY);
	if (fd == -1) {
		perror("Failed to open read.txt");
		return -1;
	}
	printf("Open file success\n");

	int len;
	if ((len = lseek(fd, 0, SEEK_END)) == -1) {
		perror("Failed to move cursor at end of read.txt file");
		return -1;
	}
	printf("File size of %d bytes\n", len);
	if (lseek(fd, 0, SEEK_SET) == -1) {
		perror("Failed to move cursor at start of read.txt file");
		return -1;
	}

	printf("Reading file read.txt\n");
	char buf[len + 1];
	memset(buf, 0, sizeof(buf));

	size_t bytes_read_total = 0;
	ssize_t ret;
	while (bytes_read_total < len &&
	       (ret = read(fd, buf + bytes_read_total,
			   len - bytes_read_total)) != 0) {
		if (ret == -1) {
			if (errno == EINTR)
				continue;
			perror("Failed to read read.txt");
			break;
		}
		bytes_read_total += ret;
	}

	buf[bytes_read_total] = '\0';

	printf("File text is:\n\"%s\"\n", buf);

	printf("Close file read.txt\n");

	if (close(fd) == -1) {
		perror("Failed to close read.txt");
		return -1;
	}

	return 0;
}
