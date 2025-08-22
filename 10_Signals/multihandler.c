#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* handler for SIGINT and SIGTERM */
static void signal_handler(int signo)
{
	if (signo == SIGINT)
		printf("Caught SIGINT!\n");
	else if (signo == SIGTERM)
		printf("Caught SIGTERM!\n");
	else {
		/* this should never happen */
		fprintf(stderr, "Unexpected signal!\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

int main(void)
{
	/*
	 * Register signal_handler as our signal handler
	 * for SIGINT.
	 */
	if (signal(SIGINT, signal_handler) == SIG_ERR) {
		fprintf(stderr, "Cannot handle SIGINT!\n");
		exit(EXIT_FAILURE);
	}
	/*
	 * Register signal_handler as our signal handler
	 * for SIGTERM.
	 */
	if (signal(SIGTERM, signal_handler) == SIG_ERR) {
		fprintf(stderr, "Cannot handle SIGTERM!\n");
		exit(EXIT_FAILURE);
	}
	/* Reset SIGPROF's behavior to the default. */
	if (signal(SIGPROF, SIG_DFL) == SIG_ERR) {
		fprintf(stderr, "Cannot reset SIGPROF!\n");
		exit(EXIT_FAILURE);
	}
	/* Ignore SIGHUP. */
	if (signal(SIGHUP, SIG_IGN) == SIG_ERR) {
		fprintf(stderr, "Cannot ignore SIGHUP!\n");
		exit(EXIT_FAILURE);
	}
	printf("Hi, I'm a process with PID %d\n", getpid());
	for (;;)
		pause();
	return 0;
}
