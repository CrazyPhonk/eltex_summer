#include <stdio.h>
#include <pthread.h>

#define N 5
#define INCR_COUNT 10000000

int a = 0;
pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;


void* incr_sum(void* arg) {
  for (int i = 0; i < INCR_COUNT; i++) {
    pthread_mutex_lock(&m1);
    a++;
    pthread_mutex_unlock(&m1);
  }

  return NULL;
}

int main() {
  pthread_t threads[N];
  int indexes[N], s;

  for (int i = 0; i < N; i++) {
    indexes[i] = i + 1;

    s = pthread_create(&threads[i], NULL, incr_sum, (void*)&indexes[i]);
    if (s != 0)
      perror("pthread_create");
  }

  for (int i = 0; i < N; i++) {
    s = pthread_join(threads[i], NULL);
    if (s != 0)
      perror("pthread_join");
  }

  printf("%d\n", a);
}
