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
#define SINGLE_PREFIX_INPUT 4   //single prefix search
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
    char data_file[MAX_FILE_NAME_LENGTH], search_prefix[MAX_PREFIX_LENGTH],
         output_file[MAX_FILE_NAME_LENGTH], data_for_tree[MAX_DATA_INPUT];
    char* ptr_token;
    int weight;
    FILE* ptr_file;
    ter_char_node_t* ter_char_root_node = NULL;

    /*
    if(argc == SINGLE_PREFIX_INPUT){
        // if the input is only a one prefix for search

        if(check_invalid_input(argv[1],"data file", MAX_FILE_NAME_LENGTH) ||
           check_invalid_input(argv[2],"output file", MAX_FILE_NAME_LENGTH) ||
           check_invalid_input(argv[3],"search prefix", MAX_PREFIX_LENGTH)){
           // check if the inputs are in valid length
           exit(EXIT_FAILURE);
        }
        strcpy(data_file, argv[1]); // copy for clarity
        strcpy(output_file, argv[2]);
        strcpy(search_prefix, argv[3]);
    }
    else{ */

        if(check_invalid_input(argv[1],"data file", MAX_FILE_NAME_LENGTH) ||
           check_invalid_input(argv[2],"output file", MAX_FILE_NAME_LENGTH)){
           // check if the inputs are of valid length

           exit(EXIT_FAILURE);
        }
        strcpy(data_file, argv[1]); // copy for clarity
        strcpy(output_file, argv[2]);

        //build tree
        ptr_file = fopen(data_file, "r");

        if(!ptr_file){
            printf("File cannot be opened.\n");
            exit(EXIT_FAILURE);
        }

        //get data from file that has format <weight>;<key> per line
        while(fgets(data_for_tree, MAX_PREFIX_LENGTH, ptr_file) != NULL){
            //while there is still input
            if(check_invalid_input(data_for_tree, "data prefix",
                MAX_PREFIX_LENGTH)){
                   exit(EXIT_FAILURE);
            }

            ptr_token = strtok(data_for_tree, ";");
            weight = atoi(ptr_token);       // weight as int for a prefix
            ptr_token = strtok(NULL, "\n"); // key as string for the prefix
            ter_char_root_node = insert(ter_char_root_node, ptr_token, weight);
        }

        fclose(ptr_file);
        //end build tree

        //search for the new search_prefix in tree
        while(scanf(" %s", search_prefix) == SUCCESS){
            // scanning each prefix from input file
            if(check_invalid_input(search_prefix , "search prefix", MAX_PREFIX_LENGTH)){
               // check if the inputs are in valid length
               exit(EXIT_FAILURE);
            }
            //search tree for prefix
            find_and_traverse(ter_char_root_node, search_prefix);

        }
        //free ternary tree
        free_ternary_tree(ter_char_root_node);

}
