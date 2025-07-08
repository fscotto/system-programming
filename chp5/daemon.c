/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Fabio Scotto di Santolo
 */


#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define NR_OPEN 1048576

int main(void)
{
	// create new process
	pid_t pid = fork();
	if (pid == -1) {
		return -1;
	} else if (pid != 0) {
		printf("Running daemon with pid %d\n", pid);
		exit(EXIT_SUCCESS);
	}

	// create a new session and process group
	if (setsid() == -1)
		return -1;

	// set the working directory to the root directory
	if (chdir("/") == -1)
		return -1;

	// close all open files--NR_OPEN is overkill, but works
	for (int i = 0; i < NR_OPEN; i++) {
		close(i);
	}

	// redirect fd's 0,1,2 to /dev/null
	open("/dev/null", O_RDWR); // stdin
	dup(0);			   // stdout
	dup(0);			   // stderr

	// do its daemon thing
	for (int i = 0; i < 10; i++) {
		printf("Hello from daemon %d\n", getpid());
		sleep(1000);
	}

	return 0;
}
