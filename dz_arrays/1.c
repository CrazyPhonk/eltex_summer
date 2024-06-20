#include <stdlib.h>
#include <stdio.h>
int main(){
    int N = 0;
    int count = 1;
    scanf("%d", &N);
    int matrix [N][N];
    for (int i = 0; i< N; i++){
        for (int j = 0; j<N;j++){
            matrix[i][j] = count;
            count++;
        }
    }
    for (int i = 0; i< N; i++){
        for (int j = 0; j<N;j++){
            printf("%d ", matrix[i][j]);  
        }
        printf("\n");
    }
}