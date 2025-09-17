#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "Usage: %s FILE...\n", argv[0]);
		return EXIT_FAILURE;
	}

	for (int i = 1; i < argc; i++) {
		FILE *fp = fopen(argv[i], "r");
		if (fp == NULL) {
			perror("fopen");
			return EXIT_FAILURE;
		}

		// Read file and print on the stdout
		size_t nread;
		unsigned char buff[BUFFER_SIZE];
		while ((nread = fread(buff, 1, sizeof(buff), fp)) > 0) {
			fwrite(buff, 1, nread, stdout);
		}

		if (fclose(fp) != 0) {
			perror("fclose");
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}
