/*
 * Q14. Identify the type of each file given on the command line.
 *      lstat() is used so a symbolic link is reported as a link and not
 *      as the file it points to.
 */
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("usage: %s path...\n", argv[0]);
        return 1;
    }
    for (int i = 1; i < argc; i++) {
        struct stat s;
        if (lstat(argv[i], &s) == -1) { perror(argv[i]); continue;}
        printf("%s: %s\n", argv[i],
               S_ISREG(s.st_mode)  ? "regular file" :
               S_ISDIR(s.st_mode)  ? "directory" :
               S_ISLNK(s.st_mode)  ? "symbolic link" :
               S_ISFIFO(s.st_mode) ? "FIFO" :
               S_ISSOCK(s.st_mode) ? "socket" :
               S_ISCHR(s.st_mode)  ? "character device" :
               S_ISBLK(s.st_mode)  ? "block device" : "unknown");
    }
    return 0;
}
