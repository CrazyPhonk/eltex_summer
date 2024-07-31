#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE* fd = NULL;
    char c;
    fd = fopen("output.txt", "w");
    if (fd == NULL){
        perror("Cannot open the file to write\n");
        exit(-1);
    }
    fprintf(fd, "String from file");
    fclose(fd);

    fd = fopen("output.txt", "r");
    if (fd == NULL){
        perror("Cannot open the file to read\n");
        exit(-2);
    }
    fseek(fd, 0, SEEK_END);
    long pos = ftell(fd);
    while (pos >= 0) {
        fseek(fd, pos, SEEK_SET);
        c = fgetc(fd);
        printf("%c", c);
        pos--;
    }
    fclose(fd);
}