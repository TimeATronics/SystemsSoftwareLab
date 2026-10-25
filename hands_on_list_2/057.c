/*
 * Q57. System Limitation Exploration: Write a program to print system
 * limitations for:
 *   Maximum length of arguments in the exec family of functions.
 *   Maximum number of simultaneous processes per user ID.
 *   Number of clock ticks (jiffies) per second.
 *   Maximum number of open files.
 *   Size of a page.
 *   Total number of pages in physical memory.
 *   Number of currently available pages in physical memory.
 */
#include <stdio.h>
#include <unistd.h>

int main(void) {
    printf("a. max exec argument length          = %ld\n", sysconf(_SC_ARG_MAX));
    printf("b. max simultaneous processes/user   = %ld\n", sysconf(_SC_CHILD_MAX));
    printf("c. clock ticks (jiffies) per second  = %ld\n", sysconf(_SC_CLK_TCK));
    printf("d. max open files                    = %ld\n", sysconf(_SC_OPEN_MAX));
    printf("e. size of a page                    = %ld bytes\n", sysconf(_SC_PAGESIZE));
    printf("f. total pages in physical memory    = %ld\n", sysconf(_SC_PHYS_PAGES));
    printf("g. available pages in physical memory= %ld\n", sysconf(_SC_AVPHYS_PAGES));
    return 0;
}
