/*
 * Q9. Print inode, hard links, uid, gid, size, block size, blocks and the
 *     access, modification and change times of the file given on the
 *     command line.
 *     Run: ./bin/009 /etc/passwd
 */
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main(int, char **argv) {
    struct stat s;
    if (stat(argv[1], &s) == -1) { perror(argv[1]); return 1; }
    printf("Inode = %lu\n", (unsigned long)s.st_ino);
    printf("Number of Hard Links = %lu\n", (unsigned long)s.st_nlink);
    printf("UID = %u\n", s.st_uid);
    printf("GID = %u\n", s.st_gid);
    printf("Size = %ld\n", (long)s.st_size);
    printf("Block Size = %ld\n", (long)s.st_blksize);
    printf("Number of Blocks = %ld\n", (long)s.st_blocks);
    printf("Time of Last Access  = %s", ctime(&s.st_atime));
    printf("Time of Last Modification = %s", ctime(&s.st_mtime));
    printf("Time of Last Change = %s", ctime(&s.st_ctime));
    return 0;
}
