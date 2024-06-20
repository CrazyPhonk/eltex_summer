#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("Введите размер матрицы: ");
    scanf("%d", &n);
    
    int matrix[n][n];
    
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            matrix[i][j] = 1;
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            matrix[i][j] = 0;
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}