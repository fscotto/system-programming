/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Fabio Scotto di Santolo
 */


#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFF_LEN 4096

int main(int argc, char *argv[])
{
	// Check number of arguments
	if (argc < 3) {
		fprintf(stderr, "Usage: %s SOURCE DEST\n", argv[0]);
		return EXIT_FAILURE;
	}

	// Get arguments
	const char *src = argv[1];
	const char *dst = argv[2];

	// Open source file in read only mode
	int srcfd = open(src, O_RDONLY);
	if (srcfd == -1) {
		perror("Failed open source file");
		return EXIT_FAILURE;
	}

	// Open destination file in write mode, if exists trunc file otherwise
	// create a new file
	int dstfd = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (dstfd == -1) {
		perror("Failed open destination file");
		if (close(srcfd) == -1) {
			perror("Failed close source file");
		}
		return EXIT_FAILURE;
	}

	int exit_code = EXIT_SUCCESS;
	char buff[BUFF_LEN]; // reading data buffer
	ssize_t read_bytes;
	while ((read_bytes = read(srcfd, buff, BUFF_LEN)) != 0) {
		if (read_bytes == -1) {
			// There is an error for reading source file
			if (errno == EINTR)
				continue;
			perror("Failed to read source file");
			exit_code = EXIT_FAILURE;
			break;
		}

		// Write buffer at destination file
		if (write(dstfd, buff, read_bytes) == -1) {
			perror("Error to write to destination file");
			exit_code = EXIT_FAILURE;
			break;
		}
	}

	// Try to close files
	if (close(srcfd) == -1) {
		perror("Failed to close source file");
		exit_code = EXIT_FAILURE;
	}
	if (close(dstfd) == -1) {
		perror("Failed to close destination file");
		exit_code = EXIT_FAILURE;
	}

	return exit_code;
}
