#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define THREADS 10

long shared = 0;

sem_t mutex;

void *threadFunc(void *arg)
{
    int a, b;
    for (long j = 0; j < 100000; j++){
       /* sem_wait(&mutex);*/
        a = shared;
        b = 1;
        shared = a + b;
        /*sem_post(&mutex);*/
    }
}

int main(int argc, char *argv[]) {
    pthread_t t[THREADS];
    int s;

    /*sem_init(&mutex, 0, 1);*/
    for (int i = 0; i < THREADS; ++i) {
        s = pthread_create(&t[i], NULL, threadFunc, NULL);//criando
    }

    for (int i = 0; i < THREADS; ++i) {
        s = pthread_join(t[i], NULL);//esperando elas terminares
    }

    printf("compartilhada = %ld\n", shared);

}
