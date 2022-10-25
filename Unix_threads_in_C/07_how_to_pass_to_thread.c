#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/*
    Problem: Create 10 threads, each taking a unique prime from
             the primes array and print it in the screen.

    Solution: Dynamically allocate memory for each thread.
              Free the memory after the value is printed!.

    Takeaway: We are passing memory addresses, and not actual values.
*/

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void* routine(void* argument) {
    int index = *(int*) argument;
    printf("%d ", primes[index]);
    //printf("Address of primes[i]: %p", &primes[index]);
    free(argument);
}

int main(int argc, char* argv[]) {
    pthread_t thread[10];

    int i;
    for (i = 0; i < 10; i++) {
        int* dynamic_memory = malloc(sizeof(int));
        *dynamic_memory = i;
        if (pthread_create(&thread[i], NULL, &routine, dynamic_memory) != 0) {
            perror("Failed to create thread.");
        }
    }
    for (i = 0; i < 10; i++) {
        if (pthread_join(thread[i], NULL) != 0) {
            perror("Failed to join thread.");
        }
    }
    return 0;
}