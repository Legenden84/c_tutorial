#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/*
Takeaways: The purpose of this code is to create threads in a loop. So that its not neccessary to create a line of code
for every thread. By using a for loop instead.

1) Create an array of threads.
   If you ptread_create() and phread_join() in the same for loop. Then you will get sequentially execution (1 thread at a time).
2) The corrext approach is to make two for loops.

NB: Threads doesnt neccesarily finish in the order that it is printed in the terminal.
*/

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
    pthread_t thread[4];
    pthread_mutex_init(&mutex, NULL);
    int i;
    for (i = 0; i < 4; i++) {
        if (pthread_create(&thread[i], NULL, &routune, NULL) != 0) {
            perror("Failed to create thread!");
            return 1;
        }
        printf("Thread %d has started\n", i);
    }
    for (i = 0; i < 4; i++) {
        if (pthread_join(thread[i], NULL) != 0) {
            perror("Failed to join thread!");
            return 2;
        }
        printf("Thread %d has finished\n", i);

    }
    pthread_mutex_destroy(&mutex);
    printf("Number of mails: %d\n", mails);
    return 0;
}