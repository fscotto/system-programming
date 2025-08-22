/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Fabio Scotto di Santolo
 */


#include <stdio.h>
#include <sys/resource.h>
#include <unistd.h>

int main(void)
{
	int ret;
	ret = nice(0);
	printf("Current nice by nice function: %d\n", ret);
	ret = getpriority(PRIO_PROCESS, 0);
	printf("Current nice by getpriority function: %d\n", ret);
	if (setpriority(PRIO_PROCESS, 0, 10) == -1) {
		perror("setpriority");
		return -1;
	}
	ret = getpriority(PRIO_PROCESS, 0);
	printf("Current nice by getpriority function: %d\n", ret);
	return 0;
}
