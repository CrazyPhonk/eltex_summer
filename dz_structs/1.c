#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct abonent {
char name[10];
char second_name[10];
char tel[10];
int a;
} abonent;
int search(abonent *arr, char * nam){
    if (strcmp(arr -> name, nam)==0){
        return 1;
    }
    return -1;
}

int main(){
    abonent arr [100];
    int func;
    int i = 0;
    int j;
    for (j = 0; j < 100;j++){
        memset(arr[j].name, 0, 10);
        memset(arr[j].second_name, 0, 10);
        memset(arr[j].tel, 0, 10);
    }

    bool flag = false;
    char nam[10];
    char second_name[10];
    char tel[10];
    while(1){
        printf("1) New abonent\n");
        printf("2) Delete abonent\n");
        printf("3) Search by name\n");
        printf("4) List\n");
        printf("5) Exit\n");
        scanf("%d", &func);
    switch(func){
        case 1:  
            if(i > 100){
                printf("The struct is full\n");
                break;
            }
            printf("Enter name\n");
            scanf("%s", nam);
            strcpy(arr[i].name, nam);
            printf("Enter second name\n");
            scanf("%s", second_name);
            strcpy(arr[i].second_name, second_name);
            printf("Enter telephone number\n");
            scanf("%s", tel);
            strcpy(arr[i].tel, tel);
            i++;
            break;
        case 2:
            printf("Enter the name to delete\n");
            scanf("%s", nam);
            for(j = 0; j<100; j++){
                if(search(&arr[j], nam) == 1){
                    memset(arr[j].name, 0, 10);
                    memset(arr[j].second_name, 0, 10);
                    memset(arr[j].tel, 0, 10);
                    printf("Abonent deleted\n");
                    break;
                }
            }
            break;
        case 3: 
            printf("Enter the name to search\n");
            scanf("%s", nam);
            printf("%s\n", nam);
            for(j = 0; j < 100; j++){
                if(search(&arr[j], nam)==1){
                    printf("Second name: %s\n", arr[j].second_name);
                    printf("Tel: %s\n", arr[j].tel);
                    flag = true;
                    break;
                }
            }
            if (flag == false){
                printf("Name was not found :(\n");
            }
            break;
        case 4: 
            for(j = 0; j < 100; j++){
                if(arr[j].name[0] != 0){
                    printf("List number %d:\n", j+1);
                    printf("Name: %s\n", arr[j].name);
                    printf("Second name: %s\n", arr[j].second_name);
                    printf("Tel: %s\n", arr[j].tel);
                    }
                }
            break;
        case 5: 
            return 0;
        default:
            printf("Wrong func\n");
        }

    }
}