#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main(int argc, char *argv[]) {
    const char *path = (argc > 1) ? argv[1] : ".";

    if (print_tree(path, 0) == -1) {
        perror("Error traversing directory");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

