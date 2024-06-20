#include <stdio.h>
#include <stdlib.h>
#define N 10
int main(){
    int arr [N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int * pointer = arr;
    for (int i = 0; i<N; i++){
        printf("%d ", *(pointer + i));
    }
    printf("\n");
}