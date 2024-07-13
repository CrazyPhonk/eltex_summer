#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(){
    void * lib = NULL;
    int func = 0;
    void * myfunc;
    int a,b, res;
    lib = dlopen("dynamicLib.so", RTLD_NOW);
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
                myfunc = dlsym(lib, "plus");
                res = plus(a,b);
                printf("Result= %d\n", res);
                break;
            case 2:
                myfunc = dlsym(lib, "minus");
                res = minus(a,b);
                printf("Result= %d\n", res);
                break;
            case 3:
                myfunc = dlsym(lib, "multiply");
                res = multiply(a,b);
                printf("Result= %d\n", res);
                break;
            case 4:
                myfunc = dlsym(lib, "devide");
                res = devide(a,b);
                printf("Result= %d\n", res);
                break;
            case 5:
                dlclose(lib);
                return 0;
            default:
                printf("Wrong func\n");
        }
    }
}