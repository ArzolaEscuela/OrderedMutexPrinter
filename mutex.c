#include<stdio.h> 
#include<string.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

const int _TARGET_THREAD_COUNT = 5;
pthread_t threads[5];

int idCounter = 0;
int currentTurn = 1; 
pthread_mutex_t lock; 
  
void* OrderedPrint(void *arg) 
{ 
    pthread_mutex_lock(&lock); 
    idCounter++;
    int id = idCounter;
    printf("\nThread #%d has been created.", id); 
    pthread_mutex_unlock(&lock);

    while(1)
    {
        while(currentTurn != id) { sleep(1); }
        printf("\nThread #%d prints.", id); 
        currentTurn++;
        if (currentTurn > _TARGET_THREAD_COUNT){currentTurn = 1;}
    }
  
    return NULL; 
} 

int main ()
{
    for (int i = 0; i < _TARGET_THREAD_COUNT; i++)
    {
        int err;
        err = pthread_create(&threads[i], NULL, OrderedPrint, NULL);
        if (err)
        {
            printf("There was an error: %d", err);
            return 1;
        }
    }

    pthread_join(threads[0], NULL);
    return 0;
}
