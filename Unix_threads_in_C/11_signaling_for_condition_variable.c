#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

/*
    pthread_cond_signal() only awakens 1 thread (kinda random which one). 
    Use pthread_cond_broadcast() instead to "broadcast" to all ofthe threads.
*/

pthread_mutex_t mutex_fuel;
pthread_cond_t cond_fuel;

int fuel = 0;

void* gas_station_filling(void* arg) {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutex_fuel);
        fuel += 60;
        printf("Gas station fuel amount: %d\n", fuel);
        pthread_mutex_unlock(&mutex_fuel);
        pthread_cond_broadcast(&cond_fuel);
        sleep(1);
    }
}

void* car(void* arg) {
    pthread_mutex_lock(&mutex_fuel);
    while (fuel < 40) {
        printf("No fuel, waiting...\n");
        pthread_cond_wait(&cond_fuel, &mutex_fuel);
    }
    fuel -= 30;
    printf("Car got fuel. Fuel left in gas station: %d\n", fuel);
    pthread_mutex_unlock(&mutex_fuel);
}

int main(int argc, char* argv[]) {
    pthread_mutex_init(&mutex_fuel, NULL);
    pthread_cond_init(&cond_fuel, NULL);
    pthread_t thread[6];
    for (int i = 0; i < 6; i++) {
        if (i == 4 || i == 5) {
            if (pthread_create(&thread[i], NULL, &gas_station_filling, NULL) != 0) {
                perror("Failed to create thread");
            }
        } else {
            if (pthread_create(&thread[i], NULL, &car, NULL) != 0) {
                perror("Failed to create thread");
            }
        }
    }

    for (int i = 0; i < 6; i++) {
        if (pthread_join(thread[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    pthread_cond_destroy(&cond_fuel);
    pthread_mutex_destroy(&mutex_fuel);
    return 0;    
}