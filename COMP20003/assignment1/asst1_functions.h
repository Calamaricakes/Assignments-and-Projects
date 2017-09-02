#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define FAILURE 0

typedef struct ter_char_node ter_char_node_t;

struct ter_char_node{
    char key;
    int weight;
    int end_of_flag;
    ter_char_node_t *left, *equal, *right;
};

int check_invalid_input(char check_string[], char data_name[], int max_length);
ter_char_node_t* insert(ter_char_node_t* pNode, char* word, int weight);
void find_and_traverse(ter_char_node_t* pNode, char* prefix);
void traverse(ter_char_node_t* pNode, char* buffer, int depth);
void free_ternary_tree(ter_char_node_t* pNode);
void print_hello();

ter_char_node_t* insert(ter_char_node_t* pNode, char* word, int weight){
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
        new_node->key = *word;
        new_node->end_of_flag = FALSE;
        new_node->left = new_node->equal = new_node->right = NULL;

        if(*(word+1) == '\0'){ //if there are no more characters to insert
            new_node->end_of_flag = TRUE;
            new_node->weight = weight;
        }
        else{
            //continue to insert the new characters
            new_node->equal = insert(new_node->equal, word+1, weight);
        }
        return new_node;
    }
    if(*(word) < pNode->key){// if the word is 'smaller'
        pNode->left = insert(pNode->left, word, weight);
    }
    else if(*(word) == pNode->key){ // if word is 'equal'
        if(*(word+1) == '\0'){ //if the word has ended, put flag and weight
            pNode->end_of_flag = TRUE;
            pNode->weight = weight;
        }
        else{ //if there are more keys, insert down the 'equal' branch
            pNode->equal = insert(pNode->equal, word+1, weight);
        }
    }
    else{// if word is 'bigger'
        pNode->right = insert(pNode->right, word, weight);
    }
    return root_node;
}

void find_and_traverse(ter_char_node_t* pNode, char* prefix){
/* find node in ternary tree that contains the prefix, if prefix is found
   the pNode will point there if we reached the end of the search_prefix.
   if the prefix does not exist, then pNode should be null. */

    char buffer[250];

    strcpy(buffer, prefix); //current word

    while((*prefix != '\0') && (pNode != NULL)){

    // traverse tree to find the end of the search prefix

        if (*prefix < pNode->key){
            pNode = pNode->left;
            continue;
        }
        if (*prefix > pNode->key){
            pNode = pNode->right;
            continue;
        }
        if (*prefix == pNode->key){
            pNode = pNode->equal;
            prefix++;
            continue;
        }
    }
    // pNode now points at the end of the search word, now search for candidate
    // autocomplete keys

    if(pNode){
    //  Include the prefix itself as a candidate if the prefix is a key.
        if(pNode->end_of_flag == TRUE){
            buffer[strlen(prefix)] = '\0';
            printf("%s\n", buffer);
        }
        //print all the keys that contain the prefix

        traverse(pNode, buffer, strlen(prefix));
    }
}

void traverse(ter_char_node_t* pNode, char* buffer, int depth){

    if(!pNode){
        return;
    }
    traverse(pNode->left, buffer, depth+1);

    buffer[depth] = pNode->key;

    if(pNode->end_of_flag == TRUE){
        buffer[depth+1] = '\0';
        printf("%s\n", buffer);
    }

    traverse(pNode->equal, buffer, depth+1);
    traverse(pNode->right, buffer, depth+1);
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
    printf("Hi\n");
    free_ternary_tree(pNode->left);
    free_ternary_tree(pNode->equal);
    free_ternary_tree(pNode->right);
    free(pNode);
}

void print_hello_world(){
    printf("Hello World!\n");
}
