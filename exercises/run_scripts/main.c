/* This program executes a sequence of Bash scripts
 * in sequential order. Each script is run in a child
 * process, and the parent prints the exit status.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s <file1>...\n", argv[0]);
		return EXIT_FAILURE;
	}

	for (int i = 1; i < argc; i++) {
		const char *script_name = argv[i];
		printf("execute script %d: %s\n", i, script_name);

		/* fork process for execute script itself */
		pid_t pid = fork();
		switch (pid) {
		case -1:
			perror("fork");
			exit(EXIT_FAILURE);
			break;
		case 0:
			// child executes the current script
			if (execlp("/bin/bash", "bash", script_name,
				   (char *)NULL) == -1) {
				perror("execlp");
				exit(EXIT_FAILURE);
			}
			break;
		default:
			// parent waits for the child process
			int status;
			if (waitpid(pid, &status, 0) == -1) {
				perror("waitpid");
				exit(EXIT_FAILURE);
			}
			if (WIFEXITED(status)) {
				printf("script %s exited with code %d\n",
				       script_name, WEXITSTATUS(status));
			} else if (WIFSIGNALED(status)) {
				printf("script %s terminated by signal %d\n",
				       script_name, WTERMSIG(status));
			} else {
				printf("script %s did not exit normally\n",
				       script_name);
			}
			break;
		}
	}

	return EXIT_SUCCESS;
}
