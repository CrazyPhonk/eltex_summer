#include <stdio.h>

int main() {
    char arr[] = {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'};
    int hex_num = 0x00000000004011d8;
    
    FILE *file = fopen("output.txt", "wb");

    if (file == NULL) {
        printf("Open file error\n");
        return 1;
    }

    fwrite(arr, sizeof(char), sizeof(arr)/sizeof(char), file);
    fwrite(&hex_num, sizeof(int), 1, file);

    fclose(file);
    return 0;
}
