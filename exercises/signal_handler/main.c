#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t sigint_caught = 0;

void signal_handler(int signo, siginfo_t *si, void *ucontext)
{
	(void)si;
	(void)ucontext;

	if (signo == SIGINT) {
		sigint_caught += 1;
		if (write(STDOUT_FILENO, "Caught SIGINT signal\n", 22) == -1) {
			_exit(EXIT_FAILURE);
		}
		if (sigint_caught >= 3) {
			if (write(STDOUT_FILENO, "Reach SIGINT limit\n", 20) ==
			    -1) {
				_exit(EXIT_FAILURE);
			}
			_exit(EXIT_FAILURE);
		}
	} else if (signo == SIGUSR1) {
		if (write(STDOUT_FILENO, "Caught SIGUSR1 signal\n", 23) == -1) {
			_exit(EXIT_FAILURE);
		}
	} else {
		if (write(STDOUT_FILENO, "Unknown signal\n", 16) == -1) {
			_exit(EXIT_FAILURE);
		}
	}
}

int main(void)
{
	struct sigaction action;
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGINT);
	sigaddset(&action.sa_mask, SIGUSR1);
	action.sa_sigaction = signal_handler;
	action.sa_flags = SA_SIGINFO;

	if (sigaction(SIGINT, &action, NULL) == -1) {
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGUSR1, &action, NULL) == -1) {
		perror("sigaction");
		exit(EXIT_FAILURE);
	}

	printf("Hi, I'm process with PID %d\n", getpid());
	for (;;)
		pause();
	return EXIT_SUCCESS;
}
