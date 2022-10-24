#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/*
Takeaway: Threads are sharing memory. Meaning, changing a variable in one thread. Also, changes the same variable in the other threads.
*/

int x = 2;

void* routune() {
    x++;
    sleep(1);
    printf("Value of x: %d\n", x);
}

void* routune2() {
    sleep(2);
    printf("Value of x: %d\n", x);
}

int main(int argc, char* argv[]) {
    pthread_t t1, t2;
    if (pthread_create(&t1, NULL, &routune, NULL) != 0) {
        return 1;
    }
    if (pthread_create(&t2, NULL, &routune2, NULL) != 0) {
        return 2;
    }
    if (pthread_join(t1, NULL)) {
        return 2;
    }
    if (pthread_join(t2, NULL)) {
        return 2;
    }
    return 0;
}