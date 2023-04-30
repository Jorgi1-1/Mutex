#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_HILOS 5

pthread_mutex_t mutex; 
int count = 0; 

void* hilo(void* arg) 
{
    pthread_mutex_lock(&mutex);
    count++; 
    printf("Count value: %d\n", count);
    pthread_mutex_unlock(&mutex); 
    pthread_exit(NULL);
}

int main() 
{
    pthread_t threads[NUM_HILOS];
    int i;

    pthread_mutex_init(&mutex, NULL); 

    for(i = 0; i < NUM_HILOS; i++){
        pthread_create(&threads[i], NULL, hilo, NULL); 
    }

    for(i = 0; i < NUM_HILOS; i++){
        pthread_join(threads[i], NULL); 
    }
    printf("Count final value: %d\n", count);
    pthread_mutex_destroy(&mutex); 
    return 0;
}
