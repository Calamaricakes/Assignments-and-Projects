#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
    FILE* file_ptr;
    char characters[250];

    file_ptr = fopen("test_words.csv", "r");
    if(!file_ptr){
        printf("Unable to open file\n");
        exit(EXIT_FAILURE);
    }
    while(fgets(characters, 250, file_ptr) != NULL){
        printf("HERE\n");
        printf("%s\n", characters);
    }

    fclose(file_ptr);
    return 0;

}
