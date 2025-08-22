#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void catch_sighup(int);

int main(void)
{
	signal(SIGHUP, catch_sighup);
	printf("Hi, I'm a process with PID %d\n", getpid());
	sleep(1000);
	return EXIT_SUCCESS;
}

void catch_sighup(int sig)
{
	printf("Catch signal SIGHUP\n");
	exit(EXIT_SUCCESS);
}
