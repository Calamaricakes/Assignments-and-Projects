#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define FAILURE 0
#define MAX_FILE_NAME_LENGTH 100
#define MAX_PREFIX_LENGTH 250
#define MAX_DATA_INPUT 250
#define MAX_NUM_SEARCH_PREFIX 1000
#define MAX_CONSOLE_OUTPUT 500

typedef struct ter_char_node ter_char_node_t;

struct ter_char_node{
    char key;
    int weight;
    int end_of_flag;
    ter_char_node_t *left, *equal, *right;
};

typedef struct stats{
    int num_comparisons;
    char search_prefix[MAX_PREFIX_LENGTH];
}stats_t;

typedef struct stats2{
    int weight;
    char search_prefix[MAX_PREFIX_LENGTH];
}stats2_t;

typedef struct data_info{
    int num_prefix_nodes;
    int num_comparisons;
    int num_search_comparisons;
    char search_prefix[MAX_PREFIX_LENGTH];
}data_info_t;

ter_char_node_t* insert_in_ternary_tree(ter_char_node_t* pNode, char* word, int weight);
data_info_t find_and_traverse2(ter_char_node_t* pNode, char* prefix, stats2_t* info_arr);
int check_invalid_input(char check_string[], char data_name[], int max_length);
int find_and_traverse(ter_char_node_t* pNode, char* prefix);
int sort_prefix_results_decending(stats2_t arr[], int n);
void traverse(ter_char_node_t* pNode, char* buffer, int depth);
int traverse2(ter_char_node_t* pNode, char* buffer, int depth, stats2_t* info_arr, int index_position);
void free_ternary_tree(ter_char_node_t* pNode);

ter_char_node_t* insert_in_ternary_tree(ter_char_node_t* pNode, char* word, int weight){
/* insert functions to insert a node into a trenary search
   tree.'word' is the comparitor with ASCII that is case
   sensitive. Insertion sequence depends on the int 'weight'of
   the given node in decreasing order, with the largest weight
   inserted first. returns the node* root of the trenary tree.
*/
    ter_char_node_t* root_node = pNode;

    if (pNode == NULL){ //assign the node if it is empty
        ter_char_node_t* new_node =
        (ter_char_node_t*)malloc(sizeof(ter_char_node_t));

        if(!new_node){
            printf("Malloc Failure\n");
            exit(EXIT_FAILURE);
        }

        //initialise values
        new_node->key = *word;
        new_node->end_of_flag = FALSE;
        new_node->left = new_node->equal = new_node->right = NULL;

        //if there are no more characters to insert
        if(*(word+1) == '\0'){
            new_node->end_of_flag = TRUE;
            new_node->weight = weight;
        }
        else{
            //continue to insert the new characters
            new_node->equal = insert_in_ternary_tree(new_node->equal, word+1, weight);
        }
        return new_node;
    }
    if(*(word) < pNode->key){// if the word is 'smaller'
        pNode->left = insert_in_ternary_tree(pNode->left, word, weight);
    }
    else if(*(word) == pNode->key){
        // if word is 'equal'

        if(*(word+1) == '\0'){
            //if the word has ended, put flag and weight
            pNode->end_of_flag = TRUE;
            pNode->weight = weight;
        }
        else{
            //if there are more keys, insert down the 'equal' branch
            pNode->equal = insert_in_ternary_tree(pNode->equal, word+1, weight);
        }
    }
    else{
        // if word is 'bigger'
        pNode->right = insert_in_ternary_tree(pNode->right, word, weight);
    }
    return root_node;
}

int find_and_traverse(ter_char_node_t* pNode, char* prefix){
/* find node in ternary tree that contains the prefix, if prefix is found
   the pNode will point there if we reached the end of the search_prefix.
   if the prefix does not exist, then pNode should be null. */

    char buffer[MAX_PREFIX_LENGTH]; //unusual behaviour when not initialised
    int i = 0;
    int num_comparisons = 0;

    printf("Prefix: %s\n", prefix);

    while((*prefix != '\0') && (pNode != NULL)){
    // traverse tree to find the end of the search prefix

        if (*prefix < pNode->key){
            pNode = pNode->left;
            num_comparisons++;
            continue;
        }
        if (*prefix > pNode->key){
            pNode = pNode->right;
            num_comparisons++;
            continue;
        }
        if (*prefix == pNode->key){
            buffer[i++] = *prefix;
            num_comparisons++;
            if(*(prefix+1) == '\0'){
                break;
            }
            pNode = pNode->equal;
            prefix++;
            continue;
        }
    }
    // pNode now points at the end of the search word, now search for candidate
    // autocomplete keys

    if(pNode){

        // include the prefix itself as a candidate if the prefix is a key.
        if(pNode->end_of_flag == TRUE){
            buffer[i] = '\0';
            printf("%s\n", buffer);
        }

        //print all autocomplete candidates
        traverse(pNode->equal, buffer, i);
    }
    else{
        printf("NOTFOUND\n");
    }
    return num_comparisons; //return number of comparisons done
}

