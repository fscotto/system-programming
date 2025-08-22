/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Fabio Scotto di Santolo
 */


#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int ret;

	ret = truncate("./pirate.txt", 45);
	if (ret == -1) {
		perror("truncate");
		return -1;
	}
	return 0;
}
