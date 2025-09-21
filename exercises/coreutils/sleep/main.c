#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void alarm_handler(int, siginfo_t *, void *);

int main(int argc, char *argv[])
{
  struct sigaction act, old_act;
  sigset_t newmask, oldmask, suspmask;
  
  if (argc < 2) {
    fprintf(stderr, "Usage: %s SECONDS", argv[0]);
    return EXIT_FAILURE;
  }

  unsigned int timeout = (unsigned int)strtol(argv[1], (char **)NULL, 10);

  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;
  act.sa_sigaction = alarm_handler;
  
  if (sigaction(SIGALRM, &act, &old_act) < 0) {
    perror("sigaction");
    return EXIT_FAILURE;
  }

  sigemptyset(&newmask);
  sigaddset(&newmask, SIGALRM);
  if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
    perror("sigprocmask");
    return EXIT_FAILURE;
  }

  alarm(timeout);

  suspmask = oldmask;
  sigdelset(&suspmask, SIGALRM);
  sigsuspend(&suspmask);

  alarm(0);

  if (sigaction(SIGALRM, &old_act, NULL) == -1) {
    perror("sigaction restore");
  }

  if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
    perror("sigprocmask restore");
  }
  
  return EXIT_SUCCESS;
}

static void alarm_handler(int signo, siginfo_t *info, void *context)
{
  //printf("Catch signal %d from %u\n", signo, info->si_pid);
}
