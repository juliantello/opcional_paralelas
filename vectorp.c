//version pthread
#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define VECTOR_SIZE 16
#define NUM_THREADS 8

int V[] = {10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13};
int VR[VECTOR_SIZE];

int func(int m, int n) {
    if (m == 0) {
        return n + 1;
    } else if (n == 0) {
        return func(m - 1, 1);
    } else {
        return func(m - 1, func(m, n - 1));
    }
}

void *thread_func(void *arg) {
    int thread_id = *(int *)arg;
    int start = (VECTOR_SIZE / NUM_THREADS) * thread_id;
    int end = start + VECTOR_SIZE / NUM_THREADS;

    for (int i = start; i < end; i++) {
        int result = func(3, V[i]);
        VR[i] = result;
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_func, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("VR: [ ");
    for (int i = 0; i < VECTOR_SIZE; i++) {
        printf("%d ", VR[i]);
    }
    printf("]\n");

    return 0;
}