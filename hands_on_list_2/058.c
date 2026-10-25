/*
 * Q58. Multithreading Exploration: Write a simple program to create three
 * threads and print the IDs of the created threads.
 */
#include <pthread.h>
#include <stdio.h>

static void *work(void *arg) {
    long id = (long)arg;
    printf("thread %ld: pthread_self() = %lu\n", id, (unsigned long)pthread_self());
    return NULL;
}

int main(void) {
    pthread_t t[3];
    for (long i = 0; i < 3; i++) {
        if (pthread_create(&t[i], NULL, work, (void *)i) != 0) perror("pthread_create");
    }
    for (int i = 0; i < 3; i++) pthread_join(t[i], NULL);
    return 0;
}
