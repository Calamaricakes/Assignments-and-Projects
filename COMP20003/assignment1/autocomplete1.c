#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "asst1_functions.h"

#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define FAILURE 0
#define SINGLE_PREFIX_INPUT 3   //single prefix search
#define MAX_FILE_NAME_LENGTH 100
#define MAX_PREFIX_LENGTH 250
#define MAX_NUM_SEARCH_PREFIX 50

int main(int argc, char* argv[]){
    char data_file[MAX_FILE_NAME_LENGTH], prefix[MAX_PREFIX_LENGTH],
         output_file[MAX_FILE_NAME_LENGTH], input_prefix[MAX_PREFIX_LENGTH];
    int i;

    // overflow checks
    if(argc == SINGLE_PREFIX_INPUT){
        if(strlen(argv[1]) > MAX_FILE_NAME_LENGTH - 1){
            // strlen() does not include terminating character

            printf("Datafile name too long, limit %d characters.\n",
                    MAX_FILE_NAME_LENGTH - 1);
            exit(EXIT_FAILURE);
        }
        else if(strlen(argv[2]) > MAX_FILE_NAME_LENGTH - 1){
            printf("Output file name too long, limit %d characters.\n",
                    MAX_FILE_NAME_LENGTH - 1);
            exit(EXIT_FAILURE);
        }
        else if(strlen(argv[3]) > MAX_PREFIX_LENGTH - 1){
            printf("Prefix length too long, limit %d characters.\n",
            MAX_PREFIX_LENGTH - 1);
            exit(EXIT_FAILURE);
        }
    }

    strcpy(data_file, argc[1]); // copy for clarity
    strcpy(prefix, argv[2]);

    while(scanf("%s", input_prefix) == SUCCESS){


    }
    return 0;


}
