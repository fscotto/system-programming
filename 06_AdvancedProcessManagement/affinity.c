/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Fabio Scotto di Santolo
 */


#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>

int main(void)
{
	cpu_set_t set;
	CPU_ZERO(&set);
	CPU_SET(0, &set);
	CPU_CLR(1, &set);

	int ret = sched_setaffinity(0, sizeof(cpu_set_t), &set);
	if (ret == -1) {
		perror("sched_setaffinity");
	}

	for (int i = 0; i < CPU_SETSIZE; i++) {
		int cpu = CPU_ISSET(i, &set);
		if (cpu) {
			printf("cpu=%d is set\n", i);
		}
	}

	return 0;
}
