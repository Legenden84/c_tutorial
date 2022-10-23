#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* routine() {
    printf("Beginning threads\n");
    sleep(1);
    printf("Ending thread\n");
}

int main(int argc, char* argv[]) {
    pthread_t thread1;
    pthread_t thread2;
    if (pthread_create(&thread1, NULL, &routine, NULL) != 0) {
        return 1;
    }
    if (pthread_create(&thread2, NULL, &routine, NULL) != 0) {
        return 1;
    }
    if (pthread_join(thread1, NULL) != 0) {
        return 3;
    }
    if (pthread_join(thread2, NULL) != 0) {
        return 4;
    }
    return 0;
}