#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void function(char* word, int length);

int main(int argc, char* argv[]){

    function("cherry", strlen("cherry"));
    return 0;

}

void function(char* word, int length){
    int i;

    for(i = 0; i < length; i++){
        printf("%c\n", *(word+i));

    }

}
