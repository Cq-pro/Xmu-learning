#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty, full, mutex;

void *producer(void *arg) {
    int item;
    while (1) {
        item = rand() % 100; // 生成数据
        sem_wait(&empty);     // 检查是否有空位
        sem_wait(&mutex);     // 上锁
        
        buffer[in] = item;    // 将数据放入缓冲区
        in = (in + 1) % BUFFER_SIZE;
        printf("Produced: %d\n", item);
        
        sem_post(&mutex);     // 解锁
        sem_post(&full);      // 更新占用位置
    }
}

void *consumer(void *arg) {
    int item;
    while (1) {
        sem_wait(&full);      // 检查是否有数据
        sem_wait(&mutex);     // 上锁
        
        item = buffer[out];   // 取出数据
        out = (out + 1) % BUFFER_SIZE;
        printf("Consumed: %d\n", item);
        
        sem_post(&mutex);     // 解锁
        sem_post(&empty);     // 更新空闲位置
    }
}

int main() {
    pthread_t prod, cons;
    sem_init(&empty, 0, BUFFER_SIZE); 
    sem_init(&full, 0, 0); 
    sem_init(&mutex, 0, 1); 

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
