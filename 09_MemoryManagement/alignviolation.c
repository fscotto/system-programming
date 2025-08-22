#include <stdio.h>

int main(void) {
  char greeting[] = "Ahoy Matey";
  char *c = greeting[1];
  unsigned long badnews = *(unsigned long *)c;

  printf("%s\n", c);
  printf("%lu\n", badnews);

  return 0;
}
