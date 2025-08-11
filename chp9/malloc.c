#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *xmalloc(size_t size);

int main(void)
{
	char *str = xmalloc(1024);
	char *src = "HelloWorld";
	for (int i = 0; i < (int)strlen(src); i++)
		str[i] = src[i];
	printf("%s\n", str);

	int *numbers = calloc(10, sizeof(int));
	for (int i = 0; i < 10; i++) {
		numbers[i] = i + 1;
		printf("%d ", numbers[i]);
	}

	printf("\n");

	int *p = realloc(numbers, 2 * sizeof(int));
	if (!p) {
		perror("realloc");
		exit(1);
	}

	for (int i = 0; i < 20; i++) {
		printf("%d ", p[i]);
	}
	return EXIT_SUCCESS;
}

void *xmalloc(size_t size)
{
	void *p;
	p = malloc(size);
	if (!p) {
		perror("xmalloc");
		exit(1);
	}
	return p;
}
