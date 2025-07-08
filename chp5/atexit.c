/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Fabio Scotto di Santolo
 */


#include <stdio.h>
#include <stdlib.h>

void out(void)
{
	printf("atexit() succeeded!\n");
}

int main(void)
{
	if (atexit(out)) {
		fprintf(stderr, "atexit() failed\n");
		return 1;
	}
	return 0;
}
