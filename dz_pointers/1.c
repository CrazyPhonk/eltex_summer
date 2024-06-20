#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

char find_substring(char str, char substr) {
    int len1 = strlen(str);
    int len2 = strlen(substr);
    
    for (int i = 0; i <= len1 - len2; i++) {
        int j;
        for (j = 0; j < len2; j++) {
            if (str[i + j] != substr[j]) {
                break;
            }
        }
        if (j == len2) {
            return &str[i];
        }
    }
    
    return NULL;
}

int main() {
    char str[MAX_SIZE];
    char substr[MAX_SIZE];
    
    printf("Enter a string: ");
    gets(str);
    
    printf("Enter a substring to search for: ");
    gets(substr);
    
    char result = find_substring(str, substr);
    
    if (result != NULL) {
        printf("Substring found at index: %ldn", result - str);
    } else {
        printf("Substring not foundn");
    }
    
    return 0;
}