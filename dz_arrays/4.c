#include <stdio.h>

void fill_the_Matrix(int n, int matrix[n][n]) {
    int value = 1;
    int minRow = 0, minCol = 0;
    int maxRow = n - 1, maxCol = n - 1;
    while (value <= n * n) {
        for (int i = minCol; i <= maxCol; i++) {
            matrix[minRow][i] = value++;
        }
        minRow++;
        for (int i = minRow; i <= maxRow; i++) {
            matrix[i][maxCol] = value++;
        }
        maxCol--;
        for (int i = maxCol; i >= minCol; i--) {
            matrix[maxRow][i] = value++;
        }
        maxRow--;
        for (int i = maxRow; i >= minRow; i--) {
            matrix[i][minCol] = value++;
        }
        minCol++;
    }
}

int main() {
    int N;
    printf("Enter the number\n");
    scanf("%d", &N);

    int matrix[N][N];
    

    fill_the_Matrix(N, matrix);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}