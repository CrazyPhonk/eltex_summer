#include <stdio.h>
#include <pthread.h>

#define N 5

void* print_index(void* arg) {
  int* i = (int*)arg;
  printf("%d\n", *i);

  return NULL;
}

int main() {
  pthread_t threads[N];
  int indexes[N], s;

  for (int i = 0; i < N; i++) {
    indexes[i] = i + 1;

    s = pthread_create(&threads[i], NULL, print_index, (void*)&indexes[i]);
    if (s != 0)
      perror("pthread_create");
  }

  for (int i = 0; i < N; i++) {
    s = pthread_join(threads[i], NULL);
    if (s != 0)
      perror("pthread_join");
  }
}
