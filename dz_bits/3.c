#include <stdio.h>
#include <stdlib.h>

int printBinary(int num, int count) {
    for (int i = 31; i >= 0; i--) {
        if (num & (1 << i)) {
            printf("1");
            count++;
        } else {
            printf("0");
        }
        if (i % 8 == 0) {
            printf(" ");
        }
    }
    printf("\n");
    return count;
}

int main() {
    int number, count = 0, result = 0;
    printf("Enter the number: ");
    scanf("%d", &number);
    printf("Binary num %d: ", number);
    result = printBinary(number, count);
    printf("Result: %d\n", result);
    return 0;
}
