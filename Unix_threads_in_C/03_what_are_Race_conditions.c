#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/*
Takeaway: Threads doesnt always complete before the other one starts. Therefore, it is kinda random when the actual read/increament/write 
operations occour. (need mutex!)
NB: Race conditions can only occour in multi core processors!
*/

int mails = 0;

void* routune() {
    for (int i = 0; i < 1000000; i++) {
        mails++;
    }
    /*
    1) Read value of mails.
    2) Increament value of mails.
    3) Write value of mails.
    */
    
}

int main(int argc, char* argv[]) {
    pthread_t t1, t2;
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
    printf("Number of mails: %d\n", mails);
    return 0;
}