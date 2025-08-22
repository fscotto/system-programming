/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Fabio Scotto di Santolo
 */


#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

int main(void)
{
	struct iovec iov[3];

	char *buf[] = {"The term buccaneer comes from the word boucan.\n",
		       "A boucan is a wooden frame used for cooking meet.\n",
		       "Buccaneer is the West Indies name for a pirate.\n"};

	int fd = open("buccaneer.txt", O_WRONLY | O_CREAT | O_TRUNC);
	if (fd == -1) {
		perror("open");
		return 1;
	}

	// fill out three iovec structures
	for (int i = 0; i < 3; i++) {
		iov[i].iov_base = buf[i];
		iov[i].iov_len = strlen(buf[i]) + 1;
	}

	// with a single call, write them all out
	ssize_t nr = writev(fd, iov, 3);
	if (nr == -1) {
		perror("writev");
		return 1;
	}

	printf("wrote %lu bytes\n", nr);

	if (close(fd)) {
		perror("close");
		return 1;
	}

	return 0;
}
