#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Data{
    char name[10];
    char second_name[10];
    char tel[10];
} Data;


typedef struct Node {
    Data data;
    struct Node* next;
} Node;

Node* head = NULL; 


void addElement(char name[], char second_name[], char tel[]) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->data.name, name);
    strcpy(newNode->data.second_name, second_name);
    strcpy(newNode->data.tel, tel);
    newNode->next = head;
    head = newNode;
    printf("The element was added\n");
}


void deleteElement(char name[]) {
    Node* temp = head;
    Node* prev = NULL;
    while(temp != NULL) {
        if(strcmp(temp->data.name, name) == 0) {
            if(prev == NULL) {
                head = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("The element was deleted\n");
}


void getElement(char name[]) {
    Node* temp = head;
    while(temp != NULL) {
        if(strcmp(temp->data.name, name) == 0) {
            printf("Name: %s, Second name: %s, tel: %s\n", temp->data.name, temp->data.second_name,temp->data.tel);
            return;
        }
        temp = temp->next;
    }
    printf("The element was not found\n");
}


void getAllElements() {
    Node* temp = head;
    while(temp != NULL) {
        printf("Name: %s, Second name: %s, tel: %s\n", temp->data.name, temp->data.second_name, temp->data.tel);
        temp = temp->next;
    }
}

void freeAll(){
    Node * tmp = head;
    Node * next;
    while(tmp!= NULL){
        next = tmp -> next;
        free(tmp);
        tmp = next;
    }
    printf("Object cleared\n");
}

int main() {
    char name[10];
    char second_name[10];
    char tel[10];
    int choice;
    
    while(1) {
        printf("1) New abonent\n");
        printf("2) Delete abonent\n");
        printf("3) Search by name\n");
        printf("4) List\n");
        printf("5) Exit\n");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("Enter the name of an element: ");
                scanf("%s", name);
                printf("Enter the second name of an element: ");
                scanf("%s", second_name);
                printf("Enter the phone number of an element: ");
                scanf("%s", tel);
                addElement(name, second_name, tel);
                break;
            case 2:
                printf("Enter the name to delete: ");
                scanf("%s", name);
                deleteElement(name);
                break;
            case 3:
                printf("Enter the name to search: ");
                scanf("%s", name);
                getElement(name);
                break;
            case 4:
                getAllElements();
                break;
            case 5:
                freeAll();
                exit(0);
            default:
                printf("Wrong func\n");
        }
    }
    
    return 0;
}
