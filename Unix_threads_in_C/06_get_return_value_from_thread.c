#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

/*
Takeaway: The pthread_join() returns a double void pointer (void **).
To return the value of roll_dice():
    1) Add the reference to the &roll_dice in the pthread_create.
    2) Initiate a return type in the main function (int* res).
    3) Pass the reference in the pthread_join as the return value (&res).
    NB: Remember to malloc/free memory! malloc is needed because you cannot
        reference a local variable from a function. Because its on the stack.
    NB: Ussually it is a good idea to malloc/free in the same function.
*/

void* roll_dice() {
    int value = (rand() % 6) + 1;
    int* result = malloc(sizeof(int));
    *result = value;
    printf("Dice roll: %d\n", value);
    printf("Address of dice roll: %p\n", result);
    return (void*) result;
}

int main(int argc, char* argv[]) {
    int* result;
    srand(time(NULL));
    pthread_t thread;
    if (pthread_create(&thread, NULL, &roll_dice, NULL) != 0) {
        return 1;
    }
    if (pthread_join(thread, (void**) &result) != 0) {
        return 2;
    }
    printf("Result: %d\n", *result);
    printf("address of result: %p\n", result);
    free(result);
    return 0;
}