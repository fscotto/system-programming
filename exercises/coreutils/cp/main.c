#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[])
{
	if (argc < 3) {
		fprintf(stderr, "Usage: %s SRC DEST", argv[0]);
		return EXIT_FAILURE;
	}

	const char *src = argv[1];
	const char *dest = argv[2];

	FILE *fp1 = fopen(src, "rb");
	if (fp1 == NULL) {
		perror("cannot open source file");
		return EXIT_FAILURE;
	}

	FILE *fp2 = fopen(dest, "wb");
	if (fp2 == NULL) {
		perror("cannot open destination file");
		fclose(fp1);
		return EXIT_FAILURE;
	}

	size_t nread;
	unsigned char buff[BUFFER_SIZE];
	while ((nread = fread(buff, 1, sizeof(buff), fp1)) > 0) {
		if (fwrite(buff, 1, nread, fp2) != nread) {
			perror("fwrite");
			fclose(fp1);
			fclose(fp2);
			return EXIT_FAILURE;
		}
	}

	if (ferror(fp1)) {
		perror("read error");
		fclose(fp1);
		fclose(fp2);
		return EXIT_FAILURE;
	}

	if (fclose(fp1) != 0) {
		perror("cannot close source file");
		return EXIT_FAILURE;
	}

	if (fclose(fp2) != 0) {
		perror("cannot close destination file");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
