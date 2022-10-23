#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Takeaway: Use mutex to lock/unlock critical sections. That you want one thread to run, before another thread can run. 
// Thus, getting rid of race conditions.

int mails = 0;
pthread_mutex_t mutex;

void* routune() {
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char* argv[]) {
    pthread_t t1, t2;
    pthread_mutex_init(&mutex, NULL);
    if (pthread_create(&t1, NULL, &routune, NULL) != 0) {
        return 1;
    }
    if (pthread_create(&t2, NULL, &routune, NULL) != 0) {
        return 2;
    }
    if (pthread_join(t1, NULL) != 0) {
        return 2;
    }
    if (pthread_join(t2, NULL) != 0) {
        return 2;
    }
    pthread_mutex_destroy(&mutex);
    printf("Number of mails: %d\n", mails);
    return 0;
}