/*
 * Q18. Record locking on a file with three records (20 bytes each).
 *     Lock a record before accessing or modifying it:
 *     a. write lock on record 1, then b. read lock on record 2.
 */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

/* One record = 4-byte int id + 16-byte name = 20 bytes. Offsets 0, 20 and 40. */
struct rec { int id; char name[16]; };

int main(void) {
    int fd = open("records.db", O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd == -1) { perror("open records.db"); return 1; }
    struct rec r[3] = {{1, "alpha"}, {2, "beta"}, {3, "gamma"}};
    write(fd, r, sizeof r);

    /* l_len = sizeof(struct rec) locks one record. */
    struct flock fl;
    fl.l_whence = SEEK_SET; /* l_start is an absolute offset */
    fl.l_len = sizeof(struct rec);
    struct rec cur; /* hold the record being read */

    /* a. write lock (exclusive) on record 1 at offset 0 */
    fl.l_type = F_WRLCK;
    fl.l_start = 0;
    fcntl(fd, F_SETLKW, &fl); /* wait if someone else holds the lock */
    lseek(fd, fl.l_start, SEEK_SET); /* position the offset at record 1 */
    read(fd, &cur, sizeof cur); /* access the record only when locked */
    printf("record 1 before = %s\n", cur.name);

    struct rec upd = {cur.id, "ALPHA"}; /* new record to write */
    lseek(fd, fl.l_start, SEEK_SET); /* back to record 1 to write it back */

    write(fd, &upd, sizeof upd);
    printf("record 1 write-locked and updated to %s\n", upd.name);

    /* b. read lock (shared) on record 2 at offset 20; read-only access */
    fl.l_type = F_RDLCK;
    fl.l_start = sizeof(struct rec);
    fcntl(fd, F_SETLKW, &fl);
    lseek(fd, fl.l_start, SEEK_SET);

    read(fd, &cur, sizeof cur);
    printf("record 2 read-locked: %s\n", cur.name);

    close(fd);   /* closing the file releases every lock held on it */
    return 0;
}
