#include <stdio.h>

int main() {
    int num, newByte, result;
    printf("Enter the positive num: ");
    scanf("%d", &num);
    printf("New byte num: ");
    scanf("%d", &newByte);  
    if (newByte < 0 || newByte > 255) {
        printf("Wrong num\n");
        return 1;
    }  
    result = (num & 0xFFFF00FF) | (newByte << 8);
    printf("Result: %d\n", result);
}
