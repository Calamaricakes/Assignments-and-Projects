#include <stdio.h>
#include <stdlib.h>

typedef struct Node_t{
    int number;
    struct Node_t* next;
}Node_t;

void freeSingleLinkedList(Node_t* linkedList);
void printSingleLinkedList(Node_t* linkedList);

int main(){

    int integer;
    Node_t* linkedList = NULL;
    Node_t* new_node = NULL;
    Node_t* current_node = NULL;

    printf("Please enter an integer to be linked: ");

    while(scanf("%d", &integer) != EOF){

        if(linkedList == NULL){
            linkedList = (Node_t*)malloc(1);
            linkedList->number = integer;
            linkedList->next = NULL;
            current_node = linkedList;
            printf("Please enter an integer to be linked: ");
            continue;
        }

        new_node = (Node_t*)malloc(1);
        new_node->number = integer;
        new_node->next = NULL;
        current_node->next = new_node;
        current_node = new_node;
        printf("Please enter an integer to be linked: ");

    }
    printSingleLinkedList(linkedList);
    freeSingleLinkedList(linkedList);

    return 0;
}

void printSingleLinkedList(Node_t* linkedList){

    while(linkedList != NULL){
        printf("%d ", linkedList->number);
        linkedList =  linkedList->next;
    }

}

void freeSingleLinkedList(Node_t* linkedList){
    Node_t* next = NULL;

    while (linkedList != NULL) {
        next = linkedList->next;
        free(linkedList);
        linkedList = next;
    }
}
