#include <stdio.h>
#include <stdlib.h>

void printBinary(int num) {
    for (int i = 31; i >= 0; i--) {
        if (num & (1 << i)) {
            printf("1");
        } else {
            printf("0");
        }
        if (i % 8 == 0) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    int number;
    printf("Enter the number: ");
    scanf("%d", &number);
    printf("Binary num %d: ", number);
    printBinary(number);

    return 0;
}
