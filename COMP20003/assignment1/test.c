#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int number;
}node_t;

int comp(node_t* first, node_t* second){
    if(first->number < second->number){
        return -1;
    }
    else if(first->number > second->number){
        return 1;
    }
    else{
        return 0;
    }
}

int main(int argc, char* argv[]){
    node_t one, two;
    one.number = 2;
    two.number = 2;
    printf("%d\n", comp(&one, &two));
    return 0;
}
