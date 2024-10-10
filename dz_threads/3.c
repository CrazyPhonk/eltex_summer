#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_STORES 5
#define MAX_CAPACITY 10000
#define LOADER_REFILL 5000

typedef struct {
    int capacity;
    int current_customers;
    pthread_mutex_t mutex;
} Store;

typedef struct {
    Store *stores;
    int need;
} CustomerArgs;

Store stores[NUM_STORES];

void init_store(Store *store) {
    store->capacity = rand() % MAX_CAPACITY + 1;
    store->current_customers = 0;
    pthread_mutex_init(&store->mutex, NULL);
}

int enter_store(Store *store) {
    pthread_mutex_lock(&store->mutex);
    if (store->current_customers < store->capacity) {
        store->current_customers++;
        pthread_mutex_unlock(&store->mutex);
        return 1;
    } else {
        pthread_mutex_unlock(&store->mutex);
        return 0;
    }
}

void leave_store(Store *store) {
    pthread_mutex_lock(&store->mutex);
    store->current_customers--;
    pthread_mutex_unlock(&store->mutex);
}

void customer_thread(void *args) {
    CustomerArgs *customer_args = (CustomerArgs *)args;
    Store *stores = customer_args -> stores;
    int need = customer_args->need;

    while (need > 0) {
        for (int i = 0; i < NUM_STORES; i++) {
            if (enter_store(&stores[i])) {
                need -= stores[i].capacity;
                printf("Покупатель зашел в магазин %d, осталось %d потребности\n", stores[i].capacity, need);
                leave_store(&stores[i]);
                sleep(2);
                break;
            }
        }
        if (need <= 0) {
            printf("Покупатель завершил покупки\n");
            break;
        }
    }

    pthread_exit(NULL);
}

void loader_thread(void *args) {
    Store *stores = (Store *)args;

    while (1) {
        for (int i = 0; i < NUM_STORES; i++) {
            if (stores[i].current_customers == 0) {
                stores[i].capacity += LOADER_REFILL;
                printf("Погрузчик заполнил магазин %d на %d\n", stores[i].capacity, LOADER_REFILL);
                sleep(1);
                break;
            }
        }
    }

    pthread_exit(NULL);
}

int main() {
    for (int i = 0; i < NUM_STORES; i++) {
        init_store(&stores[i]);
    }

    pthread_t customer_threads[3];
    CustomerArgs customer_args[3];
    for (int i = 0; i < 3; i++) {
        customer_args[i].stores = stores;
        customer_args[i].need = rand() % 100000;
        pthread_create(&customer_threads[i], NULL, customer_thread, (void *)&customer_args[i]);
    }
    pthread_t loader_thread_id;
    pthread_create(&loader_thread_id, NULL, loader_thread, (void *)stores);

    for (int i = 0; i < 3; i++) {
        pthread_join(customer_threads[i], NULL);
    }
    pthread_join(loader_thread_id, NULL);

    for (int i = 0; i < NUM_STORES; i++) {
        pthread_mutex_destroy(&stores[i].mutex);
    }

    return 0;
}