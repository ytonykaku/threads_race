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

void isClose(long counter, int guess){
    int result = counter - guess;
    if(result < 0) result = result * (-1);
    if(result >= 50000) printf("\nMuito Frio\n");
    else if(result <= 49999 && result >= 10000) printf("\nFrio\n");
    else if(result <= 9999 && result >= 5000) printf("\nQuente\n");
    else printf("\nMuito Quente\n");
}

int main(int argc, char *argv[]) {
    pthread_t t[THREADS];
    int s;
    int guess1, guess2 = 0;


    /*sem_init(&mutex, 0, 1);*/
    for (int i = 0; i < THREADS; ++i) {
        s = pthread_create(&t[i], NULL, threadFunc, NULL);//criando
    }

    for (int i = 0; i < THREADS; ++i) {
        s = pthread_join(t[i], NULL);//esperando elas terminarem
    }

    for(int i = 0; i < 3; i++){
        printf("Jogador 1, digite um número:\n");
        scanf("%d", &guess1);
        isClose(shared, guess1);
        printf("Jogador 2, digite um número:\n");
        scanf("%d", &guess2);  
        isClose(shared, guess2);    
    }

    printf("Jogador 1, digite sua última jogada:\n");
    scanf("%d", &guess1);
    printf("Jogador 2, digite sua última jogada:\n");
    scanf("%d", &guess2);    

    printf("compartilhada = %ld\n", shared);

    guess1 = shared - guess1;
    if(guess1 < 0) guess1 = guess1 * (-1);
    guess2 = shared - guess2;
    if(guess2 < 0) guess2 = guess2 * (-1);

    if(guess1 < guess2) printf("Jogador 1 venceu");
    else printf("Jogador 2 venceu");
}
