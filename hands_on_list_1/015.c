/*
 * Q15. Display the environment of the user using the environ variable.
 */
#include <stdio.h>

extern char **environ;

int main(void) {
    for (char **e = environ; *e != NULL; e++) printf("%s\n", *e);
    return 0;
}
