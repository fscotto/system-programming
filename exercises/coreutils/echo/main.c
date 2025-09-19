#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
  if (argc == 1) {
    write(STDOUT_FILENO, "\n", 1);
    return EXIT_SUCCESS;
  }

  size_t argl[argc-1];
  size_t bytes_count = 0;
  for (int i = 1; i < argc; i++) {
    size_t len = strlen(argv[i]);
    bytes_count += len;
    argl[i-1] = len;
  }
  bytes_count += argc - 2; // whitespaces
  bytes_count += 1;        // newline

  char *str = malloc(bytes_count + 1);
  if (str == NULL) {
    perror("malloc");
    return EXIT_FAILURE;
  }

  size_t pos = 0;
  for (int i = 1; i < argc; i++) {
    memcpy(str + pos, argv[i], argl[i-1]);
    pos += argl[i-1];
    if (i < argc - 1) {
      str[pos++] = ' ';
    }
  }
  str[pos++] = '\n';
  str[pos] = '\0';

  if (write(STDOUT_FILENO, str, pos) == -1) {
     perror("write");
     free(str);
     return EXIT_FAILURE;
  }

  free(str);
  str = NULL;

  return EXIT_SUCCESS;
}
