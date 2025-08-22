/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Fabio Scotto di Santolo
 */


#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

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
