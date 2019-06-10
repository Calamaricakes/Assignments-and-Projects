#include <stdio.h>
#include <stdlib.h>

typedef struct Node_t{
    int number;
    struct Node_t* next;
}Node_t;

void freeStack(Node_t* linkedList);
Node_t* pop(Node_t* linkedList);
Node_t* push(Node_t* linkedList, int number);

int main(){

    int number;
    char decision = 'n';
    Node_t* linkedList = NULL;

    printf("Enter integer for stack: ");

    while(scanf("%d", &number) != EOF){
        linkedList = push(linkedList, number);
        printf("Enter integer for stack: ");
    }

    printf("Stack constructed\n");

    printf("Do you wish to pop the stack? y/n\n");
    scanf("%c", &decision);

    while(decision == 'y'){
        if(linkedList != NULL){
            linkedList = pop(linkedList);
            printf("\nDo you wish to pop the stack? y/n\n");
            scanf(" %c", &decision);
        }
        else{
            break;
        }
    }

    freeStack(linkedList);
    return 0;
}

Node_t* push(Node_t* linkedList, int number){

    Node_t* node;

    if(linkedList == NULL){
        linkedList = (Node_t*)malloc(1);
        linkedList->number = number;
        linkedList->next = NULL;
        return linkedList;
    }
    else{
        node = (Node_t*)malloc(1);
        node->number = number;
        node->next = linkedList;
        return node;
    }

}

Node_t* pop(Node_t* linkedList){

    Node_t* next = NULL;

    if(linkedList == NULL){
        printf("Empty stack\n");
        return linkedList;
    }
    else{
        printf("%d ", linkedList->number);
        next = linkedList->next;
        free(linkedList);
        return next;
    }
}

void freeStack(Node_t* linkedList){

    Node_t* next = NULL;

    while(linkedList != NULL){
        next = linkedList->next;
        printf("Free: %d\n", linkedList->number);
        free(linkedList);
        linkedList = next;
    }

}
