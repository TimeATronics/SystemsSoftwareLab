/*
 * Q25. Execute another program with exec.
 *   a. the program itself (echo here)
 *   b. pass it an argument: ./bin/025 Alice
 * exec() replaces the current image, so it only returns on error.
 */
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
    const char *name = argc > 1 ? argv[1] : "guest";
    execl("/bin/echo", "echo", "Hello", name, (char *)0);
    return 1;
}
