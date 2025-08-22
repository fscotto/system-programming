/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Fabio Scotto di Santolo
 */


#include <stdio.h>
#define _XOPEN_SOURCE 500
#include <unistd.h>

int main(void)
{
	printf("My session id=%d\n", getsid(0));
	printf("My process group id=%d\n", getpgid(0));
	return 0;
}
