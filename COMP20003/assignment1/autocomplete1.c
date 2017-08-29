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
#define MAX_DATA_INPUT 250
#define MAX_NUM_SEARCH_PREFIX 50

int main(int argc, char* argv[]){
    /* Program creates a referencial ternary char tree for the purpose ot an
       string autocomplete program. Ternary char tree is made from data_file
       (argv[1]), outputs the result of a prefix(argv[3] or text file [using input
       redirection]) in a file to output_file(argv[2]).
    */
    char data_file[MAX_FILE_NAME_LENGTH], prefix[MAX_PREFIX_LENGTH],
         output_file[MAX_FILE_NAME_LENGTH], data_for_tree[MAX_DATA_INPUT];
    char* ptr_token;
    int weight;
    FILE* ptr_file;

    if(argc == SINGLE_PREFIX_INPUT){
        /* if the input is only a one prefix for search */

        if(check_invalid_input(argv[1],"data file", MAX_FILE_NAME_LENGTH) ||
           check_invalid_input(argv[2],"output file", MAX_FILE_NAME_LENGTH) ||
           check_invalid_input(argv[3],"prefix", MAX_PREFIX_LENGTH)){
           // check if the inputs are in valid length
           exit(EXIT_FAILURE);
        }
        strcpy(data_file, argc[1]); // copy for clarity
        strcpy(output_file, argv[2]);
        strcpy(prefix, argv[3]);
    }
    else{
        if(!scanf("%s\n", prefix)){ // if there is no prefix to search for
            printf("No prefix input\n");
            exit(EXIT_FAILURE);
        }

        if(check_invalid_input(argv[1],"data file", MAX_FILE_NAME_LENGTH) ||
           check_invalid_input(argv[2],"output file", MAX_FILE_NAME_LENGTH) ||
           check_invalid_input(prefix, "prefix", MAX_PREFIX_LENGTH)){
           // check if the inputs are in valid length
           exit(EXIT_FAILURE);
        }
        strcpy(data_file, argc[1]); // copy for clarity
        strcpy(output_file, argv[2]);

        //build tree
        ptr_file = fopen(data_file, "r");

        if(!ptr_file){
            printf("File cannot be opened.\n", );
            exit(EXIT_FAILURE);
        }

        while(fgets(data_for_tree, MAX_PREFIX_LENGTH, ptr_file) != NULL){
            //while there is still input

            ptr_token = strtok(data_for_tree, ";");
            weigth = atoi(ptr_token);           // weight as int for a prefix
            ptr_token = strtok(NULL, "\n");     // key as string for the prefix
        }
        fclose(ptr_file);
        //search tree

        //search for the new prefix in tree
        while(scanf("%s", prefix) == SUCCESS){
            // scanning each prefix from input file
            if(check_invalid_input(prefix , "prefix", MAX_PREFIX_LENGTH)){
               // check if the inputs are in valid length
               exit(EXIT_FAILURE);
            }

        }
    }




        /* data_file, prefix, and output_file should now be initilised */



    }


}
