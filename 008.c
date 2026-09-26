/*
 * Q8. Open the file given on the command line read-only, read it line by
 *     line, display each line and close it at end of file.
 */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int, char **argv) {
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) { perror(argv[1]); return 1; }
    char line[256]; char c; int n = 0;
    /* Read Byte-by-Byte until EOL or buffer full */
    while (read(fd, &c, 1) == 1) {
        line[n++] = c;
        if (c == '\n' || n == (int)sizeof line - 1) {
            write(1, line, n);
            n = 0;
        }
    }
    /* If last line does not have EOL */
    if (n > 0) write(1, line, n);
    close(fd);
    return 0;
}
