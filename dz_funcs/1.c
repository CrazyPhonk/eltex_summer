#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct abonent {
char name[10];
char second_name[10];
char tel[10];
} abonent;

int search(abonent *arr, char * nam){
    if (strcmp(arr -> name, nam)==0){
        return 1;
    }
    return -1;
}

int add(char* nam, char *second_name, char * tel, abonent * arr, int i){
    if(i > 100){
                printf("The struct is full\n");
                return -1;
            }
            
            strcpy(arr -> name, nam);
            strcpy(arr -> second_name, second_name);
            strcpy(arr -> tel, tel);
            
            return 0;
}
int delete(char * nam, abonent * arr){
                if(search(arr, nam) == 1){
                    memset(arr -> name, 0, 10);
                    memset(arr -> second_name, 0, 10);
                    memset(arr -> tel, 0, 10);
                    printf("Abonent deleted\n");
                    return 0;
                }
            return -1;
}
void list(abonent arr[]){
    for(int j = 0; j < 100; j++){
                if(arr[j].name[0] != 0){
                    printf("List number %d:\n", j);
                    printf("Name: %s\n", arr[j].name);
                    printf("Second name: %s\n", arr[j].second_name);
                    printf("Tel: %s\n", arr[j].tel);
                    }
                }
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
            printf("Enter name\n");
            scanf("%s", nam);
            printf("Enter second name\n");
            scanf("%s", second_name);
            printf("Enter telephone number\n");
            scanf("%s", tel);
            if(add(nam, second_name, tel, &arr[i], i) != -1){
                printf("New abonent added\n");
            }
            i++;
            break;
        case 2:
            printf("Enter the name to delete\n");
            scanf("%s", nam);
            for(int j = 0; j<100; j++){
                if(delete(nam, &arr[j]) == 0)
                    break;
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
            list(arr);
            break;
        case 5: 
            return 0;
        default:
            printf("Wrong func\n");
        }

    }
}