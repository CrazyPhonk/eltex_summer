#include <stdio.h>
#include <string.h>

char* findSubstring(char *str, char *sub) {
    int i, j;
    int len1 = strlen(str);
    int len2 = strlen(sub);

    for(i = 0; i <= len1 - len2; i++) {
        for(j = 0; j < len2; j++) {
            if(str[i + j] != sub[j]) {
                break;
            }
        }
        if(j == len2) {
            return &str[i];
        }
    }
    return NULL;
}

int main() {
    char str[100];
    char sub[100];

    printf("Enter the string: ");
    scanf("%s", &str);
    printf("Enter the substring to search: ");
    scanf("%s", &sub);
    char *result = findSubstring(str, sub);

    if(result) {
        printf("The begining of substring: %s\n", result);
    } else {
        printf("Substring has not been found\n");
    }

    return 0;
}
