#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int cond = 0;
pthread_mutex_t lock;
pthread_cond_t cv;

void*
even_handler (void *a) {

    while (1) {
        pthread_mutex_lock(&lock);
        
        while (cond%2 != 0) {
            pthread_cond_wait(&cv, &lock);
        }
        
        printf("\nin even thread => %d\n", cond);
        cond++;
        sleep(2);
        pthread_cond_signal(&cv);
        pthread_mutex_unlock(&lock);
    }
}

void*
odd_handler (void *a) {

    while (1) {
        pthread_mutex_lock(&lock);
        
        while (cond%2 == 0) {
            pthread_cond_wait(&cv, &lock);
        }
        
        printf("\nin odd thread => %d\n", cond);
        cond++;
        sleep(2);

        pthread_cond_signal(&cv);
        pthread_mutex_unlock(&lock);
    }   
}

int main () {

    pthread_t odd;
    pthread_t even;
    printf("\n Inside main process\n");

    pthread_create(&even, NULL, even_handler, NULL);
    pthread_create(&odd, NULL, odd_handler, NULL);

    pthread_join(even, NULL);
    pthread_join(odd, NULL);
    return 0;
}
