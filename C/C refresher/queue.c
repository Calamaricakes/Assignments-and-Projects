// implementing a first in first out (FIFO) data structure with linked lists

#include <stdio.h>
#include <stdlib.h>

typedef struct Node_t{
    int number;
    struct Node_t* next;
}Node_t;

Node_t* newNode(int number);
void enqueue(Node_t** queue_ptr_ptr, int number);
int dequeue(Node_t** queue_ptr_ptr);
void clearQueue(Node_t** queue_ptr);
void printQueue(Node_t* queue_ptr);

#define EMPTY -1

int main(){

    int inputNumber, number;
    char decision;
    Node_t* queue_ptr = NULL;

    printf("Please enter an option to enqueue('e'), dequeue('d'), print('p') or quit('q'): ");

    while(scanf(" %c", &decision) != 'q'){

        switch (decision){
            case 'e':
                printf("Please enter an number for the queue: ");
                scanf("%d", &inputNumber);
                enqueue(&queue_ptr, inputNumber);
                break;

            case 'd':
                number = dequeue(&queue_ptr);

                if(number != EMPTY){
                    printf("Dequeue: %d \n", number);
                }
                break;

            case 'p':
                printQueue(queue_ptr);
                break;

            case 'c':
                clearQueue(&queue_ptr);
                printQueue(queue_ptr);
                break;
        }

        printf("Please enter an option to enqueue('e'), dequeue('d'), print('p'), clear('c'), quit('q'): ");
    }

    clearQueue(&queue_ptr);

    return 0;
}

void enqueue(Node_t** queue_ptr_ptr, int number){

    Node_t* current_node_ptr = *queue_ptr_ptr;
    Node_t* new_node_ptr = NULL;

    if(*queue_ptr_ptr == NULL){
        *queue_ptr_ptr = newNode(number);
        return;
    }

    while(current_node_ptr->next != NULL){
        current_node_ptr = current_node_ptr->next;
    }

    new_node_ptr = newNode(number);
    current_node_ptr->next = new_node_ptr;
}

Node_t* newNode(int number){

    Node_t* node = (Node_t*)malloc(1);
    node->number = number;
    node->next = NULL;
    return node;
}

void printQueue(Node_t* queue_ptr){

    if(queue_ptr == NULL){
        printf("Empty queue.\n");
    }

    while(queue_ptr != NULL){
        printf("%d ", queue_ptr->number);
        queue_ptr = queue_ptr->next;
    }

    printf("\n");
}

int dequeue(Node_t** queue_ptr_ptr){

    int number;
    Node_t* next_ptr = NULL;
    Node_t* queue_ptr = *queue_ptr_ptr;

    if(queue_ptr == NULL){
        printf("Empty queue\n");
        return EMPTY;
    }

    next_ptr = queue_ptr->next;
    number = queue_ptr->number;
    free(queue_ptr);
    *queue_ptr_ptr = next_ptr;

    return number;
}

void clearQueue(Node_t** queue_ptr_ptr){
    Node_t* temp_ptr = NULL;

    if(*queue_ptr_ptr == NULL){
        return;
    }

    while(*queue_ptr_ptr != NULL){
        temp_ptr = (*queue_ptr_ptr)->next;
        free(*queue_ptr_ptr);
        *queue_ptr_ptr = temp_ptr;
    }
}