void traverse(ter_char_node_t* pNode, char* buffer, int depth){
    /* traverse searches the ternary tree recursively for autocomplete
       candidates. When a complete word(indicated by end_of_flag) is found,
       traverse prints the candidate to screen. */

    if(!pNode){
        return;
    }

    //traverse left node
    traverse(pNode->left, buffer, depth);
    buffer[depth] = pNode->key;

    //complete word is found, print to screen
    if(pNode->end_of_flag == TRUE){
        buffer[depth+1] = '\0';
        printf("key: %s --> weight: %d\n", buffer, pNode->weight);
    }
    //traverse equal node, depth is incremented to match buffer index
    traverse(pNode->equal, buffer, depth+1);

    //traverse right node
    traverse(pNode->right, buffer, depth);
}

data_info_t find_and_traverse2(ter_char_node_t* pNode, char* prefix, stats2_t* info_arr){
/* find node in ternary tree that contains the prefix, if prefix is found
   the pNode will point there if we reached the end of the search_prefix.
   if the prefix does not exist, then pNode should be null. */

    char buffer[MAX_PREFIX_LENGTH] = {0}; //unusual behaviour when not initialised
    int i = 0;
    int num_comparisons = 0;
    data_info_t info_node;

    printf("Prefix: %s\n", prefix);

    while((*prefix != '\0') && (pNode != NULL)){

    // traverse tree to find the end of the search prefix

        if (*prefix < pNode->key){
            pNode = pNode->left;
            num_comparisons++;
            continue;
        }
        if (*prefix > pNode->key){
            pNode = pNode->right;
            num_comparisons++;
            continue;
        }
        if (*prefix == pNode->key){
            buffer[i++] = *prefix;
            num_comparisons++;
            if(*(prefix+1) == '\0'){
                break;
            }
            pNode = pNode->equal;
            prefix++;
            continue;
        }
    }
    // pNode now points at the end of the search word, now search for candidate
    // autocomplete keys

    if(pNode){

        // include the prefix itself as a candidate if the prefix is a key.
        if(pNode->end_of_flag == TRUE){
            buffer[i] = '\0';
        }

        //save search information into a struct, then return the struct
        info_node.num_prefix_nodes = traverse2(pNode->equal, buffer, i, info_arr, 0);
        info_node.num_comparisons = num_comparisons;
    }
    else{
        printf("NOTFOUND\n");
        //save search information into a struct, then return the struct
        info_node.num_prefix_nodes = -1;
        info_node.num_comparisons = num_comparisons;
    }
    return info_node;
}

int traverse2(ter_char_node_t* pNode, char* buffer, int depth,
    stats2_t* info_arr, int index_position){
    //

    if(!pNode){
        return index_position;
    }
    stats2_t prefix_node;

    index_position = traverse2(pNode->left, buffer, depth,
                               info_arr, index_position);

    buffer[depth] = pNode->key;

    if(pNode->end_of_flag){
        buffer[depth+1] = '\0';
        prefix_node.weight = pNode->weight;
        strcpy(prefix_node.search_prefix, buffer);
    }

    index_position = traverse2(pNode->equal, buffer, depth+1,
                               info_arr, index_position);
    index_position = traverse2(pNode->right, buffer, depth,
                               info_arr, index_position);

    if(pNode->end_of_flag){
        info_arr[index_position] = prefix_node; //** ASSIGNED TO info_arr
        return index_position + 1;
    }
    else{
        return index_position;
    }
}

int sort_prefix_results_decending(stats2_t arr[], int n){
    int i, j, num_comparisons = 0;
    int max_value = -1, index_max_value;
    stats2_t holder;

    for(i = 0; i < n - 1; i++){
        max_value = arr[i].weight;
        for(j = i + 1; j < n; j++){
            if(arr[j].weight > max_value){
                max_value = arr[j].weight;
                index_max_value = j;
            }
            num_comparisons++;
        }
        if(arr[i].weight != max_value){
            holder = arr[i];
            arr[i] = arr[index_max_value];
            arr[index_max_value] = holder;
        }
    }
    return num_comparisons;
}

int check_invalid_input(char check_string[], char data_name[], int max_length){
    /* checks if length of the string is within max_length using strlen().
       strlen() does not include terminating character*/

       if(strlen(check_string) + 1 > max_length){
           // strlen() does not include terminating character
           printf("%s too long, limit %d characters.\n", data_name, max_length);
           return SUCCESS;
       }
       return FAILURE;
}
void free_ternary_tree(ter_char_node_t* pNode){
    if(!pNode){
        return;
    }
    free_ternary_tree(pNode->left);
    free_ternary_tree(pNode->equal);
    free_ternary_tree(pNode->right);
    free(pNode);
}
