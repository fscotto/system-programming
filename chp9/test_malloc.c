#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int main(void) {
	char *buf = (char *)malloc(256);
	if (!buf) {
		perror("malloc");
		return 1;
	}

	size_t size = malloc_usable_size(buf);
	printf("%d\n", size);
	free(buf);
	return 0;
}
