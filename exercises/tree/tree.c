/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Fabio Scotto di Santolo
 */


#include "tree.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int print_tree(const char *path, int depth)
{
	DIR *dir = opendir(path);
	if (!dir)
		return -1;

	struct dirent *entry;
	while ((entry = readdir(dir)) != NULL) {
		// Skip . and ..
		if (strcmp(entry->d_name, ".") == 0 ||
		    strcmp(entry->d_name, "..") == 0)
			continue;

		for (int i = 0; i < depth; i++)
			printf("  ");
		printf("|-- %s\n", entry->d_name);

		// Construct full path
		char full_path[4096];
		snprintf(full_path, sizeof(full_path), "%s/%s", path,
			 entry->d_name);

		struct stat st;
		if (stat(full_path, &st) == 0 && S_ISDIR(st.st_mode)) {
			print_tree(full_path, depth + 1);
		}
	}

	closedir(dir);
	return 0;
}
