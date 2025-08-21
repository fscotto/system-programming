#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

int main(void) {
	/* Initialize string array */
	char **names = (char **)calloc(5, sizeof(char *));
	for (int i = 0; i < 5; i++) {
		names[i] = (char *)malloc(sizeof(char *));
	}
	
	memcpy(names[0], "Fabio", 5);
	memcpy(names[1], "Chiara", 6);
	memcpy(names[2], "Valerio", 7);
	memcpy(names[3], "Luca", 4);
	memcpy(names[4], "Leila", 5);

	printf("\nBefore freed array...\n");
	malloc_stats();
	printf("\n");

	for (int i = 0; i < 5; i++) {
		printf("%s\n", names[i]);
	}

	for (int i = 0; i < 5; i++) {
		free(names[i]);
	}

	printf("\nAfter freed array...\n");
	malloc_stats();
	printf("\n");

	return 0;
}
