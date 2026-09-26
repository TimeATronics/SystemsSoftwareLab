/*
 * Q7. Copy file1 into file2, like $ cp file1 file2.
 *     Run: ./bin/007 file1 file2
 */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int, char **argv) {
    int in = open(argv[1], O_RDONLY);
    if (in == -1) { perror(argv[1]); return 1; }
    int out = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (out == -1) { perror(argv[2]); return 1; }
    char buf[4096];
    ssize_t n;
    while ((n = read(in, buf, sizeof buf)) > 0) write(out, buf, n);
    close(in);
    close(out);
    return 0;
}
