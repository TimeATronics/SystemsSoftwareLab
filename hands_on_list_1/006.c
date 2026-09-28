/*
 * Q6. Read from stdin and write to stdout using only read() and write().    
 */
#include <unistd.h>

int main(void) {
    char buf[512]; ssize_t n;
    while ((n = read(0, buf, sizeof buf)) > 0) write(1, buf, n);
    return 0;
}
