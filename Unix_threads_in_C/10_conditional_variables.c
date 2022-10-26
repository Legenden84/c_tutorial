#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

/*
    pthread_cond_wait() is equivalent to: 
        pthread_mutex_unlock(&mutex_fuel);
        "wait for signal on cond_fuel"
        pthead_mutex_lock(&mutex_fuel);

    A conditional variable is an identifier for a certain signal that you could either signal or wait for. On signaling you are signaling that
    the conditions might have changed.

    NB: Remember to initialize both the mutex and the cond!, and destroying both aswell.
*/

pthread_mutex_t mutex_fuel;
pthread_cond_t cond_fuel;

int fuel = 0;

void* gas_station_filling(void* arg) {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutex_fuel);
        fuel += 15;
        printf("Gas station fuel amount: %d\n", fuel);
        pthread_mutex_unlock(&mutex_fuel);
        pthread_cond_signal(&cond_fuel);
        sleep(1);
    }
}

void* car(void* arg) {
    pthread_mutex_lock(&mutex_fuel);
    while (fuel < 40) {
        printf("No fuel, waiting...\n");
        pthread_cond_wait(&cond_fuel, &mutex_fuel);
    }
    fuel -= 40;
    printf("Car got fuel. Fuel left in gas station: %d\n", fuel);
    pthread_mutex_unlock(&mutex_fuel);
}

int main(int argc, char* argv[]) {
    pthread_mutex_init(&mutex_fuel, NULL);
    pthread_cond_init(&cond_fuel, NULL);
    pthread_t thread[2];
    for (int i = 0; i < 2; i++) {
        if (i == 1) {
            if (pthread_create(&thread[i], NULL, &gas_station_filling, NULL) != 0) {
                perror("Failed to create thread");
            }
        } else {
            if (pthread_create(&thread[i], NULL, &car, NULL) != 0) {
                perror("Failed to create thread");
            }
        }
    }

    for (int i = 0; i < 2; i++) {
        if (pthread_join(thread[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    pthread_cond_destroy(&cond_fuel);
    pthread_mutex_destroy(&mutex_fuel);
    return 0;    
}