#include <stdio.h>
#include <stdlib.h>

typedef struct Node_t{
    int number;
    struct Node_t* next;
}Node_t;

#define EMPTY -1

void freeStack(Node_t* linkedList);
int pop(Node_t** linkedList);
void push(Node_t** linkedList, int number);
void printStack(Node_t* linkedList);

int main(){

    int inputNumber, number;
    char decision;
    Node_t* linkedList = NULL;

    printf("Options: Push 'i', Pop: 'o', Exit: 'e'\n");
    scanf(" %c", &decision);

    while(decision != 'e'){

        switch(decision){

            case 'i':
                printf("Please enter integer for stack: ");
                scanf("%d", &inputNumber);
                push(&linkedList, inputNumber);
                break;

            case 'o':
                number = pop(&linkedList);
                printf("Pop: %d\n", number);
                break;

            case 'p':
                printStack(linkedList);
                break;

        }
        printf("Options: Push 'i', Pop 'o', Print 'p', Exit 'e'\n");
        scanf(" %c", &decision);
    }

    freeStack(linkedList);
    return 0;
}

void push(Node_t** linkedList, int number){

    Node_t* node;

    if(*linkedList == NULL){
        *linkedList = (Node_t*)malloc(1);
        (*linkedList)->number = number;
        (*linkedList)->next = NULL;
    }
    else{
        node = (Node_t*)malloc(1);
        node->number = number;
        node->next = *linkedList;
        *linkedList = node;
    }

}

int pop(Node_t** linkedList){

    Node_t* next = NULL;
    int number;

    if(linkedList == NULL){
        printf("linkList empty.\n");
        return EMPTY;
    }
    else{
        number = (*linkedList)->number;
        next = (*linkedList)->next;
        free(*linkedList);
        *linkedList = next;
        return number;
    }
}

void printStack(Node_t* linkedList){

    while(linkedList != NULL){
        printf("%d ", linkedList->number);
        linkedList = linkedList->next;
    }
    printf("\n");
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
