#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex, rw_mutex;
int read_count = 0;

void *reader(void *arg) {
    while (1) {
        sem_wait(&mutex); // 锁定mutex保护read_count
        read_count++;
        if (read_count == 1) {
            sem_wait(&rw_mutex); // 第一个读者锁定rw_mutex
        }
        sem_post(&mutex); // 解锁mutex

        printf("Reading data...\n"); // 读操作

        sem_wait(&mutex);
        read_count--;
        if (read_count == 0) {
            sem_post(&rw_mutex); // 最后一个读者解锁rw_mutex
        }
        sem_post(&mutex);
    }
}

void *writer(void *arg) {
    while (1) {
        sem_wait(&rw_mutex); // 锁定rw_mutex保证互斥

        printf("Writing data...\n"); // 写操作

        sem_post(&rw_mutex); // 解锁rw_mutex
    }
}

int main() {
    pthread_t r[5], w[5];
    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);

    for (int i = 0; i < 5; i++) {
        pthread_create(&r[i], NULL, reader, NULL);
        pthread_create(&w[i], NULL, writer, NULL);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(r[i], NULL);
        pthread_join(w[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);

    return 0;
}
