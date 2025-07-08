/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Fabio Scotto di Santolo
 */


#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int fd = open("test.txt", O_CREAT | O_RDWR);
	// close(fd);
	return EXIT_SUCCESS;
}
