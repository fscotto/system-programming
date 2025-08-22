#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Handler for SIGINT */
static void sigint_handler(int signo)
{
	/*
	 * Technically, you shouldn't use printf(...) in a
	 * signal handler, but it isn't the end of the
	 * world. I'll discuss why in the section
	 * "Reentrancy".
	 */
	printf("Caught SIGINT\n");
	exit(EXIT_SUCCESS);
}

int main(void)
{
	/*
	 * Register sigint_handler as our signal handler
	 * for SIGINT.
	 */
	if (signal(SIGINT, sigint_handler) == SIG_ERR) {
		fprintf(stderr, "Cannot handle SIGINT\n");
		exit(EXIT_FAILURE);
	}

	for (;;) {
		pause();
	}
	return EXIT_SUCCESS;
}
