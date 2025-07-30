#define _GNU_SOURCE
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

static void *download(void *);

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "Usage: %s file1 file2...", argv[0]);
		return 1;
	}

	const int nfile = argc - 1;
	pthread_t workers[nfile];
	for (int i = 0; i < nfile; i++) {
		pthread_create(&workers[i], NULL, download, argv[i + 1]);
	}

	for (int i = 0; i < nfile; i++) {
		pthread_join(workers[i], NULL);
	}
	printf("All downloads complete.\n");

	return 0;
}

static void *download(void *arg)
{
	char *uri = (char *)arg;
	int tid = syscall(SYS_gettid);
	printf("[Thread %x] Starting download of %s\n", tid, uri);
	sleep(rand() % 3 + 1);
	printf("[Thread %x] Finished download of %s\n", tid, uri);
	pthread_exit(0);
}
