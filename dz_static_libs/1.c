#include <stdio.h>
#include <stdlib.h>

extern int plus(int a, int b);
extern int minus(int a, int b);
extern int multiply(int a, int b);
extern int devide(int a, int b);

int main(){
    int func = 0;
    int a,b, res;
    while(1){
        printf("1) +\n");
        printf("2) -\n");
        printf("3) *\n");
        printf("4) /\n");
        printf("5) Exit\n");
        scanf("%d", &func);
        printf("Enter 2 nums: \n");
        scanf("%d", &a);
        scanf("%d", &b);
        switch(func){
            case 1:
                res = plus(a,b);
                printf("Result= %d\n", res);
                break;
            case 2:
                res = minus(a,b);
                printf("Result= %d\n", res);
                break;
            case 3:
                res = multiply(a,b);
                printf("Result= %d\n", res);
                break;
            case 4:
                res = devide(a,b);
                printf("Result= %d\n", res);
                break;
            case 5:
                exit(0);
            default:
                printf("Wrong func\n");
        }
    }
}