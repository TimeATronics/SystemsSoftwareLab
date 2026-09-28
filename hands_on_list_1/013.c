/*
 * Q13. Wait up to 10 seconds for stdin using select().
 */
#include <stdio.h>
#include <sys/select.h>

int main(void) {
    fd_set set; struct timeval tv = {10, 0};
    FD_ZERO(&set);
    FD_SET(0, &set);
    printf("waiting up to 10 seconds for STDIN...\n");
    int r = select(1, &set, NULL, NULL, &tv);
    if (r > 0) printf("data is available on STDIN\n");
    else printf("no data available within 10 seconds\n");
    return 0;
}
