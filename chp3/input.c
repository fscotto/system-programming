#include <limits.h>
#include <stdio.h>

int main(void)
{
	printf("Limit buffer size is %u bytes.\n", LINE_MAX);
	printf("Buffer size is %u bytes.\n", BUFSIZ);
}
