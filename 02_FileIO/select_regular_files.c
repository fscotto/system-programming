/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Fabio Scotto di Santolo
 */


#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>

#define FILE_NUMBER 3
#define FILENAME_MAX_LEN 10
#define TIMEOUT 10
#define BUF_LEN 1024

int create_tmp_file(char *filename);
void cleanup(char *filenames[]);

int main(void)
{
	int exit_code = 0;
	char *filename_template = "test%d.txt";
	char *filenames[FILE_NUMBER] = {NULL};
	int fds[FILE_NUMBER] = {0};

	// Create a bunch of number ephemeral files
	for (int i = 0; i < FILE_NUMBER; i++) {
		char *filename =
		    (char *)malloc(FILENAME_MAX_LEN * sizeof(char));
		if (!filename) {
			perror("malloc failed");
			exit_code = -1;
			goto exit;
		}
		snprintf(filename, FILENAME_MAX_LEN, filename_template, i + 1);
		filenames[i] = filename;
		printf("Opening file %s...\n", filename);
		fds[i] = create_tmp_file(filename);
		if (fds[i] == -1) {
			fprintf(stderr, "Error to open file %s: %s\n", filename,
				strerror(errno));
			exit_code = -1;
			goto exit;
		}
		printf("Open file %s with file descriptor %d\n", filename,
		       fds[i]);

		// write something in the files
		dprintf(fds[i], "Hello I am %s\n", filename);
	}

	fd_set readfds;
	FD_ZERO(&readfds);
	for (int i = 0; i < FILE_NUMBER; i++) {
		FD_SET(fds[i], &readfds);
	}

	struct timeval *timeout =
	    (struct timeval *)malloc(sizeof(struct timeval));
	timeout->tv_sec = TIMEOUT;
	timeout->tv_usec = 0;

	/* This function do not work with regular files because for the
	 * operating system, a regular file is ready always. This example is
	 * wrong the best way to use select() is with socket, pipe or other
	 * channel types.
	 */
	int ret = select(FILE_NUMBER + 1, &readfds, NULL, NULL, timeout);

	if (ret == -1) {
		fprintf(stderr, "Error to select: %s\n", strerror(errno));
		exit_code = 1;
		goto exit;
	} else if (!ret) {
		fprintf(stderr, "%d seconds elapsed.\n", TIMEOUT);
		exit_code = 1;
		goto exit;
	}

	for (int i = 0; i < FILE_NUMBER; i++) {
		int fd = fds[i];
		if (FD_ISSET(fd, &readfds)) {
			char buf[BUF_LEN + 1];
			int len = read(fd, buf, BUF_LEN);
			if (len == -1) {
				fprintf(stderr, "Error reading file %s: %s\n",
					filenames[i], strerror(errno));
				exit_code = 1;
				goto exit;
			}
			if (len) {
				buf[len] = '\0';
				printf("%s:\n%s\n", filenames[i], buf);
			}
		}
	}

exit:
	// Closing and remove all creating files
	for (int i = 0; i < FILE_NUMBER; i++) {
		int fd = fds[i];
		printf("Close file with file descriptor %d\n", fd);
		if (close(fd) == -1) {
			fprintf(stderr, "Error to close file %d: %s\n", fd,
				strerror(errno));
		}
	}

	free(timeout);
	timeout = NULL;

	printf("Cleanup files\n");
	cleanup(filenames);

	return exit_code;
}

int create_tmp_file(char *filename)
{
	int fd = open(filename, O_CREAT | O_EXCL | O_RDWR, 0644);
	if (fd == -1) {
		return -1;
	}
	return fd;
}

void cleanup(char *filenames[])
{
	for (int j = 0; j < FILE_NUMBER; j++) {
		if (filenames[j] != NULL) {
			if (remove(filenames[j]) == -1)
				fprintf(stderr, "Failed to remove %s: %s\n",
					filenames[j], strerror(errno));
			free(filenames[j]);
			filenames[j] = NULL;
		}
	}
}
