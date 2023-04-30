#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex; 
pthread_cond_t cond_var; 
int hello_written = 0;

void* hello(void* arg) 
{
    pthread_mutex_lock(&mutex); 
    printf("Hola ");
    hello_written = 1; 
    pthread_cond_signal(&cond_var); 
    pthread_mutex_unlock(&mutex); 
    pthread_exit(NULL);
}

void* world(void* arg) 
{
    pthread_mutex_lock(&mutex); 

    while( hello_written == 0 )
    {
        pthread_cond_wait(&cond_var, &mutex); 
    }

    printf("mundo!\n");

    pthread_mutex_unlock(&mutex); 
    pthread_exit(NULL);
}

int main() {
    pthread_t thread_1, thread_2;

    pthread_mutex_init(&mutex, NULL); 
    pthread_cond_init(&cond_var, NULL); 

    pthread_create(&thread_1, NULL, hello, NULL); 
    pthread_create(&thread_2, NULL, world, NULL); 

    pthread_join(thread_1, NULL); 
    pthread_join(thread_2, NULL); 

    pthread_cond_destroy(&cond_var); 
    pthread_mutex_destroy(&mutex); 

    return 0;
}
