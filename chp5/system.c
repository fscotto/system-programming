#include <stdio.h>
#define _XOPEN_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* my_system - synchronously spawns and waits for the command
 * "/bin/sh -c <cmd>".
 * 
 * Returns -1 on error of any sort, or the exit code from the
 * launched process. Does not block or ignore any signals.
 */
int my_system(const char *);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <command>", argv[0]);
        return EXIT_FAILURE;
    }
    
    const char *command = argv[1];
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return EXIT_FAILURE;
    } else if (pid > 0) {
        int ret = my_system(command);
        if (ret == -1) {
            fprintf(stderr, "command: \"%s\" error", command);
            return EXIT_FAILURE;
        }
        return ret;
    }
    
    int status;
    wait(&status);
    return status;
}

int my_system(const char *cmd) {
    pid_t pid = fork();
    if (pid == -1) {
        return -1;
    } else if (pid == 0) {
        const char *argv[4];
        argv[0] = "sh";
        argv[1] = "-c";
        argv[2] = cmd;
        argv[3] = NULL;

        execv("/bin/sh", argv);
        exit(-1);
    }
    
    int status;
    if (waitpid(pid, &status, 0) == -1) {
        return -1;
    } else if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }
    return -1;
}
