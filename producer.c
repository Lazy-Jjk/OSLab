#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
int *buffer;       
int buffer_size;      
int in = 0;        
int out = 0;       
sem_t empty;  
sem_t full;  
sem_t mutex;  
void* producer(void* arg);
void* consumer(void* arg);
int main() {
    int num_producers, num_consumers;
    printf("Enter the buffer size: ");
    scanf("%d", &buffer_size);
    printf("Enter the number of producers: ");
    scanf("%d", &num_producers);
    printf("Enter the number of consumers: ");
    scanf("%d", &num_consumers);
    buffer = (int*)malloc(buffer_size * sizeof(int));
    if (buffer == NULL) {
        fprintf(stderr, "Failed to allocate memory for buffer\n");
        return -1;
    }
    sem_init(&empty, 0, buffer_size);
    sem_init(&full, 0, 0);           
    sem_init(&mutex, 0, 1);          

    pthread_t *producers = (pthread_t*)malloc(num_producers * sizeof(pthread_t));
    pthread_t *consumers = (pthread_t*)malloc(num_consumers * sizeof(pthread_t));
    int i;
    for ( i = 0; i < num_producers; i++) {
        pthread_create(&producers[i], NULL, producer, (void*)(intptr_t)i);
    }
    for ( i = 0; i < num_consumers; i++) {
        pthread_create(&consumers[i], NULL, consumer, (void*)(intptr_t)i);
    }
    for (i = 0; i < num_producers; i++) {
        pthread_join(producers[i], NULL);
    }
    for (i = 0; i < num_consumers; i++) {
        pthread_join(consumers[i], NULL);
    }
    free(buffer);
    free(producers);
    free(consumers);
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    return 0;
}
void* producer(void* arg) {
    int producer_id = (int)(intptr_t)arg;
    while (1) {
        sleep(rand() % 3 + 1);  
        int item = rand() % 100; 
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[in] = item;
        printf("Producer %d produced item %d at index %d\n", producer_id, item, in);
        in = (in + 1) % buffer_size;  
        sem_post(&mutex);
        sem_post(&full);
    }
    return NULL;
}
void* consumer(void* arg) {
    int consumer_id = (int)(intptr_t)arg;
    while (1) {
        sleep(rand() % 3 + 1); 
        sem_wait(&full);
        sem_wait(&mutex);
        int item = buffer[out];
        printf("Consumer %d consumed item %d from index %d\n", consumer_id, item, out);
        out = (out + 1) % buffer_size;  
        sem_post(&mutex);
        sem_post(&empty);
    }
    return NULL;
}

