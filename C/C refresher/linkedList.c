#include <stdio.h>
#include <stdlib.h>

typedef struct Node_t{
    int number;
    struct Node_t* next;
}Node_t;

void freeSingleLinkedList(Node_t* linkedList);
void printSingleLinkedList(Node_t* linkedList);
Node_t* deleteFromSingleLinkedList(Node_t* linkedList, int deleteNumber);

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

    char decision;
    int deleteNumber;

    printf("\nDo you wish to delete any from the list? Y/N\n");

    scanf("%c", &decision);

    while(decision == 'Y' || decision == 'y'){
        printf("Please enter integer to delete: ");
        scanf("%d", &deleteNumber);
        linkedList = deleteFromSingleLinkedList(linkedList, deleteNumber);
        printSingleLinkedList(linkedList);
        printf("\nDo you wish to delete any from the list? Y/N\n");
        scanf(" %c", &decision);
    }

    freeSingleLinkedList(linkedList);

    return 0;
}

void printSingleLinkedList(Node_t* linkedList){

    if(linkedList == NULL){
        printf("Empty list\n");
        return;
    }

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

Node_t* deleteFromSingleLinkedList(Node_t* linkedList, int deleteNumber){
    Node_t* next = NULL;

    // if the number to delete is the first one in the list
    if(linkedList->number == deleteNumber){
        next = linkedList->next;
        free(linkedList);
        linkedList = next;
        return linkedList;
    }

    Node_t* current = linkedList;

    while(current != NULL){
        next = current->next;

        if(next == NULL){
            return linkedList;
        }

        if(next->number == deleteNumber){

            // get the node after the node you want to delete
            next = next->next;

            // delete the node
            free(current->next);

            // point the current node to the one after the deleted node
            current->next = next;

            return linkedList;
        }

        current = next;
    }
    return linkedList;

}
