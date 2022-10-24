#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

/*
Takeaway: The pthread_join() returns a double coid pointer (void **).
To return the value of roll_dice():
    1) Add the reference to the &roll_dice in the pthread_create.
    2) Initiate a return type in the main function (int* res).
    3) Pass the reference in the pthread_join as the return value (&res).
    NB: Remember to malloc/free memory!
*/

void* roll_dice() {
    int value = (rand() % 5) + 1;
    int* result = malloc(sizeof(int));
    *result = value;
    // printf("roll_dice(): %d\n", value);
    return (void*) result;
}

int main(int argc, char* argv[]) {
    int* res;
    srand(time(NULL));
    pthread_t th;
    if (pthread_create(&th, NULL, &roll_dice, NULL) != 0) {
        return 1;
    }
    if (pthread_join(th, (void**) &res) != 0) {
        return 2;
    }
    printf("Result: %d\n", *res);
    free(res);
    return 0;
}