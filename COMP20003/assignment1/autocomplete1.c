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
    /* Program creates a referencial ternary char tree for the purpose ot an
       string autocomplete program. Ternary char tree is made from data_file
       (argv[1]), outputs the result of a prefix(argv[3] or text file [using input
       redirection]) in a file to output_file(argv[2]).
    */
    char data_file[MAX_FILE_NAME_LENGTH], prefix[MAX_PREFIX_LENGTH],
         output_file[MAX_FILE_NAME_LENGTH], input_prefix[MAX_PREFIX_LENGTH];
    int multiple_output = FALSE;
    int i;

    if(argc == SINGLE_PREFIX_INPUT){
        /* if the input is only a one prefix for search */

        if(check_input(argv[1],"data file", MAX_FILE_NAME_LENGTH) ||
           check_input(argv[2],"output file", MAX_FILE_NAME_LENGTH) ||
           check_input(argv[3],"prefix", MAX_PREFIX_LENGTH)){
           // check if the inputs are in valid length
           exit(EXIT_FAILURE);
        }
        strcpy(data_file, argc[1]); // copy for clarity
        strcpy(output_file, argv[2]);
        strcpy(prefix, argv[3]);
    }
    else{

        while(scanf("%s", prefix) == SUCCESS){




        }

    }




        /* data_file, prefix, and output_file should now be initilised */



    }


}
