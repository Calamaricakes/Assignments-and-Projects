#include "asst1_functions.h"

int main(int argc, char* argv[]){
    /* Program creates a referencial ternary char tree for the purpose of an
       string autocomplete program. Ternary char tree is made from data_file
       (argv[1]), outputs the result of the search to a file(argv[2]).
    */
    char data_file[MAX_FILE_NAME_LENGTH], search_prefix[MAX_PREFIX_LENGTH],
         output_file[MAX_FILE_NAME_LENGTH], data_for_tree[MAX_DATA_INPUT];
    char* ptr_token;
    int i, weight, node_index = 0;
    FILE* ptr_input_file;
    ter_char_node_t* ter_char_root_node = NULL;
    stats_t search_information[MAX_NUM_SEARCH_PREFIX];

    if(check_invalid_input(argv[1],"data file", MAX_FILE_NAME_LENGTH) ||
        check_invalid_input(argv[2],"output file", MAX_FILE_NAME_LENGTH)){
        // check if the inputs are of valid length

        exit(EXIT_FAILURE);
    }
    strcpy(data_file, argv[1]); // copy for clarity
    strcpy(output_file, argv[2]);

    // start build tree
    ptr_input_file = fopen(data_file, "r");

    if(!ptr_input_file){
        printf("Input file cannot be opened.\n");
        exit(EXIT_FAILURE);
    }

    //get data from file that has format <weight>;<key> per line
    while(fgets(data_for_tree, MAX_PREFIX_LENGTH, ptr_input_file) != NULL){
        //while there is still input
        if(check_invalid_input(data_for_tree, "data prefix",
            MAX_PREFIX_LENGTH)){
            exit(EXIT_FAILURE);
        }

        ptr_token = strtok(data_for_tree, ";");
        weight = atoi(ptr_token);       // weight as int for a prefix
        ptr_token = strtok(NULL, "\n"); // key as string for the prefix
        ter_char_root_node = insert_in_ternary_tree(ter_char_root_node,
            ptr_token, weight);

    }

    fclose(ptr_input_file);
    //end build tree

    //write all stdout to file
    if(!freopen(output_file, "w", stdout)){
        printf("Output file cannot be opened.\n");
        exit(EXIT_FAILURE);
    }

    //search for the new search_prefix in tree
    while(scanf(" %s", search_prefix) == SUCCESS){
        // scanning each prefix from input file

        if(check_invalid_input(search_prefix , "search prefix",
         MAX_PREFIX_LENGTH)){
            // check if the inputs are in valid length
            exit(EXIT_FAILURE);
        }

        //search tree for prefiX
        search_information[node_index].num_comparisons =
        find_and_traverse(ter_char_root_node, search_prefix);
        strcpy(search_information[node_index].search_prefix, search_prefix);
        //save search info to a struct of search_information array

        node_index++; //point to next struct
        printf("\n");

        if(node_index >= MAX_NUM_SEARCH_PREFIX){
            printf("Too many search terms\n");
            free_ternary_tree(ter_char_root_node);
            exit(EXIT_FAILURE);
        }
    }
    //end search

    //print statistics
    for(i = 0; i < node_index; i++){
        printf("Prefix: %s found with %d char comparisons\n",
        search_information[i].search_prefix,
        search_information[i].num_comparisons);
    }

    //free ternary tree
    free_ternary_tree(ter_char_root_node);
    fclose(stdout); //close stdout to file

    return 0;
}
